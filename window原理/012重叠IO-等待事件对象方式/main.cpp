#include "MyOVERLAPPED.h"
#include <tchar.h>
#include <stdio.h>
#include <process.h>

// �ȴ�IO�¼����źŵĺ���
unsigned int __stdcall IOProc(void *pArg);

int main(int argc, char* argv[])
{
	HANDLE hFile = CreateFile(
		_T("main.cpp"),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		printf("���ļ�ʧ��, errcode:%d\n", GetLastError());
		return 1;
	}

	//���õ�һ���ص�io��Ϣ
	MyOVERLAPPED *ov1 = new MyOVERLAPPED;
	ov1->Offset = 0;
	ov1->OffsetHigh = 0;
	ov1->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ov1->pBuff = new char[20];
	ZeroMemory(ov1->pBuff, 20);
	ov1->nIndex = 0;
	//�ɷ�io����
	ReadFile(hFile, ov1->pBuff, 20, NULL, ov1);

	//���õڶ����ص�io��Ϣ
	MyOVERLAPPED *ov2 = new MyOVERLAPPED(50, 300);
	ZeroMemory(ov2->pBuff, 50);
	ov2->nIndex = 1;
	ReadFile(hFile, ov2->pBuff, 50, NULL, ov2);



	// �����̵߳ȴ�IO��������
	HANDLE hThreadEvent[2];
	hThreadEvent[0] = (HANDLE)_beginthreadex(0, 0, IOProc, ov1, 0, 0);
	hThreadEvent[1] = (HANDLE)_beginthreadex(0, 0, IOProc, ov2, 0, 0);

	WaitForMultipleObjects(_countof(hThreadEvent), hThreadEvent, TRUE, INFINITE);
	CloseHandle(hFile);

	system("pause");
	return 0;
}

// �ȴ��¼��źŵ��̺߳���
unsigned int __stdcall IOProc(void *pArg)
{
	MyOVERLAPPED* pMyOverlapped = (MyOVERLAPPED*)pArg;

	WaitForSingleObject(pMyOverlapped->hEvent, -1);

	printf("[%d] IO�������, ��ȡ�ֽ�:%d, ��ȡλ��:%d, ��ȡ����:[ %s ]\n",
		pMyOverlapped->nIndex,
		pMyOverlapped->InternalHigh,
		pMyOverlapped->Offset,
		pMyOverlapped->pBuff
		);

	// �ͷſռ�
	delete  pMyOverlapped;

	return 0;
}
