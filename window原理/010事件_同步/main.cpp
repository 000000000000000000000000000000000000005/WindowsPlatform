#include <windows.h>
#include <process.h>
#include <tchar.h>
#include <stdio.h>

HANDLE hEventA = NULL;
HANDLE hEventB = NULL;
HANDLE hEventC = NULL;

long g_nCount = 10; //�ܹ�ѭ��10��

unsigned int __stdcall ThreadA(void* pArg)
{
	while (true)
	{
		WaitForSingleObject(hEventA, INFINITE);
		if (g_nCount <= 0) break;
		ResetEvent(hEventA);
		printf("[%d]==A\n", GetCurrentThreadId());
		SetEvent(hEventB);
	}
	return 0;
}

unsigned int __stdcall ThreadB(void* pArg)
{
	while (true)
	{
		WaitForSingleObject(hEventB, INFINITE);
		if (g_nCount <= 0) break;
		ResetEvent(hEventB);
		printf("[%d]==B\n", GetCurrentThreadId());
		SetEvent(hEventC);
	}
	return 0;
}

unsigned int __stdcall ThreadC(void* pArg)
{
	while (true)
	{
		WaitForSingleObject(hEventC, INFINITE);
		ResetEvent(hEventC);
		printf("[%d]==C\n", GetCurrentThreadId());
		SetEvent(hEventA);
		//
		--g_nCount;
		if (g_nCount <= 0) break;
	}
	SetEvent(hEventB);
	SetEvent(hEventA);

	return 0;
}


int main(int argc, char* argv[])
{
	//���������¼�
	hEventA = CreateEvent(NULL, TRUE, FALSE, _T("A�߳��¼�"));
	hEventB = CreateEvent(NULL, TRUE, FALSE, _T("B�߳��¼�"));
	hEventC = CreateEvent(NULL, TRUE, FALSE, _T("C�߳��¼�"));

	// ����3���߳�
	HANDLE phTread[3];
	phTread[0] = (HANDLE)_beginthreadex(0, 0, ThreadA, 0, 0, 0);
	phTread[1] = (HANDLE)_beginthreadex(0, 0, ThreadB, 0, 0, 0);
	phTread[2] = (HANDLE)_beginthreadex(0, 0, ThreadC, 0, 0, 0);

	//�����¼�A
	SetEvent(hEventA);

	WaitForMultipleObjects(_countof(phTread), phTread, TRUE, INFINITE);

	//�ͷ��ں˶������ü���
	CloseHandle(hEventA);
	CloseHandle(hEventC);
	CloseHandle(hEventC);

	return 0;
}