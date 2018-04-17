//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
// �ź�����ʹ��
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <process.h>
#include <cstdio>
#include <time.h>

HANDLE  g_hSem;    // �ź���
HANDLE  g_hMutex;   // ������
DWORD  g_Array[10];


#define COLOR_GREEN 0xa 
#define COLOR_WHITE 0xf 
// ����ɫ��ӡ�ַ���
void print(int Color, const char* pFormat, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

	va_list va;
	va_start(va, pFormat);
	vprintf(pFormat, va);
	va_end(va);
}



// �����߳�
unsigned int __stdcall ReaderProc(void* pArg)
{
	int nIndex = 0;
	while (true)
	{
		// �ж��Ƿ���д���ź�
		// ReleaseSemaphore����FALSE˵����û��д�����ݵ��߳��ڹ���
		if (FALSE == ReleaseSemaphore(g_hSem, 1, 0)) 
		{
			print(COLOR_WHITE, "[%d]û�����ݶ���\n", GetThreadId(GetCurrentThread()));
		}
		else 
		{
			// д��ʱ���ܶ�, �ȴ�������
			WaitForSingleObject(g_hMutex, -1);
			print(COLOR_WHITE, "[%d]��ȡ����:%d\n", GetThreadId(GetCurrentThread()), g_Array[0]);
			// �ͷŻ�����
			ReleaseMutex(g_hMutex);
		}

	}
	return 0;
}


// д�߳�
unsigned int __stdcall WriterProc(void* pArg)
{
	DWORD nIndex = 0;
	while (true) 
	{
		// ��ʼҪд������, д�Ͷ�����ͬʱ����, �ȴ�������.
		WaitForSingleObject(g_hMutex, INFINITE);
		g_Array[0] = rand() % 50;
		print(COLOR_GREEN, "[%d] --------- д������:%d  --------- \n", GetThreadId(GetCurrentThread()), g_Array[0]);
		// ֪ͨ���߳���������
		WaitForSingleObject(g_hSem, INFINITE);
		// �ͷŻ�����
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

int main()
{
	srand((unsigned int)time(NULL));

	g_hSem = CreateSemaphore(NULL,
		5,  // ���źŵĸ���
		5,  // �����źŸ���
		NULL);

	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	// ����3���߳�
	HANDLE phTread[3];
	phTread[0] = (HANDLE)_beginthreadex(0, 0, ReaderProc, 0, 0, 0);
	phTread[1] = (HANDLE)_beginthreadex(0, 0, ReaderProc, 0, 0, 0);
	phTread[2] = (HANDLE)_beginthreadex(0, 0, WriterProc, 0, 0, 0);

	WaitForMultipleObjects(_countof(phTread), phTread, TRUE, INFINITE);

	return 0;

}