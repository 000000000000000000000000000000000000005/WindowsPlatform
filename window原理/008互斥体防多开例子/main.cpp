#include <windows.h>
#include <tchar.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	HANDLE hMutex = NULL;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, _T("008������"));

	if (NULL == hMutex)
	{
		hMutex = CreateMutex(NULL, TRUE, _T("008������"));
		printf("Դ����id:%d Դ���id:%d\n", GetCurrentProcessId(), hMutex);
		//
		printf("����������\n");
		while (true);
	}
	else
	{
		printf("����һ�������Ѿ�������,�رճ���\n");
	}
	CloseHandle(hMutex);

	system("pause");
	return 0;
}