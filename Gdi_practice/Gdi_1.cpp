// Gdi_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Gdi_1.h"
#include <windows.h>
#include <GdiPlus.h>
#include <iostream>

#define MAX_LOADSTRING 100

// Global Variables:
struct Config
{
	wchar_t * text;
	wchar_t * font;
	float height;
	float angle;
	Gdiplus::Font * tempFont;
	Gdiplus::Color * fillColor;
	Gdiplus::Color * outlineColor;
	Gdiplus::Color * backgroundColor;
	Gdiplus::PointF * position;
	float scale;
	bool antialiasing;
	bool defaultRegion;
	void init()
	{
 		this->text = L"TEXT";
		this->font = L"Times new roman";
		this->height = 24;
		this->angle = 0;
		this->tempFont = new Gdiplus::Font(&Gdiplus::FontFamily(L"Times new roman"), 25);
		this->fillColor = new Gdiplus::Color(Gdiplus::Color::Black);
		this->outlineColor = new Gdiplus::Color(Gdiplus::Color::Red);
		this->backgroundColor = new Gdiplus::Color(Gdiplus::Color::White);
		this->position = new Gdiplus::PointF(0, 0);
		this->scale = 3;
		this->antialiasing = true;
		this->defaultRegion = false;
	}
};
Config config;
HRGN oldR;
HINSTANCE hInst;                                // current instance
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Settings(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::Status status = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	if (status != Gdiplus::Ok)
	{
		return FALSE;
	}

	config.init();
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GDI_1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDI_1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	Gdiplus::GdiplusShutdown(gdiplusToken);
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDI_1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GDI_1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
	Gdiplus::Graphics g(hWnd);
	Gdiplus::GraphicsPath path;
	path.AddString(config.text, -1, new Gdiplus::FontFamily(config.font), Gdiplus::FontStyleRegular, config.height * config.scale, *config.position, new Gdiplus::StringFormat());
	Gdiplus::Region r(&path);
	GetWindowRgn(hWnd, oldR);
	RECT rect, rect1;
	GetClientRect(hWnd, &rect);
	ClientToScreen(hWnd, (LPPOINT)&rect);
	GetWindowRect(hWnd, &rect1);
	HRGN h = r.GetHRGN(&g);
	OffsetRgn(h, (rect.left - rect1.left), (rect.top - rect1.top));
	SetWindowRgn(hWnd, h, TRUE);
	//SetWindowRgn(hWnd, oldR, FALSE);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, Settings);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			/*case IDM_FILE_SETTINGS:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, Settings);
				break;*/
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break; 
    case WM_PAINT:
        {
			HDC hdc = BeginPaint(hWnd, &ps);
			Gdiplus::Graphics g(hdc);
			Gdiplus::Font myFont(new Gdiplus::FontFamily(L"Arial"), 16);
			Gdiplus::PointF layoutRect(0, 0);
			Gdiplus::StringFormat format;
			Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 0, 0, 0));
			Gdiplus::GraphicsPath path;
			path.AddString(config.text, -1, new Gdiplus::FontFamily(config.font), Gdiplus::FontStyleRegular, config.height, *config.position, &format);
			g.Clear(*config.backgroundColor);
			g.RotateTransform(config.angle);
			g.ScaleTransform(config.scale, config.scale);
			g.SetInterpolationMode(config.antialiasing ? Gdiplus::InterpolationModeHighQuality : Gdiplus::InterpolationModeLowQuality);
			g.DrawPath(new Gdiplus::Pen(*config.outlineColor, 2.f), &path);
			g.FillPath(new Gdiplus::SolidBrush(*config.fillColor), &path);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemTextW(hDlg, IDC_EDIT_TEXT, config.text);
		SetDlgItemTextW(hDlg, IDC_EDIT_FONT_FAMILY, config.font);
		SetDlgItemInt(hDlg, IDC_EDIT_FONT_SIZE, config.height, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT_FILL_COLOR, config.fillColor->GetValue(), FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT_OUTLINE_COLOR, config.outlineColor->GetValue(), FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT_BACKGROUND_COLOR, config.backgroundColor->GetValue(), FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT_X, config.position->X, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT_Y, config.position->Y, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT_ANGLE, config.angle, TRUE);
		wchar_t s[32];
		_scwprintf(s, L"%lf", &config.scale);
		SetDlgItemTextW(hDlg, IDC_EDIT_SCALE, s);
		CheckDlgButton(hDlg, IDC_CHECK_QUALITY, config.antialiasing);
		CheckDlgButton(hDlg, IDC_CHECK_REGION, config.defaultRegion);
		PostMessage(hWnd, WM_PAINT, 0, 0);
	}
	return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			GetDlgItemTextW(hDlg, IDC_EDIT_TEXT, config.text, 0);
			GetDlgItemTextW(hDlg, IDC_EDIT_FONT_FAMILY, config.font, 0);
			config.height = GetDlgItemInt(hDlg, IDC_EDIT_FONT_SIZE, FALSE, FALSE);
			config.fillColor->SetValue(GetDlgItemInt(hDlg, IDC_EDIT_FILL_COLOR, FALSE, FALSE));
			config.outlineColor->SetValue(GetDlgItemInt(hDlg, IDC_EDIT_OUTLINE_COLOR, FALSE, FALSE));
			config.backgroundColor->SetValue(GetDlgItemInt(hDlg, IDC_EDIT_BACKGROUND_COLOR, FALSE, FALSE));
			config.position->X = GetDlgItemInt(hDlg, IDC_EDIT_X, FALSE, FALSE);
			config.position->Y = GetDlgItemInt(hDlg, IDC_EDIT_Y, FALSE, FALSE);
			config.angle = GetDlgItemInt(hDlg, IDC_EDIT_ANGLE, FALSE, FALSE);
			wchar_t s[32];
			_scwprintf(s, L"%lf", &config.scale);
			GetDlgItemTextW(hDlg, IDC_EDIT_SCALE, config.text, 0);
			config.antialiasing = IsDlgButtonChecked(hDlg, IDC_CHECK_QUALITY);
			config.defaultRegion = IsDlgButtonChecked(hDlg, IDC_CHECK_REGION);
			PostMessage(hWnd, WM_PAINT, 0, 0);
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			PostQuitMessage(0);
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}
