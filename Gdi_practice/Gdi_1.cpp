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
	Gdiplus::Color fillColor;
	Gdiplus::Color outlineColor;
	Gdiplus::Color backgroundColor;
	Gdiplus::PointF position;
	float scale;
	bool antialiasing;
	bool defaultRegion;
	void init()
	{
 		this->text = L"TEXT";
		this->font = L"Times new roman";
		this->height = 24;
		this->angle = 0;
		this->fillColor = Gdiplus::Color(255, 255, 0);
		this->outlineColor = Gdiplus::Color::Red;
		this->backgroundColor = Gdiplus::Color::White;
		this->position = Gdiplus::PointF(0, 0);
		this->scale = 3;
		this->antialiasing = true;
		this->defaultRegion = true;
	}
};
Config config;
HRGN oldRgn;
Gdiplus::Rect rectangle;
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
   config.init();
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   GetWindowRgn(hWnd, oldRgn);

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
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_RBUTTONUP:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, Settings);
		{
			Gdiplus::Graphics g(hWnd);
			Gdiplus::GraphicsPath path;
			path.AddString(config.text,
							-1,
							new Gdiplus::FontFamily(config.font),
							Gdiplus::FontStyleRegular,
							config.height,
							config.position,
							new Gdiplus::StringFormat());
			g.RotateTransform(config.angle);
			g.ScaleTransform(config.scale, config.scale);
			g.SetInterpolationMode(config.antialiasing ? Gdiplus::InterpolationModeHighQuality : Gdiplus::InterpolationModeLowQuality);
			Gdiplus::Region r(&path);
			RECT rect, rect1;
			GetClientRect(hWnd, &rect);
			ClientToScreen(hWnd, (LPPOINT)&rect);
			GetWindowRect(hWnd, &rect1);
			HRGN h = r.GetHRGN(&g);
			OffsetRgn(h, (rect.left - rect1.left), (rect.top - rect1.top));
			SetWindowRgn(hWnd, config.defaultRegion ? oldRgn : h, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
    case WM_PAINT:
        {
			HDC hdc = BeginPaint(hWnd, &ps);
			{
				Gdiplus::Graphics g(hdc);
				Gdiplus::GraphicsPath path;
				path.AddString(config.text,
								-1,
								new Gdiplus::FontFamily(config.font),
								Gdiplus::FontStyleRegular,
								config.height,
								config.position,
								new Gdiplus::StringFormat);
				g.Clear(config.backgroundColor);
				g.RotateTransform(config.angle);
				g.ScaleTransform(config.scale, config.scale);
				if (config.antialiasing)
				{
					g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
				}
				//g.SetSmoothingMode(config.antialiasing ? Gdiplus::SmoothingModeHighQuality : );
				g.DrawPath(new Gdiplus::Pen(config.outlineColor, 2.f), &path);
				g.FillPath(new Gdiplus::SolidBrush(config.fillColor), &path);
			}
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

void copy(wchar_t*& text, wchar_t* buff)
{
	text = (new wchar_t[wcslen(buff)]);
	for (int i = 0; i < wcslen(buff); i++)
	{
		text[i] = buff[i];
	}
	text[wcslen(buff)] = L'\0';
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
			SetDlgItemInt(hDlg, IDC_EDIT_FILL_COLOR, config.fillColor.GetValue(), FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_OUTLINE_COLOR, config.outlineColor.GetValue(), FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_BACKGROUND_COLOR, config.backgroundColor.GetValue(), FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_X, config.position.X, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_Y, config.position.Y, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_ANGLE, config.angle, TRUE);
			wchar_t s[32];
			swprintf(s, -1, L"%.2f", config.scale);
			SetDlgItemTextW(hDlg, IDC_EDIT_SCALE, s);
			CheckDlgButton(hDlg, IDC_CHECK_QUALITY, config.antialiasing);
			CheckDlgButton(hDlg, IDC_CHECK_REGION, config.defaultRegion);
		}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			wchar_t buff[32];
			GetDlgItemTextW(hDlg, IDC_EDIT_TEXT, buff, sizeof(buff));
			copy(config.text, buff);
			GetDlgItemTextW(hDlg, IDC_EDIT_FONT_FAMILY, buff, sizeof(buff));
			copy(config.font, buff);
			config.height = GetDlgItemInt(hDlg, IDC_EDIT_FONT_SIZE, 0, 0);
			config.fillColor = GetDlgItemInt(hDlg, IDC_EDIT_FILL_COLOR, 0, 0);
			config.outlineColor = GetDlgItemInt(hDlg, IDC_EDIT_OUTLINE_COLOR, 0, 0);
			config.backgroundColor = GetDlgItemInt(hDlg, IDC_EDIT_BACKGROUND_COLOR, 0, 0);
			config.position.X = GetDlgItemInt(hDlg, IDC_EDIT_X, 0, 0);
			config.position.Y = GetDlgItemInt(hDlg, IDC_EDIT_Y, 0, 0);
			config.angle = GetDlgItemInt(hDlg, IDC_EDIT_ANGLE, 0, 0);
			config.scale = GetDlgItemInt(hDlg, IDC_EDIT_SCALE, 0, 0);
			config.antialiasing = IsDlgButtonChecked(hDlg, IDC_CHECK_QUALITY);
			config.defaultRegion = IsDlgButtonChecked(hDlg, IDC_CHECK_REGION);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}
