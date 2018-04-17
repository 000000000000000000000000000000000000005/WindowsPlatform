#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include <process.h>
#include <cstdio>

HANDLE      g_hEvent[64] = { 0 }; // ����ͻ����׽��ֵ�����
SOCKET      g_hSocket[64] = { 0 };// �������е��׽���(����˱����ڵ�0��,ʣ�µĶ�����ͻ���)
DWORD       g_nEventCount = 0;      // ��ǰ�ͻ��˸���
sockaddr_in g_clientAddr[64];       // �ͻ��˵�ַ

// �ȴ������¼����߳�
unsigned int CALLBACK waitNetEvent(void *pArg);

int main()
{
	// 1. ��ʼ���׽���
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	//1. ��������˵���ʽTCP�׽���
	g_hSocket[0] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	//2. ���׽���
	sockaddr_in serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons((short)1234);
	InetPtonA(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // ���ַ�����IPת��������
	// 2.1 ���׽��ֵ���ַ�Ͷ˿���
	bind(g_hSocket[0], (sockaddr*)&serverAddr, sizeof(serverAddr));


	// 3. �����׽���
	listen(g_hSocket[0], SOMAXCONN);


	// 4. �����¼�����
	g_hEvent[0] = WSACreateEvent();
	g_nEventCount++;

	// 5. ���׽��ֺ��¼������������
	WSAEventSelect(g_hSocket[0],         // Ҫ���¼����ӵ��׽���
		g_hEvent[0],            // Ҫ���׽������ӵ��¼�
		FD_ACCEPT | FD_CLOSE// ע��ᴥ���¼�����������¼�,
		);


	// 6. ����һ���̵߳ȴ��¼����󱻴���
	HANDLE hThread = (HANDLE)_beginthreadex(0, 0, waitNetEvent, 0, 0, 0);

	// �ȴ��߳��˳�
	WaitForSingleObject(hThread, -1);

	return 0;
}

unsigned int CALLBACK waitNetEvent(void *pArg)
{

	DWORD               dwRet = 0;
	DWORD               dwIndex = 0;
	WSANETWORKEVENTS    netEvent;
	while (true)
	{

		// �ȴ��¼�����
		dwRet = WSAWaitForMultipleEvents(g_nEventCount,
			g_hEvent,
			FALSE,
			-1,
			TRUE
			);

		// �жϷ���ֵ�Ƿ���ȷ
		// ֻ�з���ֵ�� WSA_WAIT_EVENT_0  �� WSA_WAIT_EVENT_0 + 64 ֮�ڵ�ֵ������ȷ
		// ��Ϊ�ȴ��������ֻ�ܵȴ�64���¼�. �¼�������,�ͻ᷵���¼��������е����
		if (dwRet < WSA_WAIT_EVENT_0 || dwRet >= WSA_WAIT_EVENT_0 + 64) {
			continue;
		}

		// ���WSAWaitForMultipleEvents������������.
		// ˵��������ѵ�ȴ����¼�������������һ���¼����󱻼���.
		// ��ʱ, ���Ὣ�¼������������е���������.
		// �õ���ǰ���������¼������������е����
		dwIndex = dwRet - WSA_WAIT_EVENT_0;




		// ����ǰ���¼�������������ö�ٳ���
		// ����Ҫö�ٵ��׽���
		WSAEnumNetworkEvents(g_hSocket[dwIndex],    // �¼������Ӧ���׽��־��
			g_hEvent[dwIndex],     // Ҫ����ö�ٵ��¼�������
			&netEvent                 // ö�ٳ�����Ϣ
			);


		if (netEvent.lNetworkEvents & FD_ACCEPT) { // �����������¼�������

			// �¼�����������׽�����������±���64, ����, WSAEnumNetworkEventsֻ��
			// �ȴ�64�����ڵ��¼�����. ���, ���������64��,�Ͳ����ٴ�����
			if (g_nEventCount < 64) {


				// ���տͻ��˵�����
				int nSize = sizeof(sockaddr);
				// ���ͻ��˵�SOCKET���浽������
				g_hSocket[g_nEventCount] = accept(g_hSocket[0],
					(sockaddr*)&g_clientAddr[g_nEventCount],
					&nSize);


				// ����һ���¼�����. �����浽������
				// ���¼������������е��±�����׽������׽��������е��±�����ȵ�.
				g_hEvent[g_nEventCount] = WSACreateEvent();


				// ���µ��׽��ֺ��µ��¼�������й���
				WSAEventSelect(g_hSocket[g_nEventCount], // ���׽���
					g_hEvent[g_nEventCount],  // ���¼�����
					FD_READ | FD_CLOSE           // ע��Ҫ������·�¼�
					);


				// IP��ַת�ַ���
				char szIpAddress[20];
				InetNtopA(AF_INET, &g_clientAddr[g_nEventCount].sin_addr, szIpAddress, 20);
				printf("IP:[%s] ����\n", szIpAddress);



				// ���Ӽ���
				g_nEventCount++;
			}
		}

		// ��ȡ�¼�
		if (netEvent.lNetworkEvents & FD_READ) {

			// ��ȡ����
			char    buff[20];
			recv(g_hSocket[dwIndex], buff, 20, 0);

			char szIpAddress[20];
			InetNtopA(AF_INET, &g_clientAddr[dwIndex].sin_addr, szIpAddress, 20);

			printf("IP[%s] : [%s]\n", szIpAddress, buff);
		}

		// �ͻ��˹ر��¼�
		if (netEvent.lNetworkEvents & FD_CLOSE) {

			char szIpAddress[20];
			InetNtopA(AF_INET, &g_clientAddr[dwIndex].sin_addr, szIpAddress, 20);
			printf("IP[%s] ����\n", szIpAddress);

			// �ر��׽���
			closesocket(g_hSocket[dwIndex]);

			// ���Ѿ��ص����׽����������Ƴ�
			// �Ƴ�����:
			// ���׽��־��,�¼�������,�ͻ��˵�ַ������������ǰ�ƶ�
			// ���һ��(��63��)�����ƶ�.
			if (dwIndex < 63) {


				memmove(&g_hSocket[dwIndex],
					&g_hSocket[dwIndex + 1],
					(64 - dwIndex) * sizeof(g_hSocket[0])
					);

				memmove(&g_hEvent[dwIndex],
					&g_hEvent[dwIndex + 1],
					(64 - dwIndex) * sizeof(g_hEvent[0])
					);

				memmove(&g_clientAddr[dwIndex],
					&g_clientAddr[dwIndex + 1],
					(64 - dwIndex) * sizeof(g_clientAddr[0])
					);
			}

			// ���ټ���
			g_nEventCount--;
		}

	}
}