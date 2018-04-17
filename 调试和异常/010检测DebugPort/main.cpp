#include <windows.h>
#include <winternl.h>
#include <stdio.h>

#pragma comment(lib,"ntdll.lib")
bool NQIP_ProcessDebugPort() {

	printf("��ʼ���debug port\n");
	HANDLE nDebugPort = 0;
	NtQueryInformationProcess(GetCurrentProcess(), // Ŀ����̾��
		ProcessDebugPort, 	 // ��ѯ��Ϣ����
		&nDebugPort, 		 // �����ѯ��Ϣ
		sizeof(nDebugPort),  // ��ѯ���ʹ�С
		NULL 			     // ʵ�ʷ������ݴ�С
		);

	return nDebugPort == INVALID_HANDLE_VALUE ? true : false;
}


int main(int argc, char* argv[])
{

	bool bIsDebug = NQIP_ProcessDebugPort();
	if (bIsDebug)
	{
		MessageBoxA(NULL, "���ڱ�����", "����", 0);
	}
	else
	{
		MessageBoxA(NULL, "���ںܰ�ȫ", "��ϲ", 0);
	}
	return 0;
}

