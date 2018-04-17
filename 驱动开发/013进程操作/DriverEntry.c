#include <ntifs.h>


VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	UNREFERENCED_PARAMETER(pDriver);
	KdPrint(("Leave"));
}


// ����PID���ؽ���EPROCESS��ʧ�ܷ���NULL
PEPROCESS LookupProcess(HANDLE hPid)
{
	PEPROCESS pEProcess = NULL;
	if (NT_SUCCESS(PsLookupProcessByProcessId(
		hPid, &pEProcess)))
		return pEProcess;
	return NULL;
}

//��ͣ����
NTKERNELAPI NTSTATUS PsSuspendProcess(
	PEPROCESS pEProcess);

VOID MySyspendProcess(ULONG uPid)
{
	PEPROCESS pProcess = LookupProcess((HANDLE)uPid);
	if (pProcess != NULL)
	{
		PsSuspendProcess(pProcess);
	}
	ObDereferenceObject(pProcess);
}

//�ָ�����

NTKERNELAPI NTSTATUS PsResumeProcess(
	PEPROCESS pEProcess);
VOID MyResumeProcess(ULONG uPid)
{
	PEPROCESS pProcess = LookupProcess((HANDLE)uPid);
	if (pProcess != NULL)
	{
		PsResumeProcess(pProcess);
	}
	ObDereferenceObject(pProcess);
}

void KernelKillProcess(ULONG uPid) {
	HANDLE            hProcess = NULL;
	CLIENT_ID         ClientId = { 0 };
	OBJECT_ATTRIBUTES objAttribut =
	{ sizeof(OBJECT_ATTRIBUTES) };
	ClientId.UniqueProcess = (HANDLE)uPid; // PID
	ClientId.UniqueThread = 0;
	// �򿪽��̣���������Ч�����������
	ZwOpenProcess(
		&hProcess,    // ���ش򿪺�ľ��
		1,            // ����Ȩ��
		&objAttribut, // ��������
		&ClientId);   // ����ID�ṹ
	if (hProcess) {
		ZwTerminateProcess(hProcess, 0);
		ZwClose(hProcess);
	};
}
NTKERNELAPI HANDLE PsGetProcessInheritedFromUniqueProcessId(
	IN PEPROCESS pEProcess);
NTKERNELAPI UCHAR* PsGetProcessImageFileName(
	IN PEPROCESS pEProcess);
VOID EnumProcess() {
	PEPROCESS pEProc = NULL;
	// ѭ���������̣������̵߳����ֵ������0x25600��
	ULONG i = 0;
	for (i = 4; i < 0x25600; i = i + 4) {
		// a.����PID����PEPROCESS
		pEProc = LookupProcess((HANDLE)i);
		if (!pEProc) continue;
		// b. ��ӡ������Ϣ
		DbgPrint("EPROCESS=%p PID=%ld PPID=%ld Name=%s\n",
			pEProc, (UINT32)PsGetProcessId(pEProc),
			(UINT32)PsGetProcessInheritedFromUniqueProcessId(pEProc),
			PsGetProcessImageFileName(pEProc));
		// c. �����̶������ü�����1
		ObDereferenceObject(pEProc);
		DbgPrint("\n");
	}
}


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pPath)
{
	UNREFERENCED_PARAMETER(pPath);
	KdPrint(("Hello 15PB\n"));

	DbgBreakPoint();
	//MyResumeProcess(1836);
	//KernelKillProcess(1836);
	EnumProcess();

	pDriver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}