// TLS����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

// ˵��ʹ��TLS
#pragma comment(linker, "/INCLUDE:__tls_used")


// ��ͨ��ȫ�ֱ���
int g_nNum2 = 0xFFFFFFFF;

// TLS�ص�����A
void NTAPI t_TlsCallBack_A(PVOID DllHandle, DWORD Reason, PVOID Red) {
	if (DLL_THREAD_DETACH == Reason) // ����߳��˳����ӡ��Ϣ
		printf("t_TlsCallBack_A -> ThreadDetach!, theadid:%d\r\n", GetCurrentThreadId());

	if (DLL_PROCESS_ATTACH == Reason) {
		printf("t_TlsCallBack_A -> ThreadAttach! theadid:%d\r\n", GetCurrentThreadId());
	}
	return;
}

// TLS�ص�����B
void NTAPI t_TlsCallBack_B(PVOID DllHandle, DWORD Reason, PVOID Red) {
	if (DLL_THREAD_DETACH == Reason) // ����߳��˳����ӡ��Ϣ
		printf("t_TlsCallBack_B -> ThreadDetach!, theadid:%d\r\n", GetCurrentThreadId());

	if (DLL_PROCESS_ATTACH == Reason) {
		printf("t_TlsCallBack_B -> ThreadAttach! theadid:%d\r\n", GetCurrentThreadId());
	}

	return;
}

/*
* ע��TLS�ص�������".CRT$XLB"�ĺ����ǣ�
* CRT����ʹ��C RunTime����
* X��ʾ��ʶ�����
* L��ʾTLS callback section
* B��ʵҲ����ΪB-Y������һ����ĸ
* ��һ��˵���ǣ��������ᰴ�������ĸ��
* ˳������������ӵĶα��浽pe�ļ��С�
*/
#pragma data_seg(".CRT$XLB")
PIMAGE_TLS_CALLBACK p_thread_callback[] =
{
	t_TlsCallBack_A,  // TLS�̻߳ص�����
	t_TlsCallBack_B,
	NULL
};
#pragma data_seg()

DWORD WINAPI t_ThreadFun(PVOID pParam) {
	printf("t_Thread ->  first printf:");
	printf("[1]��ͨ��ȫ�ֱ���:%08X\n", g_nNum2);

	g_nNum2 = 0;
	//ע������
	// �����������߳��޸Ĵ˴�


	printf("t_Thread -> second printf:");
	printf("[2]��ͨ��ȫ�ֱ���:%08X\n", g_nNum2);
	return 0;
}
/*
��һ���̱߳�������ʱ��
TLS�̻߳ص���������ͨ�̻߳ص�������ִ��˳��:
1. �Ƚ�TLS�̻߳ص�������������
1.1 TLS�̻߳ص�����ע����ٸ�,�͵��ö��ٸ�,���Ұ��ն����˳�����
2. �ٵ����̻߳ص�����

��һ���߳��˳���ʱ��
1. ��TLS�̻߳ص�������������
1.1 TLS�̻߳ص�����ע����ٸ�,�͵��ö��ٸ�,���Ұ��ն����˳�����
*/

int _tmain(int argc, _TCHAR* argv[]) {

	g_nNum2 = 0x22222222;



	printf("_tmain -> TlsDemo.exe is runing..., threadid:%d\r\n\r\n", GetCurrentThreadId());
	CreateThread(NULL, 0, t_ThreadFun, NULL, 0, 0);


	//Sleep( 500 );  // ˯��100��������ȷ����һ���߳�ִ�����
	//printf( "\r\n" );
	//CreateThread( NULL , 0 , t_ThreadFun , NULL , 0 , 0 );
	system("pause");
	return 0;
}