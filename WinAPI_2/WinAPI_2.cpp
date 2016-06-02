// WinAPI_2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WinAPI_2.h"
#include <CommCtrl.h>
#include <iostream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWnd, hWndChild;
struct Element
{
	wchar_t name[255];
	int num;
} elems[100];
int k;
int format;
int index = -1;

// Forward declarations of functions included in this code module:
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);
//HWND				CreateListView(HWND hwndParent);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI_2, szWindowClass, MAX_LOADSTRING);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI_2));

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

    return (int) msg.wParam;
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

	hWnd = CreateDialogW(hInst, MAKEINTRESOURCE(IDD_MAIN_DIALOG), nullptr, DlgProc);
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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

void print(HWND hwndList, Element & el, UINT msg, WPARAM wParam)
{
	LV_ITEMW item;
	item.pszText = el.name;
	item.iItem = el.num;
	item.iSubItem = 0;
	item.mask = LVIF_TEXT;
	item.cchTextMax = 1;
	int x = ListView_InsertItem(hwndList, &item);
}

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	HWND hwndList;
	wchar_t str[255];
	int x;
	switch (message)
	{
		case WM_INITDIALOG:
			CheckDlgButton(hDlg, IDC_RADIO_LIST, 1);
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			std::cout << LOWORD(wParam);
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_ADD:
				hwndList = GetDlgItem(hDlg, IDC_LIST_CONTROL);
				GetDlgItemTextW(hDlg, IDC_EDIT_ADD, str, 255);
				elems[k].num = k;
				wcscpy_s(elems[k].name, str);
				print(hwndList, elems[k++], LVM_INSERTITEM, 0);
				SetDlgItemTextW(hDlg, IDC_EDIT_ADD, L"");
				break;
			case IDC_BUTTON_EDIT:
				if (index != -1)
				{
					hwndList = GetDlgItem(hDlg, IDC_LIST_CONTROL);
					GetDlgItemTextW(hDlg, IDC_EDIT_EDIT, str, 255);
					SendMessage(hwndList, LB_DELETESTRING, index, 0);
					wcscpy_s(elems[index].name, str);
					print(hwndList, elems[index], LB_INSERTSTRING, index);
					SetDlgItemTextW(hDlg, IDC_EDIT_EDIT, L"");
					index = -1;
				}
				break;
			case IDC_RADIO_LIST:
				hwndList = GetDlgItem(hDlg, IDC_LIST_CONTROL);
				{
					DWORD dwStyle = GetWindowLong(hwndList, GWL_STYLE);
					if ((dwStyle & LVS_TYPEMASK) != LV_VIEW_LIST)
						SetWindowLong(hwndList, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | LV_VIEW_LIST);
				}
				break;
			case IDC_RADIO_DETAILS:
				hwndList = GetDlgItem(hDlg, IDC_LIST_CONTROL);
				{
					DWORD dwStyle = GetWindowLong(hwndList, GWL_STYLE);
					if ((dwStyle & LVS_TYPEMASK) != LV_VIEW_DETAILS)
						SetWindowLong(hwndList, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | LV_VIEW_DETAILS);
				}
				break;
			case IDC_RADIO_TILE:
				hwndList = GetDlgItem(hDlg, IDC_LIST_CONTROL);
				{
					DWORD dwStyle = GetWindowLong(hwndList, GWL_STYLE);
					if ((dwStyle & LVS_TYPEMASK) != LV_VIEW_TILE)
						SetWindowLong(hwndList, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | LV_VIEW_TILE);
				}
				break;
			case IDC_RADIO_ICON:
				hwndList = GetDlgItem(hDlg, IDC_LIST_CONTROL);
				{
					DWORD dwStyle = GetWindowLong(hwndList, GWL_STYLE);
					if ((dwStyle & LVS_TYPEMASK) != LV_VIEW_ICON)
						SetWindowLong(hwndList, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | LV_VIEW_ICON);
				}
				break;
			/*case IDC_LIST_CONTROL:
				switch (LOWORD(wParam))
				{
				case LVN_ODSTATECHANGED:
					hwndList = GetDlgItem(hDlg, IDC_LIST_CONTROL);
					for (int i = 0; i < SendMessage(hwndList, LB_GETCOUNT, 0, 0); i++)
					{
						if (SendMessage(hwndList, LB_GETSEL, i, 0) > 0)
						{
							index = i;
							break;
						}
					}
					if (index != -1)
					{
						wcscpy_s(str, elems[index].name);
					}
					SetDlgItemTextW(hDlg, IDC_EDIT_EDIT, str);
					break;
				}
				break;*/
			case IDC_BUTTON_EXIT:
				DestroyWindow(hDlg);
				break;
			}
			break;
		case WM_NOTIFY:
			switch (LOWORD(wParam))
			{
				case IDC_LIST_CONTROL:
					switch (LOWORD(wParam))
					{
					case LVM_GETSELECTIONMARK:
						hwndList = GetDlgItem(hDlg, IDC_LIST_CONTROL);
						for (int i = 0; i < SendMessage(hwndList, LB_GETCOUNT, 0, 0); i++)
						{
							if (SendMessage(hwndList, LB_GETSEL, i, 0) > 0)
							{
								index = i;
								break;
							}
						}
						if (index != -1)
						{
							wcscpy_s(str, elems[index].name);
						}
						SetDlgItemTextW(hDlg, IDC_EDIT_EDIT, str);
						break;
					}
					default:
						x = LOWORD(wParam);
						break;
					break;
			}
			break;
		case WM_CLOSE:
			DestroyWindow(hDlg);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		
    return 0;
}