#include "MyOVERLAPPED.h"
#include <tchar.h>
#include <process.h>
#include <stdio.h>

// �ȴ���ɶ˿�֪ͨ���߳�
unsigned int __stdcall WaitComplePortNotify(void * pArg);

int main(int argc, char* argv[])
{
	HANDLE hFile = CreateFile(
		_T("main.cpp"),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL
		);

	if (hFile == INVALID_HANDLE_VALUE)
		return 0;

	SYSTEM_INFO si = { 0 };
	GetSystemInfo(&si);

	//������ɶ˿�
	HANDLE hComplePort = CreateIoCompletionPort(
		INVALID_HANDLE_VALUE,
		NULL,
		0,
		2 * si.dwNumberOfProcessors);

	//���ļ��������ɶ˿ڽ��й���
	CreateIoCompletionPort(
		hFile,
		hComplePort,
		0,
		0);

	// �����ȴ���ɶ˿�֪ͨ���߳�, ����ֻ����1���߳�,
	// Ϊ�˸��ߵ�Ч��, ���ﴴ����CPU����2�����߳�.
	for (unsigned int i = 0; i < si.dwNumberOfProcessors * 2; ++i)
		_beginthreadex(0, 0, WaitComplePortNotify, (void*)hComplePort, 0, 0);

	//////////////////////////////////////////////////////////////////////////
	// ��ʼͶ��IO����

	// ��ʼͶ��IO����
	MyOVERLAPPED *pOv1 = new MyOVERLAPPED(100, 0);
	pOv1->nIndex = 1;
	ReadFile(hFile, pOv1->pBuff, 100, NULL, pOv1);


	// ��ʼͶ��IO����
	MyOVERLAPPED *pOv2 = new MyOVERLAPPED(100, 200);
	pOv2->nIndex = 2;
	ReadFile(hFile, pOv2->pBuff, 100, NULL, pOv2);



	// ��ʼͶ��IO����
	MyOVERLAPPED *pOv3 = new MyOVERLAPPED(100, 400);
	pOv3->nIndex = 3;
	ReadFile(hFile, pOv3->pBuff, 100, NULL, pOv3);


	// ��ʼͶ��IO����
	MyOVERLAPPED *pOv4 = new MyOVERLAPPED(100, 600);
	pOv4->nIndex = 4;
	ReadFile(hFile, pOv4->pBuff, 100, NULL, pOv4);

	system("pause");
	// ��һ��IO���״̬���͵���ɶ˿�
	PostQueuedCompletionStatus(hComplePort, /* �������״̬����ɶ˿ڵľ�� */
		0, /* ����˶��ٸ��ֽ� */
		0, /* ��ɼ� */
		0   /* �ص��ṹ�������ַ */
		);
	return 0;
}

unsigned int __stdcall WaitComplePortNotify(void * pArg)
{
	HANDLE hComplePort = (HANDLE)pArg;

	DWORD           dwCompleSize = 0;// IO������ɵ��ֽ��� 
	DWORD           dwCompleKey = 0; // ��ɼ�(������ûɶ��)
	MyOVERLAPPED*   pMyOverlapped = NULL;// OVERLAPPED�ṹ���ַ

	BOOL            bRet = FALSE;
	while (true) {

		// �ȴ�IO����Ͷ�ݵ���ɶ���
		bRet = GetQueuedCompletionStatus(hComplePort,
			&dwCompleSize,
			&dwCompleSize,
			(OVERLAPPED**)&pMyOverlapped,
			INFINITE
			);


		// �ж��Ƿ���Ļ�ȡ�����Ѿ���ɵ�IO����
		if (bRet == TRUE && pMyOverlapped != NULL) {

			printf("[%d] IO�������, ��ȡ�ֽ�:%d, ��ȡλ��:%d, ��ȡ����:[ %s ]\n",
				pMyOverlapped->nIndex,
				pMyOverlapped->InternalHigh,
				pMyOverlapped->Offset,
				pMyOverlapped->pBuff
				);
		}

		delete pMyOverlapped;
	}
}