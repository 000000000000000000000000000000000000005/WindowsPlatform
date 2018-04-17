#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT pDriverObject);


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pPath)
{
	pPath;
	pDriver->DriverUnload = DriverUnload;
	//
	PVOID pHeadA = NULL;
	PVOID pHeadB = NULL;
	pHeadA = ExAllocatePool(PagedPool, 0xA1);
	pHeadB = ExAllocatePool(NonPagedPool, 0x15);
	//
	RtlZeroMemory(pHeadA, 0xA1);
	RtlZeroMemory(pHeadB, 0x15);
	//��ǰ10���ֽ����ΪFF
	RtlFillMemory(pHeadA, 0x10, 0xFF);

	//�����ռ�, ��pHeapB��0x15���ֽڿ�����pHeadA
	RtlCopyMemory(pHeadA, pHeadB, 0x15);


	//�ͷ��ڴ�
	ExFreePool(pHeadA);
	ExFreePool(pHeadB);

	return STATUS_SUCCESS;
}


VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	pDriverObject;
	KdPrint(("driver unload\n"));
}