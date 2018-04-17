#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <tchar.h>

#pragma  warning(disable: 4723)

HANDLE g_hMutex = NULL;


unsigned int __stdcall ThreadProc(void *pArg)
{
	int nIndex = (int)pArg;

	WaitForSingleObject(g_hMutex, INFINITE);
	printf("-----------------------------------------------------------\n");
	printf("�߳�:%d,����������,���ڵ���5���쳣�˳�\n", nIndex);
	int n = 100;

	__try
	{
		while (true)
		{
			for (int i = 0; i < 5; i++)
			{
				Sleep(1000);
				printf("%d��......\n", i + 1);
			}
			n /= 0;

		}
	}
	__except (1)
	{
		printf("�ҹ���,���������û�ͷŻ�����Ŷ(*^__^*) ��������\n");
	}

	return 0;
}



int main(int argc, char* argv[])
{
	g_hMutex = CreateMutex(NULL, FALSE, _T("008������ͬ��"));
	if (INVALID_HANDLE_VALUE == g_hMutex)
	{
		printf("�����쳣�˳�\n");
		goto __EXCEPTION_END;
	}

	HANDLE phThreadArray[10];
	for (int i = 0; i < 10; ++i)
	{
		phThreadArray[i] = (HANDLE)_beginthreadex(0, 0, ThreadProc, (void*)i, 0, 0);
	}

	WaitForMultipleObjects(10, phThreadArray, TRUE, INFINITE);
	CloseHandle(g_hMutex);


__EXCEPTION_END:
	system("pause");

	return 0;
}