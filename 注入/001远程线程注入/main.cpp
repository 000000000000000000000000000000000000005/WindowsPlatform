#include <stdio.h>
#include <windows.h>

bool DllInject(DWORD dwPid)
{
	/*
	Զ���߳�ע�룺
	��Ŀ������п���һ��Զ���̣߳�CreateRemoteThread
	�̻߳ص�����������һ�������ĺ���
	LoadLibrary����Ҳ��һ�������ĺ���
	���Ծ��ܹ���Զ�̵߳���LoadLibrary
	*/
	DWORD dwRealWrite = 0;
	//1 ��һ������
	HANDLE hProcess =
		OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);

	//2 ��Ŀ�����������һ��ռ�
	LPVOID pBuf =
		VirtualAllocEx(hProcess, 0, 1, MEM_COMMIT, PAGE_READWRITE);

	//3 ��Dll��·��д�뵽Ŀ�����������Ŀռ���
	WriteProcessMemory(
		hProcess,
		pBuf,
		L"c:/001����ע��Ķ�̬��.dll",
		(wcslen(L"c:/001����ע��Ķ�̬��.dll") + 1) * 2,
		&dwRealWrite
		);

	//4 ����һ��Զ���̣߳���Ŀ������д���LoadLibraryW.
	__asm int 3
	HANDLE hThread = CreateRemoteThread(
		hProcess,
		0, 0,
		(LPTHREAD_START_ROUTINE)LoadLibraryW,
		pBuf,
		0, 0
		);
	//5 �ȴ��߳̽���
	WaitForSingleObject(hThread, -1);
	//6 ��β����
	VirtualFreeEx(hProcess, pBuf, 1, 0);
	CloseHandle(hThread);
	CloseHandle(hProcess);
	return true;
}

int main()
{
	int nId = 0;
	printf("��������Ҫע��Ľ���ID:");
	scanf_s("%d", &nId);
	DllInject(nId);
	return 0;
}

