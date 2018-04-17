#pragma warning(disable:4101 4100 4055 4152)
#include <ntddk.h>

#define DEVICE_NAME L"\\Device\\TestSys"  

PIO_WORKITEM   g_pIoWorkItem = NULL;

void DriverUnload(PDRIVER_OBJECT pDriver);
//��ѯ�ļ���Ϣ�� Work Item �Ļص�������
VOID WorkerItemQueryFileInfoRoutine(PDEVICE_OBJECT  DeviceObject, PVOID  Context);

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING ustrDevName;
	PDEVICE_OBJECT pDevObj = NULL;

	pDriver->DriverUnload = DriverUnload;

	RtlInitUnicodeString(&ustrDevName, DEVICE_NAME);
	status = IoCreateDevice(pDriver, 0, &ustrDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDevObj);
	if (status != STATUS_SUCCESS)
	{
		DbgPrint("�豸���󴴽�ʧ��\r\n");
		return status;
	}
	pDevObj->Flags |= DO_BUFFERED_IO;
	DbgPrint("�豸���󴴽��ɹ�\r\n");
	//
	g_pIoWorkItem = IoAllocateWorkItem(pDevObj);
	if (g_pIoWorkItem)
	{
		IoQueueWorkItem(g_pIoWorkItem, WorkerItemQueryFileInfoRoutine, DelayedWorkQueue, NULL);
	}
	return STATUS_SUCCESS;
}

void DriverUnload(PDRIVER_OBJECT pDriver)
{
	UNREFERENCED_PARAMETER(pDriver);
	IoDeleteDevice(pDriver->DeviceObject);
	DbgPrint("�����Ѿ���ж��\r\n");
}

VOID WorkerItemQueryFileInfoRoutine(PDEVICE_OBJECT  DeviceObject, PVOID  Context)
{
	KdPrint(("�̹߳������\n"));
}