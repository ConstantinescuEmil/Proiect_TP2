#include <windows.h>

#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_MAIN_EDIT	102			// Edit box identifier
#define IDC_MAIN_BUTTON2 103
HWND hEdit;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hIcon = NULL;
	wClass.hIconSm = NULL;
	wClass.hInstance = hInst;
	wClass.lpfnWndProc = (WNDPROC)WinProc;
	wClass.lpszClassName = "Window Class";
	wClass.lpszMenuName = NULL;
	wClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wClass))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			"Window class creation failed\r\n",
			"Window Class Failed",
			MB_ICONERROR);
	}

	HWND hWnd = CreateWindowEx(NULL,
		"Window Class",
		"Compresor Golomb",
		WS_OVERLAPPEDWINDOW,
		200,
		200,
		400,
		400,
		NULL,
		NULL,
		hInst,
		NULL);

	if (!hWnd)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			"Window creation failed\r\n",
			"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(hWnd, nShowCmd);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
			
					HWND statik=  CreateWindowEx(0,
						  "STATIC",
						  NULL,
						  WS_CHILD | WS_VISIBLE,
						  60, 10, 300, 200,
						  hWnd,
						  NULL,
						 NULL,
						  NULL);
					
					SetWindowText(
						 statik,
						 "Introduceti textul si alegeti modul dorit"
						);



					  // Create an edit box
					  hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
						  "EDIT",
						  "",
						  WS_CHILD | WS_VISIBLE |
						  ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
						 40,
						  80,
						 300 ,
						  200,
						  hWnd,
						  (HMENU)IDC_MAIN_EDIT,
						  GetModuleHandle(NULL),
						  NULL);
					  HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);
					  SendMessage(hEdit,
						  WM_SETFONT,
						  (WPARAM)hfDefault,
						  MAKELPARAM(FALSE, 0));
					  SendMessage(hEdit,
						  WM_SETTEXT,
						  NULL,
						  (LPARAM)"");

					  // Create a push button
					  HWND hWndButton = CreateWindowEx(NULL,
						  "BUTTON",
						  "CRIPTEAZA",
						  WS_TABSTOP | WS_VISIBLE |
						  WS_CHILD | BS_DEFPUSHBUTTON,
						  40,
						  300,
						  120,
						  40,
						  hWnd,
						  (HMENU)IDC_MAIN_BUTTON,
						  GetModuleHandle(NULL),
						  NULL);
					  SendMessage(hWndButton,
						  WM_SETFONT,
						  (WPARAM)hfDefault,
						  MAKELPARAM(FALSE, 0));


					  HWND hWndButton2 = CreateWindowEx(NULL,
						  "BUTTON",
						  "DECRIPTEAZA",
						  WS_TABSTOP | WS_VISIBLE |
						  WS_CHILD | BS_DEFPUSHBUTTON,
						  220,
						  300,
						  120,
						  40,
						  hWnd,
						  (HMENU)IDC_MAIN_BUTTON2,
						  GetModuleHandle(NULL),
						  NULL);
					  SendMessage(hWndButton2,
						  WM_SETFONT,
						  (WPARAM)hfDefault,
						  MAKELPARAM(FALSE, 0));
	}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_MAIN_BUTTON:
		{
								char buffer[256];
								SendMessage(hEdit,
									WM_GETTEXT,
									sizeof(buffer) / sizeof(buffer[0]),
									reinterpret_cast<LPARAM>(buffer));
								MessageBox(NULL,
									buffer,
									"Information",
									MB_ICONINFORMATION);
								break;
		}


		case IDC_MAIN_BUTTON2:
		{
								char buffer2[256];
								SendMessage(hEdit,
									WM_GETTEXT,
									sizeof(buffer2) / sizeof(buffer2[0]),
									reinterpret_cast<LPARAM>(buffer2));
								MessageBox(NULL,
									buffer2,
									"Information",
									MB_ICONINFORMATION);
								break;
								
		}



			break;
		}
		break;

	case WM_DESTROY:
	{
					   PostQuitMessage(0);
					   return 0;
	}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}