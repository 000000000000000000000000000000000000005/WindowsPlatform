#include <windows.h>
#include <stdio.h>


bool InjectShellCode(DWORD dwPid, const char* szDllName);

int main(int argc, char* argv[])
{
	DWORD	dwPid;
	printf("����Ҫע�뵽�Ľ���PID:");
	scanf_s("%d[*]", &dwPid);
	fflush(stdin);
	InjectShellCode(dwPid, "F:\\15pb��ϰ\\Windowsƽ̨\\Debug\\001����ע��Ķ�̬��.dll");
	return 0;
}

bool InjectShellCode(DWORD dwPid, const char* szDllName)
{
	bool	bRet = false;
	HANDLE	hInjectProcess = NULL;
	HANDLE hInjectThread = NULL;
	LPVOID	pRemoteBuff = NULL;
	DWORD	dwWrite = 0;

	// 1. �򿪽���
	hInjectProcess = OpenProcess(
		PROCESS_ALL_ACCESS,
		FALSE,
		dwPid /*����ID*/
		);
	if (hInjectProcess == NULL) 
	{
		printf("�򿪽���ʧ��,�������ڱ������Ȩ��̫��,���Թ���Ա��������ٳ���\n");
		goto _EXIT;
	}

	// 2. ��Զ�̽����Ͽ����ڴ�ռ�
	pRemoteBuff = VirtualAllocEx(
		hInjectProcess,
		NULL,
		64 * 1024,
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE
		);
	if (pRemoteBuff == NULL)
	{
		printf("��Զ�̽����Ͽ��ٿս�ʧ��\n");
		goto _EXIT;
	}

	// 3. ��DLL·��д�뵽�¿����ڴ�ռ���
	WriteProcessMemory(
		hInjectProcess,
		pRemoteBuff,
		szDllName,
		strlen(szDllName) + 1,
		&dwWrite);
	if (ERROR_SUCCESS != GetLastError()) 
	{
		printf("д��DLL·��ʧ��\n");
		goto _EXIT;
	}

	DWORD	dwInjectThreadID = 0;
	printf("����Ҫע�뵽�Ŀɾ��ѵ��߳�ID:");
	scanf_s("%d[*]", &dwInjectThreadID);
	fflush(stdin);

	//4. ���߳�
	hInjectThread = OpenThread(THREAD_ALL_ACCESS, FALSE, dwInjectThreadID);
	if (NULL == hInjectThread)
	{
		printf("���߳�ʧ��\n");
		goto _EXIT;
	}

	//5. ��Ŀ���߳�Ͷ���첽apc����
	QueueUserAPC((PAPCFUNC)LoadLibraryA, hInjectThread, (DWORD)pRemoteBuff);

	bRet = true;

_EXIT:
	// ����û���ͷ�û��Ԥ�϶Է�ʲôʱ��ִ�����
	//VirtualFreeEx(hInjectProcess, pRemoteBuff, 0, MEM_RELEASE);
	// �رս��̾��
	CloseHandle(hInjectProcess);
	//�ر��߳̾��
	CloseHandle(hInjectThread);

	return bRet;
}
