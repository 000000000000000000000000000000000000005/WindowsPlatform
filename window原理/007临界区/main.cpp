#include <windows.h>
#include <stdio.h>
#include <process.h>

int g_nNum = 0;
CRITICAL_SECTION g_criticalSection; // �ٽ���


unsigned int __stdcall ThreadProc(void *pArg)
{
	int nIndex = (int)pArg;
	// �����ٽ���
	EnterCriticalSection(&g_criticalSection);

	++g_nNum;                                           //\ 
	Sleep(1); // ���߳̽����л�.                         //| �⼸�б������ٽ����ڵĴ����γ���ԭ�Ӳ��� 
	//| ֻҪû�뿪�ٽ���,��ʹ�߳̽����л�,�����̲߳���ִ�д���
	printf("[%d] g_nNum = %d\n", nIndex, g_nNum);   /// 

	// �뿪�ٽ���
	LeaveCriticalSection(&g_criticalSection);

	return 0;
}



int main(int argc, char* argv[])
{

	// ��ʼ���ٽ���
	InitializeCriticalSection(&g_criticalSection);

	HANDLE phThreadArray[10];
	for (int i = 0; i < 10; ++i) {

		// �����߳�
		phThreadArray[i] = (HANDLE)_beginthreadex(0, 0, ThreadProc, (void*)i, 0, 0);
	}


	// �ȴ������̷߳���
	WaitForMultipleObjects(10, phThreadArray, TRUE, INFINITE);

	system("pause");


	return 0;
}