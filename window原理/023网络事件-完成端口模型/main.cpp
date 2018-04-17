/*
* ��ɶ˿ڷ�Ϊ������
* ��һ����:
*  ���߳�waitClientAccept����, ��Ҫ������������:
*  1. ���ܿͻ��˽���
*  2. Ϊ�ͻ���Ͷ�ݽ������ݵ�IO������ɶ˿���
*
* �ڶ�����:
*  ���߳�waitNetworkIOProc����, ��Ҫ������������:
*  1. ����GetQueuedCompletionStatus�ȴ���һ���ֵ�2��Ͷ�ݵ�IO�������.
*  2. �����Ѿ���ɵ�IO��������������������.
*
* ��main������, ����������׼��,��Щ׼������:
*  1. ����������׽���, ���û�з�����׽���,��һ���ֵĵ�һ���޷���ɽ��տͻ����׽���.
*  2. ������ɶ˿�
*  3. Ϊ��ɶ˿ڴ��������߳�:waitNetworkIOProc
*  4. Ϊ�ȴ��ͻ������Ӵ����߳�:waitClientAccept
*/

#include "NetWorkOverlappedRecv.h"
#include <process.h>
#include <stdio.h>


// ��չOVERLAPPED�ṹ��, ���ڱ���WSARecvͶ�ݵ�IO�������Ϣ
//class NetWorkOverlappedRecv;

SOCKET g_hServer;
HANDLE g_hIocp;

// �ȴ��ͻ������ӵĻص�����
unsigned int CALLBACK waitClientAccept(void *pArg);


// �ȴ��¼����̻߳ص�����
unsigned int CALLBACK waitNetworkIOProc(void *pArg);


int main()
{
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


	// 4. ������ɶ˿�
	SYSTEM_INFO si = { sizeof(SYSTEM_INFO) };
	GetSystemInfo(&si);
	g_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
		NULL,
		NULL,
		si.dwNumberOfProcessors);

	// 5. ���׽��ֺ���ɶ˿ڽ��а�
	CreateIoCompletionPort((HANDLE)g_hServer,
		g_hIocp,
		0,
		si.dwNumberOfProcessors
		);


	// 6. ������ɶ˿ڵĹ����߳�
	for (unsigned int i = 0; i < si.dwNumberOfProcessors * 2; ++i) {

		_beginthreadex(0, 0, waitNetworkIOProc, 0, 0, 0);
	}



	// �����ȴ��ͻ��˽�����߳�
	HANDLE hThread = (HANDLE)_beginthreadex(0, 0, waitClientAccept, 0, 0, 0);

	WaitForSingleObject(hThread, -1);
	return 0;
}


// �ȴ��ͻ������ӵĻص�����
unsigned int CALLBACK waitClientAccept(void *pArg)
{

	SOCKET          hClient = NULL;
	sockaddr_in     clientAddr = { 0 };
	int             nSizeOfAddr = sizeof(clientAddr);

	while (true) {

		// 1. ���տͻ��˵�����
		hClient = accept(g_hServer, (sockaddr*)&clientAddr, &nSizeOfAddr);

		// 1.1 ���ͻ����׽��ֺ���ɶ˿ڽ��а���һ��
		CreateIoCompletionPort((HANDLE)hClient,
			g_hIocp,
			0,
			0);

		//2 Ϊ�½���Ŀͻ���Ͷ���첽��������(������񽫻�����ɶ˿ڵĵȴ��߳�ȥ�ȴ�)

		//2.1 ����OVERLAPPED�ṹ��
		NetWorkOverlappedRecv *pOver = new NetWorkOverlappedRecv;

		pOver->m_hSocket = hClient; // �����¿ͻ����׽���
		memcpy(&pOver->m_sockAddress, &clientAddr, sizeof(clientAddr)); // �����¿ͻ��˵�ַ

		pOver->m_buff.len = 20;     // ����IO������ֽ���
		pOver->m_buff.buf = new CHAR[20]; // ����ؼ�,���ڱ�����յ�������
		pOver->m_netWorkEvent = e_recv; // �˴�IO����������¼�����


		// 2.2 Ͷ��IO����
		int     nRet = 0;
		DWORD   dwRecvSize = 0;
		DWORD   dwFlag = 0;

		WSARecv(hClient,           // �ͻ����׽���
			&pOver->m_buff,    // �û�������յ�������
			1,                 // ���յ����ֽ���
			&dwRecvSize,       // ʵ�ʽ��յ����ֽ���(��Ȼ��������Ч,��������Ҫ����)
			&dwFlag,          // ��־
			pOver,             // �ص�IO�ṹ
			NULL                // ��ɺ���(��ʹ��)
			);



		// IP��ַת�ַ���
		char szIpAddress[20];
		InetNtopA(AF_INET, &clientAddr.sin_addr, szIpAddress, 20);
		printf("IP:[%s] ����\n", szIpAddress);

	}

}



// �ȴ�IO������ɵĺ���
unsigned int CALLBACK waitNetworkIOProc(void *pArg)
{
	DWORD   dwSize = 0;
	DWORD   dwIoKey = 0;
	BOOL    bRet = FALSE;
	NetWorkOverlappedRecv* pOver = NULL;

	while (true)
	{
		bRet = GetQueuedCompletionStatus(g_hIocp, // ��ɶ˿ھ��
			&dwSize,// IO������ɵ��ֽ���
			&dwIoKey,// ��ɼ�(�����ﲢû��ʹ�õ�)
			(OVERLAPPED**)&pOver,// �ص�IO�ṹ,������������Ѿ���չ���ص�IO�ṹ
			-1
			);
		if (bRet == FALSE)
			continue;

		// ����¼���һ���Զ����ö������
		// ���ö�����͵�ֵ��Ͷ��IO�����ʱ����г�ʼ����
		// ����,����WSARecv��ʱ��, ���ֵ�ͱ���e_recv����ֵ
		switch (pOver->m_netWorkEvent) {

		case e_recv:  // 
		{
						  // IP��ַת�ַ���
						  char szIpAddress[20];
						  InetNtopA(AF_INET, &pOver->m_sockAddress.sin_addr, szIpAddress, 20);

						  printf("IP[%s] : [%s]\n", szIpAddress, pOver->m_buff.buf);

						  char* pSend = { "�����Ѿ��յ�" };
						  send(pOver->m_hSocket, pSend, strlen(pSend) + 1, 0);



						  // ����Ͷ��IO����, �����Ͷ��, ����һ�οͻ��˷������ݹ���ʱ,
						  // ��ɶ˿ڻ���Ϊ�ڲ��Ѿ�û��IO����������������κ���Ӧ,�����
						  // �Ͳ����ٽ���������, �������Ӧ�ý��ն����ֽ�, ���Ը��ݿͻ���
						  // ���������������������ж�̬����.
						  DWORD dwRecvSize = 0;
						  DWORD dwFlag = 0;
						  WSARecv(pOver->m_hSocket,
							  &pOver->m_buff,
							  pOver->m_buff.len,
							  &dwRecvSize,
							  &dwFlag,
							  pOver,
							  NULL
							  );
		}
			break;
		}

	}
}
