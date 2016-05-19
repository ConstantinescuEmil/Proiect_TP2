#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"declarare_functii.h"
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

BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR pszFileName)
{
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLength;

		dwTextLength = GetWindowTextLength(hEdit);
		// No need to bother if there's no text.
		if (dwTextLength > 0)
		{
			LPSTR pszText;
			DWORD dwBufferSize = dwTextLength + 1;

			pszText = (LPSTR)GlobalAlloc(GPTR, dwBufferSize);
			if (pszText != NULL)
			{
				if (GetWindowText(hEdit, pszText, dwBufferSize))
				{
					DWORD dwWritten;

					if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
						bSuccess = TRUE;
				}
				GlobalFree(pszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
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
								char buffer[25600];
								char bufferfin[25600];
								char lit[2];
								lit[1] = '\0';
								bufferfin[0] = '\0';
								SendMessage(hEdit,
									WM_GETTEXT,
									sizeof(buffer) / sizeof(buffer[0]),
									reinterpret_cast<LPARAM>(buffer));
								FILE*A;
								A = fopen("temp.txt", "w");
								for (int i = 0; i < strlen(buffer); i++)
								{
									fprintf(A,"%c", buffer[i]);
								}
								fclose(A);



								int* v = NULL;
								int* rem = NULL;
								int* descris = NULL;
								int* decode = NULL;
								int i, j = 0;
								unsigned char c = char(1), b;
								A = fopen("temp.txt", "rb");
								FILE*B = fopen("out.txt", "wb");
								while (fread(&c, sizeof(unsigned char), 1, A))
								{
									v = encrypt(c, 3);
									concat(&rem, &v);
									descris = impartire(v, &rem);
									while (descris[0]>1)
									{

										b = char_codat(&descris);
										//fwrite(&b, sizeof(unsigned char), 1, B);
										lit[0] = b;
										strcat(bufferfin, lit);

									}
									free(descris);
								}
								restfin(&rem);
								b = char_codat(&rem);
								//fwrite(&b, sizeof(unsigned char), 1, B);
								lit[0] = b;
								strcat(bufferfin, lit);
								fclose(B);
								fclose(A);
								remove("temp.txt");
								free(rem);

								OPENFILENAME ofn;
								char szFileName[MAX_PATH] = "";

								ZeroMemory(&ofn, sizeof(ofn));

								ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
								ofn.hwndOwner = hWnd;
								ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
								ofn.lpstrFile = szFileName;
								ofn.nMaxFile = MAX_PATH;
								ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
								ofn.lpstrDefExt = "txt";

								if (GetOpenFileName(&ofn))
								{
									B = fopen(szFileName, "wb");
									for (i = 0; i < strlen(bufferfin); i++)
									{
										
										fwrite(&(bufferfin[i]), sizeof(unsigned char), 1, B);
									}

								}


								break;
		}


		case IDC_MAIN_BUTTON2:
		{
								char buffer2[25600];
								SendMessage(hEdit,
									WM_GETTEXT,
									sizeof(buffer2) / sizeof(buffer2[0]),
									reinterpret_cast<LPARAM>(buffer2));
								MessageBox(NULL,
									buffer2,
									"Information",
									MB_ICONINFORMATION);
								FILE*A;
								A = fopen("temp.txt", "w");
								for (int i = 0; i < strlen(buffer2); i++)
								{
									fprintf(A, "%c", buffer2[i]);
								}
								fclose(A);


								int* v = NULL;
								int* rem = NULL;
								int* descris = NULL;
								int* decode = NULL;
								int i, j = 0;
								unsigned char c = char(1), b;
								A = fopen("temp.txt", "rb");
								FILE*B = fopen("encode.txt", "wb");
								v = NULL;
								while (c != unsigned char(0))
								{
									decode = (int*)malloc(sizeof(int));
									decode[0] = 1;
									concat(&rem, &decode);
									while (verif_ok(decode, 3) == 0)
									{


										if (fread(&c, sizeof(unsigned char), 1, A))
										{
											if (verif_ok(decode, 3) == 0)
											{
												v = obt_vct_codat(c);
												bag_vect_la_sf(&decode, v);
											}

										}
										else { c = unsigned char(0); break; }
									}
									while (verif_ok(decode, 3) == 1 && (!rest0(decode)))
									{
										b = obt_char(decode, 3);
										fwrite(&b, sizeof(unsigned char), 1, B);
										scindare(&decode, 3);
										if (rest0(decode))c = unsigned char(0);
									}
									rem = (int*)malloc(sizeof(int));
									rem[0] = 1;
									concat(&decode, &rem);
								}
								fclose(A);
								remove("temp.txt");
								fclose(B);



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