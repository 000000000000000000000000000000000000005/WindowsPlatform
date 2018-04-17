#include <windows.h>
#include <process.h>
#include <stdio.h>


unsigned int __stdcall  ThreadProc(void * Parameter)
{
	while (true)
	{

		Sleep(1000);
	}
	return 0;
}

int main(int argc, char* argv[])
{

	HANDLE hThread = (HANDLE)_beginthreadex(NULL, NULL, ThreadProc, NULL, NULL, NULL);

	printf("��ȡ�����̵ľ����α���:%x\n", GetCurrentProcess());
	printf("��ȡ���̵߳ľ����α���:%x\n", GetCurrentThread());

	HANDLE hTargetProcess = NULL;  //��α���ת���ɵ���ʵ���
	DuplicateHandle(
		GetCurrentProcess(), //Դ���̾�� 
		GetCurrentProcess(), //Ҫ�������α���
		GetCurrentProcess(), //Ŀ����̾��
		&hTargetProcess,
		NULL,
		FALSE,
		DUPLICATE_SAME_ACCESS);

	HANDLE hTargetThread = NULL;  //��α���ת���ɵ���ʵ���
	DuplicateHandle(
		GetCurrentProcess(), //Դ���̾�� 
		GetCurrentThread(), //Ҫ�������α���
		GetCurrentProcess(), //Ŀ����̾��
		&hTargetThread,
		NULL,
		FALSE,
		DUPLICATE_SAME_ACCESS);

	printf("��ȡ�����̵ľ������ʵ���:%x\n", hTargetProcess);
	CloseHandle(hTargetProcess);
	printf("��ȡ���̵߳ľ������ʵ���:%x\n", hTargetThread);
	CloseHandle(hTargetThread);


	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	return 0;
}