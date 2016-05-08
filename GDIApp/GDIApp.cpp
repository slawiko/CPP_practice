#define _CRT_SECURE_NO_WARNINGS
// GDIApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GDIApp.h"
#include <commdlg.h>
#include <windowsx.h>
#include "Windows.h"
#include <GdiPlus.h>

using namespace Gdiplus;
using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
char text[MAX_LOADSTRING] = "Text";
int height = 48;
int textLength = 4;
int helper;
CHOOSEFONT cf; //структура стандартного диалога выбора шрифта
LOGFONT lf; //структура шрифта

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	TextDlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	HeightDlgProc(HWND, UINT, WPARAM, LPARAM);
//Status				GdiplusStartup(ULONG_PTR* token, const GdiplusStartupInput* input, GdiplusStartupOutput* output);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GDIAPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDIAPP));

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDIAPP));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GDIAPP);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, _T("GDI Application"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		//case ID_OPTIONS_SETTEXT:
		//	if (DialogBox(hInst, MAKEINTRESOURCE(IDD_TEXTDIALOG), hWnd, TextDlgProc) == IDOK)
		//	{
		//		InvalidateRect(hWnd, NULL, TRUE);
		//	}
		//	break;
		//case ID_OPTIONS_SETFONT:
		//	HDC hdc;

		//	cf.Flags = CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
		//	cf.hwndOwner = hWnd; //родительское окно
		//	cf.lpLogFont = &lf; //указатель на LOGFONT
		//	cf.lStructSize = sizeof(CHOOSEFONT); //размер структуры
		//	strcpy_s(lf.lfFaceName, "ARIAL");

		//	

		//	if (ChooseFont(&cf)) {
		//		//Здесь можно вставить действия, которые надо выполнить
		//		//в случае успешного выбора шрифта
		//		hdc = GetDC(hWnd);

		//		SetMapMode(hdc, MM_TEXT); //Поменяем режим отображения
		//		InvalidateRect(hWnd, NULL, TRUE);
		//	}
		//	break;
		//case ID_OPTIONS_FONTHEIGHT:
		//	if (DialogBox(hInst, MAKEINTRESOURCE(IDD_HEIGHTDIALOG), hWnd, HeightDlgProc) == IDOK)
		//	{
		//		InvalidateRect(hWnd, NULL, TRUE);
		//	}
		//	break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		WCHAR welcome[] = L"Welcome, GDI+ !";
		Graphics g(hdc);
		g.SetPageUnit(UnitPixel);
		RectF bounds(0, 0, float(ps.rcPaint.right), float(ps.rcPaint.bottom));
		// Создаем кисть с градиентом на все окно и полупрозрачностью
		LinearGradientBrush brush(bounds, Color(130, 255, 0, 0), Color(255, 0, 0, 255),
			LinearGradientModeBackwardDiagonal);

		// Готовим формат и параметры шрифта
		StringFormat format;
		format.SetAlignment(StringAlignmentCenter);
		format.SetLineAlignment(StringAlignmentCenter);
		Font font(L"Arial", 48, FontStyleBold);

		// Выводим текст приветствия, длина -1 означает, 
		// что строка заканчивается нулем
		g.DrawString(welcome, -1, &font, bounds, &format, &brush);

		EndPaint(hWnd, &ps);

		/*PAINTSTRUCT ps;
		RECT rect;

		HDC hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);

		int rgb = SetDCPenColor(hdc, BLACK_PEN);
		HPEN hpen = CreatePen(PS_SOLID, height, BLACK_PEN);
		HGDIOBJ hGDIObj = SelectObject(hdc, hpen);	
		

		//HFONT hFont = CreateFont(height, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
		lf.lfHeight = height;
		HFONT hFont = CreateFontIndirect(&lf);
		SelectObject(hdc, hFont); //Зададим новый шрифт
		SetTextColor(hdc, cf.rgbColors); //Зададим новый цвет текста
		SelectObject(hdc, hFont); //Зададим новый шрифт
		SetTextColor(hdc, cf.rgbColors); //Зададим новый цвет текста
		//SelectObject(hdc, GetStockObject(SYSTEM_FONT)); //Вернём стандартный шрифт

		HFONT oldFont = (HFONT) SelectObject(hdc, hFont);

		TextOut(hdc, 0, 0, text, textLength);

		SelectObject(hdc, hGDIObj);
		SetDCPenColor(hdc, rgb);
		DeleteObject(hGDIObj);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);

		EndPaint(hWnd, &ps);*/
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//INT_PTR CALLBACK TextDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		SetDlgItemText(hDlg, IDC_TEXTEDIT, text);
//		return (INT_PTR) TRUE;
//
//	case WM_COMMAND:
//		switch (LOWORD(wParam))
//		{
//		case IDOK:
//			textLength = GetWindowTextLength(GetDlgItem(hDlg, IDC_TEXTEDIT));
//			GetDlgItemText(hDlg, IDC_TEXTEDIT, text, textLength + 1);
//		case IDCANCEL:
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR) TRUE;
//		}
//		break;
//	}
//	return (INT_PTR) FALSE;
//}
//
//INT_PTR CALLBACK HeightDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		SetDlgItemInt(hDlg, IDC_HEIGHTEDIT, height, FALSE);
//		return (INT_PTR) TRUE;
//
//	case WM_COMMAND:
//		switch (LOWORD(wParam))
//		{
//		case IDOK:
//			height = GetDlgItemInt(hDlg, IDC_HEIGHTEDIT, NULL, FALSE);
//		case IDCANCEL:
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR) TRUE;
//		}
//		break;
//	}
//	return (INT_PTR) FALSE;
//}
