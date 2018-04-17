#include "MyOVERLAPPED.h"
#include <tchar.h>
#include <stdio.h>

//   ���¼����������������߳�Ϊ�ɾ��ѵ�״̬��
//   1. SleepEx
//   2. WaitForSignalObjectEx
//   3. WaitForMultipleObjectEx
//   4. SignalObjectAndWait
//   5. GetQueuedCompletionStatusEx
//   6. MsgWaitMultipelObjectEx

// ��ɺ���
VOID WINAPI OverlappedCompliteFun(DWORD dwErrorCode,  // ������
	DWORD dwNumberOfBytesTransfered,  // �ɹ���д���ֽ���
	LPOVERLAPPED lpOverlapped  // �ص�IO�ṹ��ָ��
	)
{
	MyOVERLAPPED* pMyOverlapped = (MyOVERLAPPED*)lpOverlapped;


	printf("[%d] IO�������, ��ȡ�ֽ�:%d, ��ȡλ��:%d, ��ȡ����:[ %s ]\n",
		pMyOverlapped->nIndex,
		pMyOverlapped->InternalHigh,
		pMyOverlapped->Offset,
		pMyOverlapped->pBuff
		);


	// �ͷſռ�
	delete  pMyOverlapped;

}

int main(int argc, char* argv[])
{
	HANDLE hFile = CreateFile(
		_T("main.cpp"),
		GENERIC_READ, // ��Ϊֻ���ļ�
		FILE_SHARE_READ,// �����Ȩ��
		NULL, // ��ȫ������
		OPEN_EXISTING, // ��ʱ�ļ��������
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // ʹ���첽I/O
		NULL
		);

	if (hFile == INVALID_HANDLE_VALUE)
		return 0;

	// ��һ��IO����
	MyOVERLAPPED * pOv1 = new MyOVERLAPPED(50, 0);
	pOv1->nIndex = 0;
	ReadFileEx(hFile, pOv1->pBuff, 50, pOv1, OverlappedCompliteFun);

	// �ڶ���IO����
	MyOVERLAPPED * pOv2 = new MyOVERLAPPED(80, 500);
	pOv2->nIndex = 1;
	ReadFileEx(hFile, pOv2->pBuff, 80, pOv2, OverlappedCompliteFun);

	SleepEx(100000, TRUE);
	system("pause");

	return 0;
}