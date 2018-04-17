#include <windows.h>
#include <tchar.h>
#include "Dbg.h"
#include "resource.h"

/*
	һ�������ػ�ʱ����
	1. �ı䴰�ڴ�С�ı䣬  ���ڱ�����������ʾ
	2. ������������Ҫ���»���  => InvalidateRect

	����WM_PAINT��Ϣ�����ȼ����ϲ���

	���������ǵĴ�����Ҫ���������ػ�(�Լ��ܽ�ó����ģ����ֱ����ǵĴ������û�л�ȡ�������ǲ��ᴥ��WM_PAINT��)

	�ģ�����BeginPaint��EndPaint
	1. BeginPaint����ʹ��Ч��������Ч����ϵͳ���ٷ���WM_PAINT��Ϣ
	2. ִ�л��Ʋ����ͷ�dc
	3. �����WM_PAINT��Ϣ��ȥ��BeginPaint��EndPaint���ᵼ����Ч����һֱ��Ч��ϵͳ���ϵķ���paint��Ϣ�ᵼ�³�����
'*/


/*
	��ȡdc�ķ�ʽ��===>����ͨ����ť��Ϣ��һ����ʵ��
	1.  BeginPaint��ȡ EndPaint�ͷ�->ֻ������WM_PAINT��Ϣ��
	2.  GetDC��ȡReleaseDC�ͷ�->�κεط������� ��ȡ��,ȱ����ֻ�ܻ�ȡ�ͻ�����dc�����ܻ��Ʊ�����
	3.  GetWindowDC & ReleaseDC->�κεط������Ի�ȡ�����Ի��Ʊ������� ��Ҫ����WM_NCPAINT��Ϣ����Ȼ�ᱻ����
	4. CreateDC��ȡDeleteDC-> ���Ի�ȡ��Ĵ�������dc
*/

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
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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

	case WM_NCPAINT:  //GetWindowDC & ReleaseDC->�κεط������Ի�ȡ�����Ի��Ʊ���
	{
					   return 1;
	}
		break;

	case WM_COMMAND:
	{
					   //The LOWORD contains the button's control identifier. The HIWORD specifies the notification code.
					   WORD wCtlID = LOWORD(wParam);
					   WORD wNotifyCode = HIWORD(wParam);

					   switch (wCtlID)
					   {
					   case ID_40002:  //�ƶ���Ч����
					   {
										   RECT rect;
										   GetClientRect(hwnd, &rect);
										   //�������ͻ�������Ч
										   InvalidateRect(hwnd, &rect, FALSE);
					   }
						   break;
					   case ID_40003:  //GetDC��ȡReleaseDC�ͷ�->�κεط������� ��ȡ��, ȱ����ֻ�ܻ�ȡ�ͻ�����dc�����ܻ��Ʊ�����
					   {
										   HDC hDc = GetDC(hwnd);
										   TextOut(hDc, 0, 0, _T("�����getdc"), _tcslen(_T("�����getdc")));
										   ReleaseDC(hwnd, hDc);
					   }
						   break;
					   case ID_40004:  // GetWindowDC & ReleaseDC->�κεط������Ի�ȡ�����Ի��Ʊ���, ��Ҫ����WM_NCPAINT��Ϣ
					   {
										   PrintDbgInfo(_T("get window dc"));
										   HDC hDc =  GetWindowDC(hwnd);
										   TextOut(hDc, 0, 0, _T("�����GetWindowDC"), _tcslen(_T("�����GetWindowDC")));
										   ReleaseDC(hwnd, hDc);
					   }
						   break;
					   case ID_40005: //CreateDC��ȡDeleteDC-> ���Ի�ȡ��Ĵ�������dc
					   {
										  // ����DC
										  HDC hDesktop = CreateDC(L"DISPLAY", NULL, NULL, NULL);
										  TextOut(hDesktop, 0, 0, _T("�����CreateDC"), _tcslen(_T("�����CreateDC")));
										  DeleteDC(hDesktop);
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

					 //���ÿͻ����ı�����ɫ
					 HBRUSH hBsh = CreateSolidBrush(RGB(0, 255, 0));
					 RECT rt;
					 GetClientRect(hwnd, &rt);
					 FillRect(hDc, &rt, hBsh);

					 TextOut(hDc, 100, 100, _T("�����ñ������ֱ���ɫ��֮ǰ"), _tcslen(_T("�����ñ������ֱ���ɫ֮ǰ")));
					 //����������ֵı���ɫΪ͸������Ȼ���ѿ�
					 SetBkMode(hDc, TRANSPARENT);
					 //�������
					 SetTextColor(hDc, RGB(0xff, 0, 0));
					 TextOut(hDc, 100, 120, _T("�����ñ������ֱ���ɫ��֮��"), _tcslen(_T("�����ñ������ֱ���ɫ֮��")));
					 EndPaint(hwnd, &ps);

	}
		break;

	default:
		break;
	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}