/*
* ����ģ��֮��Ϣѡ��ģ��
* ԭ����:
* ���׽��ֺʹ��ڰ󶨵�һ��, ���׽��ֳ����ض��¼���ʱ��, ϵͳ���Զ�������Ϣ������.
*/


// ���붨�������, �������������ʹ����Ϣѡ��ģ��
#define _WINSOCK_DEPRECATED_NO_WARNINGS



#include "resource.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <Commctrl.h>
#pragma comment(lib,"Comctl32.lib")



#define UM_NETEVENT 0x1000  // �û��Զ�����Ϣ : �����¼�����Ϣ


class NetClient;
SOCKET              g_hServer = NULL; // ����˾��

// ��Ӧ�Ի����ʼ��
void                OnInitDialog(HWND hWnd);
// ��Ӧ�׽��ֵ���Ϣ
void                OnSocketMessage(HWND hWnd, WPARAM wParam, LPARAM lParam);
// �Ի���ص�����
INT_PTR CALLBACK    DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
}



INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {

	case WM_INITDIALOG:
		OnInitDialog(hWnd);
		break;
	case  WM_CLOSE:
		EndDialog(hWnd, 0);
		// �����׽��ֿؼ�
		WSACleanup();
		break;

	case UM_NETEVENT: // �Զ���������¼���Ϣ
		OnSocketMessage(hWnd, wParam, lParam);
		break;

	default: return FALSE;
		break;
	}

	return TRUE;
}

void OnInitDialog(HWND hWnd)
{
	InitCommonControls(); // ��ʼ��ͨ�ÿؼ�

	// ��ʼ��list�ؼ�
	HWND hList = GetDlgItem(hWnd, IDC_LIST1);
	LV_COLUMN lc = { 0 };
	lc.mask = LVCF_TEXT | LVCF_WIDTH;
	lc.pszText = L"������Ϣ";
	lc.cx = 480;
	ListView_InsertColumn(hList, 0, &lc);

	// 1. ��ʼ���׽���
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	//1. ��������˵���ʽTCP�׽���
	g_hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	//2. ���׽���
	sockaddr_in serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons((short)1234);
	InetPtonA(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // ���ַ�����IPת��������
	// 2.1 ���׽��ֵ���ַ�Ͷ˿���
	bind(g_hServer, (sockaddr*)&serverAddr, sizeof(serverAddr));


	// 3. �����׽���
	listen(g_hServer, SOMAXCONN);


	// 4. �����ں��׽��ֽ��й���
	WSAAsyncSelect(g_hServer,     // Ҫ�ʹ��ڹ������׽���
		hWnd,          // Ҫ���׽��ֹ����Ĵ���
		UM_NETEVENT,   // ���׽��ֲ��������¼�ʱ, ���ڻ�ӵ�����Ϣ(�Զ���,��ɶ����,�����ܺ�������Ϣ�ظ�)
		FD_ACCEPT | FD_CLOSE  // ʲô���������¼��������Ϣ.
		);

	//5. �ڴ��ڻص������еȴ������¼�����Ϣ������.

}




// ���������¼�����Ϣ������
void OnSocketMessage(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// wParam �����Ų��������¼����׽��־��
	// lParam 
	//      ��16λ : ���������¼���
	//      ��16λ : ���������

	DWORD   dwNetEventCode = LOWORD(lParam);


	switch (dwNetEventCode) {

	case FD_ACCEPT: // �������������¼�,�пͻ������ӽ���
	{
						// �����ӽ������¿ͻ��˵��׽��ֺͱ����ڽ��й���,
						// ��ѡ���������׽��ֵ����ݷ��͹���ʱ���׽��ֱ��ر�ʱ�������¼�
						sockaddr_in clientAdddr = { 0 };
						int nSize = sizeof(clientAdddr);
						SOCKET  hClient = accept(g_hServer, (sockaddr*)&clientAdddr, &nSize);

						WSAAsyncSelect(hClient,
							hWnd,
							UM_NETEVENT,
							FD_READ | FD_CLOSE);
	}
		break;

	case FD_READ:  // �����ݱ����͹���
	{

					   SOCKET  hClientScoket = (SOCKET)wParam;

					   // ��������
					   char data[20];
					   recv(hClientScoket, data, sizeof(data), 0);

					   // �������ݸ��ͻ���
					   send(hClientScoket, "�յ�", 5, 0);


					   // ת���ɿ��ַ�Ȼ����뵽list�ؼ�.
					   TCHAR szBuff[20];
					   MultiByteToWideChar(CP_ACP, 0, data, -1, szBuff, 20);

					   // �����ݲ��뵽list�ؼ�
					   LVITEM li = { 0 };
					   li.mask = LVIF_TEXT;
					   li.pszText = szBuff;
					   ListView_InsertItem(GetDlgItem(hWnd, IDC_LIST1), &li);
	}
		break;


	case FD_CLOSE: // ���׽��ֱ��ر�
	{
					   // �ر��׽���
					   closesocket((SOCKET)wParam);
	}
		break;
	}
}

