#include <ntifs.h>


VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	UNREFERENCED_PARAMETER(pDriver);
	KdPrint(("Leave"));
}

KEVENT g_kEvent;
VOID t_funThread(IN PVOID StartContext) {
	// 1. ��ӡ�����ַ�
	PUNICODE_STRING pustrMsg = (PUNICODE_STRING)StartContext;
	DbgPrint("Kernel thread: %d\n", PsGetCurrentThreadId());
	DbgPrint("Kernel thread: %wZ\n", pustrMsg);
	// 2. ���¼�������Ϊ����״̬�����������߳�
	KeSetEvent(&g_kEvent, 0, TRUE);
	PsTerminateSystemThread(STATUS_SUCCESS);
}
VOID Test_CreateThread() {
	NTSTATUS       Status;
	HANDLE         hThread;
	UNICODE_STRING ustrMsg = RTL_CONSTANT_STRING(L"15PB!");
	// 1. ��ʼ���¼��󴴽��߳�
	DbgPrint("Kernel thread: %d\n", PsGetCurrentThreadId());
	KeInitializeEvent(&g_kEvent, SynchronizationEvent, FALSE);
	Status = PsCreateSystemThread(&hThread, 0, NULL, NULL, NULL,
		t_funThread, (PVOID)&ustrMsg);
	if (!NT_SUCCESS(Status))  return;
	ZwClose(hThread);
	// 2. �ȴ��¼������ź�
	KeWaitForSingleObject(&g_kEvent, Executive, KernelMode, 0, 0);
}
//��ͣ�߳�


//�ָ��߳�


//�����߳�


NTSTATUS ZwOpenThread(
	_Out_  PHANDLE ThreadHandle,
	_In_   ACCESS_MASK DesiredAccess,
	_In_   POBJECT_ATTRIBUTES ObjectAttributes,
	_In_   PCLIENT_ID ClientId);
typedef NTSTATUS(__fastcall *ZWTERMINATETHREAD)(
	HANDLE hThread,
	ULONG uExitCode);
ZWTERMINATETHREAD ZwTerminateThread = (ZWTERMINATETHREAD)0x8407c6cb; //������ַ,��Ҫ�Լ�ȥѰ��
void KernelKillThread() {
	HANDLE            hThread = NULL;
	CLIENT_ID         ClientId = { 0 };
	OBJECT_ATTRIBUTES objAttribut =
	{ sizeof(OBJECT_ATTRIBUTES) };
	ClientId.UniqueProcess = 0;
	ClientId.UniqueThread = (HANDLE)1234; // TID  
	//���̣߳���������Ч��������߳�
	ZwOpenThread(&hThread, 1, &objAttribut, &ClientId);
	if (hThread) {
		ZwTerminateThread(hThread, 0);
		ZwClose(hThread);
	}
}

// ����TID�����߳�ETHREAD��ʧ�ܷ���NULL
PETHREAD LookupThread(HANDLE hTid)
{
	PETHREAD pEThread = NULL;
	if (NT_SUCCESS(PsLookupThreadByThreadId(
		hTid,
		&pEThread)))
		return pEThread;
	return NULL;
}

VOID EnumThread(PEPROCESS pEProcess) {
	PEPROCESS pEProc = NULL;
	PETHREAD  pEThrd = NULL;
	// ѭ�������̣߳������̵߳����ֵ������0x25600��
	ULONG i = 0;
	for (i = 4; i < 0x25600; i += 4) {
		// a. ����TID����ETHREAD
		pEThrd = LookupThread((HANDLE)i);
		if (!pEThrd)  continue;
		// b. ����߳��������̣����������ӡ�߳���Ϣ
		pEProc = IoThreadToProcess(pEThrd);
		if (pEProc == pEProcess) {
			DbgPrint("[THREAD]ETHREAD=%p TID=%ld\n",
				pEThrd, (ULONG)PsGetThreadId(pEThrd));
		}
		// c. ���̶߳������ü�����1
		ObDereferenceObject(pEThrd);
	}
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


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pPath)
{
	UNREFERENCED_PARAMETER(pPath);
	KdPrint(("Hello 15PB\n"));

	DbgBreakPoint();
	PEPROCESS pProcess = LookupProcess((HANDLE)3536);
	EnumThread(pProcess);


	pDriver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}
