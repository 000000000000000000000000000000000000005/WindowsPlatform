#include <windows.h>
#include <tchar.h>
#include <process.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	HANDLE hMutex = NULL;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, _T("008������"));

	while (true)
	{
		DWORD dwTargetProcessID;
		DWORD dwMutexHandle;
		printf("������ͻ��˵Ľ���id:");
		scanf_s("%d", &dwTargetProcessID);
		fflush(stdin);
		printf("�����뻥������id:");
		scanf_s("%d", &dwMutexHandle);
		HANDLE hTargetProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwTargetProcessID);
		if (hTargetProcess == INVALID_HANDLE_VALUE)
		{
			printf("�򿪽���ʧ��, err code:%d\n", GetLastError());
		}
		//
		HANDLE hSelfMutex = NULL;
		DuplicateHandle(
			hTargetProcess,
			(HANDLE)dwMutexHandle,
			GetCurrentProcess(),
			&hSelfMutex,
			0,
			FALSE,
			DUPLICATE_CLOSE_SOURCE);

		CloseHandle(hSelfMutex);

	}
	return 0;
}