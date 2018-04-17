#include <windows.h>
#include <winternl.h>
#pragma  comment (lib,"ntdll.lib")

bool NQIP_ProcessDebugObjectHandle()
{
	HANDLE hProcessDebugObjectHandle = 0;
	DWORD dwReturnLength = 0;
	NtQueryInformationProcess(GetCurrentProcess(), 			// Ŀ����̾��
		(PROCESSINFOCLASS)0x1E, 		// ��ѯ��Ϣ����
		&hProcessDebugObjectHandle, 	// �����ѯ��Ϣ
		sizeof(hProcessDebugObjectHandle), // ��ѯ���ʹ�С
		&dwReturnLength 					// ʵ�ʷ��ش�С
		);
	MessageBoxA(NULL, "��ⵯ�����������", "����", 0);
	return hProcessDebugObjectHandle ? true : false;
}

int main(int argc, char* argv[])
{

	bool bIsDebug = NQIP_ProcessDebugObjectHandle();

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
