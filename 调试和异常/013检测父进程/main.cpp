#include <windows.h>
#include <winternl.h>
#pragma comment(lib,"ntdll.lib")
bool NQIP_CheckParentProcess()
{
	struct PROCESS_BASIC_INFORMATION {
		ULONG ExitStatus; 		 // ���̷�����
		PPEB  PebBaseAddress; 		 // PEB��ַ
		ULONG AffinityMask; 		 // CPU�׺�������
		LONG  BasePriority; 		 // �������ȼ�
		ULONG UniqueProcessId; 		 // ������PID
		ULONG InheritedFromUniqueProcessId; // ������PID
	}stcProcInfo;

	NtQueryInformationProcess(GetCurrentProcess(),
		ProcessBasicInformation,
		&stcProcInfo,
		sizeof(stcProcInfo),
		NULL);

	DWORD ExplorerPID = 0;
	DWORD CurrentPID = stcProcInfo.InheritedFromUniqueProcessId;
	GetWindowThreadProcessId(FindWindow(L"Progman", NULL), &ExplorerPID);

	return ExplorerPID == CurrentPID ? false : true;
}

int main(int argc, char* argv[])
{
	bool bIsDebug = NQIP_CheckParentProcess();
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
