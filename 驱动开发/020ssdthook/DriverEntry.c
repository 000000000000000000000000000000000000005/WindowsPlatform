#include <ntifs.h>
#pragma pack(1)
typedef struct _ServiceDesriptorEntry
{
	ULONG *ServiceTableBase;        // ������ַ
	ULONG *ServiceCounterTableBase; // �������ַ
	ULONG NumberOfServices;         // ������ĸ���
	UCHAR *ParamTableBase;          // �������ַ
}SSDTEntry, *PSSDTEntry;
#pragma pack()

// ����SSDT
NTSYSAPI SSDTEntry KeServiceDescriptorTable;

ULONG g_uProtectPID;

typedef NTSTATUS(NTAPI *NTOPENPROCESS)(
	__out PHANDLE  ProcessHandle,
	__in ACCESS_MASK  DesiredAccess,
	__in POBJECT_ATTRIBUTES  ObjectAttributes,
	__in_opt PCLIENT_ID  ClientId
	);
NTOPENPROCESS g_OldOpenProcess = NULL;


NTSTATUS NTAPI MyNtOpenProcess(
	__out PHANDLE  ProcessHandle,
	__in ACCESS_MASK  DesiredAccess,
	__in POBJECT_ATTRIBUTES  ObjectAttributes,
	__in_opt PCLIENT_ID  ClientId
	)
{
	if ((ULONG)ClientId->UniqueProcess == g_uProtectPID)
	{
		return STATUS_ABANDONED;
	}
	return g_OldOpenProcess(
		ProcessHandle,
		DesiredAccess,
		ObjectAttributes,
		ClientId
		);
}
void OffProtect()
{
	__asm { //�ر��ڴ汣��
		push eax;
		mov eax, cr0;
		and eax, ~0x10000;
		mov cr0, eax;
		pop eax;
	}
}
void OnProtect()
{
	__asm { //�ָ��ڴ汣��
		push eax;
		mov eax, cr0;
		or eax, 0x10000;
		mov cr0, eax;
		pop eax;
	}
}
void init()
{
	g_OldOpenProcess =
		(NTOPENPROCESS)KeServiceDescriptorTable.ServiceTableBase[0xBE];
}

void OnHook()
{
	OffProtect();
	KeServiceDescriptorTable.ServiceTableBase[0xBE] = (ULONG)MyNtOpenProcess;
	OnProtect();
}
void OffHook()
{
	OffProtect();
	KeServiceDescriptorTable.ServiceTableBase[0xBE] = (ULONG)g_OldOpenProcess;
	OnProtect();
}





VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	UNREFERENCED_PARAMETER(pDriver);
	OffHook();
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pPath)
{
	UNREFERENCED_PARAMETER(pPath);
	g_uProtectPID = 548;
	init();
	OnHook();
	pDriver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}

