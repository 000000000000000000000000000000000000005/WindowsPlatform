#include <windows.h>
#include <tchar.h>
#include   <stdarg.h>  
#include <Shlwapi.h>
#pragma  comment(lib, "Shlwapi.lib")

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	);

BOOL CALLBACK EnumChildProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
	);

void PrintDbgInfo(LPCTSTR lptstrFormat, ...);

//////////////////////////////////////////////
HINSTANCE g_hIntance = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_hIntance = hInstance;
	//1. ����������
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;

	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = _T("��һ��������");

	//2. ע�ᴰ��
	RegisterClassEx(&wcex);

	//3.��������
	HWND hWnd = CreateWindow(_T("��һ��������"),
		_T("�ҵĵ�һ������"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL,
		NULL,
		hInstance,
		NULL);

	//4. ��ʾˢ�´���
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	//5.��Ϣѭ��
	MSG msg = { 0 };
	while (GetMessage(&msg, 0, 0, 0))
	{
		//
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//6. �˳�ѭ��
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	)
{
	/*
	1. �Լ�����Ϣ
	2. �ӿؼ�����Ϣ WM_COMMAND(�򵥿ؼ� ��ť��˵�) WM_NOTIFY(list tree�ȸ��ӿؼ�)
	*/
	switch (uMsg)
	{
	case WM_CREATE:
	{
					  //���ڳ��򴴽���Ϣ˳��:
					  //WM_CREATE -> WM_SHOW
					  CreateWindow(_T("BUTTON"), _T("�ҵĵ�һ����ť"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 100, 30, hwnd, (HMENU)0X100, g_hIntance, NULL);
					  CreateWindow(_T("BUTTON"), _T("�ҵĵڶ�����ť"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 31, 100, 30, hwnd, (HMENU)0X101, g_hIntance, NULL);
	}
		break;
	case WM_QUIT:  //�������ڻص������н��յ�
	{
					   PrintDbgInfo(_T("uMsg:0x%X    wParam:0x%X  lParam:0x%X\n"), uMsg, wParam, lParam);
	}
		break;
	case WM_CLOSE:
	{
					 //�����������:
					 //WM_CLOSE -> WM_DESTORY -> WM_QUIT(WM_QUIT���ᱻ���յ�)
					 PostQuitMessage(0);
	}
		break;

	case WM_COMMAND:
	{
					   //The LOWORD contains the button's control identifier. The HIWORD specifies the notification code.
					   WORD wCtlID = LOWORD(wParam);
					   WORD wNotifyCode = HIWORD(wParam);
					   switch (wNotifyCode)
					   {
					   case BN_CLICKED:
					   {
										  switch (wCtlID)
										  {
										  case 0X100:
										  {
														MessageBox(hwnd, _T("��һ����ť"), _T("��ʾ"), MB_OK);
										  }
											  break;
										  case 0x101:
										  {
														//��һ�֣��ʺϲ��Ҷ��㴰�ھ��
														HWND hCalc = FindWindow(NULL,_T("������"));
														if (hCalc == NULL)
														{
															WinExec("calc", SW_SHOW);
															Sleep(500);
															hCalc = FindWindow(NULL, _T("������"));
														}
														PrintDbgInfo(_T("��������������0x%X"), hCalc);

														//�ڶ��֣���֪һ����������������صĵľ��
														HWND hChild = GetWindow(hCalc, GW_CHILD);
														PrintDbgInfo(_T("����������ؾ����0x%X"), hChild);

														//�����֣���֪һ�������Ƶ������GetWindow��ʱ��
														HWND hFind = 0;
														EnumChildWindows(hChild, EnumChildProc, (LPARAM)&hFind);

														//�����֣���֪�����ڵľ����ͨ���ؼ�id��ȡ���
														HWND hButton1 = GetDlgItem(hwnd, 0X100);
														PrintDbgInfo(_T("��ť1�ľ����0x%X"), hButton1);
										  }
											  break;
										  default:
											  break;
										  }
					   }
						   break;
					   default:
						   break;
					   }

	}
		break;
	case WM_PAINT:
	{
					 PAINTSTRUCT ps = { 0 };
					 HDC hDc = BeginPaint(hwnd, &ps);
					 TextOut(hDc, 100, 100, _T("15pb"), 4);
					 EndPaint(hwnd, &ps);

	}
		break;

	default:
		break;
	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


BOOL CALLBACK EnumChildProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
)
{
	TCHAR szTextBuff[MAX_PATH];
	TCHAR szClassNameBuff[MAX_PATH];
	GetWindowText(hwnd, szTextBuff, _countof(szTextBuff) - 1);
	GetClassName(hwnd, szClassNameBuff, _countof(szClassNameBuff) - 1);
	PrintDbgInfo(_T("����ľ����0x%X �����������%s  ���������: %s"), hwnd, szClassNameBuff, szTextBuff);
	return true;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ���ַ�ת��Ϊ���ַ�(Unicode  --> ASCII)
#define  WCHAR_TO_CHAR(lpW_Char, lpChar) \
	WideCharToMultiByte(CP_ACP, NULL, lpW_Char, -1, lpChar, _countof(lpChar), NULL, FALSE);

// ���ַ�ת��Ϊ���ַ�(ASCII --> Unicode)
#define  CHAR_TO_WCHAR(lpChar, lpW_Char) \
	MultiByteToWideChar(CP_ACP, NULL, lpChar, -1, lpW_Char, _countof(lpW_Char));

//��ʽ�������Ϣ�ַ��������������
void SprintfDbgInfo(TCHAR *pOutBuff, int nMaxOutBuffSize, LPCTSTR lptstrFormat, va_list argList)
{
	//
	const int nFileBuffSize = 256;
	TCHAR fileNameBuff[nFileBuffSize];

	//�����ļ������к�
#ifdef UNICODE
	CHAR_TO_WCHAR(__FILE__, fileNameBuff);
	TCHAR *pFileName = PathFindFileName(fileNameBuff);
	_stprintf_s(pOutBuff, nMaxOutBuffSize - sizeof(TCHAR), _T("[mod:%s:line:%d]  ::  "), pFileName, __LINE__);
#else
	_tcscpy_s(fileNameBuff, __FILE__);
	TCHAR *pFileName = PathFindFileName(fileNameBuff);
	_stprintf_s(pOutBuff, nMaxOutBuffSize - sizeof(TCHAR), _T("[mod:%s:line:%d]  ::"), pFileName, __LINE__);
#endif

	//����������Ϣ
	int nHeadLen = _tcslen(pOutBuff);
	_vstprintf_s(pOutBuff + nHeadLen, nMaxOutBuffSize - sizeof(TCHAR)-nHeadLen * sizeof(TCHAR), lptstrFormat, argList);

	//���û���
	int nBodyLen = _tcslen(pOutBuff);
	_stprintf_s(pOutBuff + nBodyLen, nMaxOutBuffSize - sizeof(TCHAR)-nBodyLen * sizeof(TCHAR), _T("\r\n"));
}

//��ӡ��������Ϣ
void PrintDbgInfo(LPCTSTR lptstrFormat, ...)
{
	const int c_nMaxBuffSize = 4096;
	TCHAR outBuff[c_nMaxBuffSize];

	//�ѽ�������������
	va_list argList;
	va_start(argList, lptstrFormat);
	SprintfDbgInfo(outBuff, c_nMaxBuffSize, lptstrFormat, argList);
	va_end(argList);

	//�����Ϣ
	OutputDebugString(outBuff);
}
