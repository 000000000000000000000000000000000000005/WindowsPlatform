#include <windows.h>
#include <tchar.h>

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
	wcex.lpszClassName = _T("copy data ����");

	//2. ע�ᴰ��
	RegisterClassEx(&wcex);

	//3.��������
	HWND hWnd = CreateWindow(_T("copy data ����"),
		_T("copy data ����"),
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
	case WM_CLOSE:
	{
					 //�����������:
					 //WM_CLOSE -> WM_DESTORY -> WM_QUIT(WM_QUIT���ᱻ���յ�)
					 PostQuitMessage(0);
	}
	case WM_COPYDATA:
	{
						COPYDATASTRUCT *pCopyData = (COPYDATASTRUCT*)lParam;
						MessageBox(hwnd, (TCHAR*)pCopyData->lpData, _T("����WM_COPYDATA"), MB_OK);
	}
		break;

	default:
		break;
	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}