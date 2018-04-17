#include <windows.h>
#include <winternl.h>
#pragma  comment (lib,"ntdll.lib")
bool NQIP_ProcessDebugFlag()
{
	BOOL bProcessDebugFlag = 0;
	NtQueryInformationProcess(GetCurrentProcess(), 		// Ŀ����̾��
		(PROCESSINFOCLASS)0x1F, 	// ��ѯ��Ϣ����
		&bProcessDebugFlag, 		// �����ѯ��Ϣ
		sizeof(bProcessDebugFlag), 	// ��ѯ���ʹ�С
		NULL 				// ʵ�ʷ��ش�С
		);

	return bProcessDebugFlag ? false : true;
}


int main(int argc, char* argv[])
{
	bool bIsDebug = NQIP_ProcessDebugFlag();
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

