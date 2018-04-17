#include <windows.h>
#include <tchar.h>
#include "Dbg.h"

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	);


//////////////////////////////////////////////
HINSTANCE g_hIntance = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CreateDbgConsole();
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
	//���õ��Ժ�����ӡ����Ϣ
	PrintWindowsMsgInfo(hwnd, uMsg, wParam, lParam);
	switch (uMsg)
	{
	case WM_CREATE:
	{
					  //���ڳ��򴴽���Ϣ˳��:
					  //WM_CREATE -> WM_SHOW
					  CreateWindow(_T("BUTTON"), _T("�ҵĵ�һ����ť"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 100, 30, hwnd, (HMENU)0X100, g_hIntance, NULL);
					  CreateDbgConsole();
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