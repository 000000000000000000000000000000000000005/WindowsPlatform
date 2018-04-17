#include <ntddk.h>

/*��������*/
NTSTATUS CommonProc(PDEVICE_OBJECT objDeivce, PIRP pIrp);
NTSTATUS ReadProc(PDEVICE_OBJECT objDeivce, PIRP pIrp);
NTSTATUS CreateProc(PDEVICE_OBJECT objDeivce, PIRP pIrp);
NTSTATUS WriteProc(PDEVICE_OBJECT objDeivce, PIRP pIrp);

VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	UNREFERENCED_PARAMETER(pDriver);
	UNICODE_STRING pSymbolLinkName =
		RTL_CONSTANT_STRING(L"\\DosDevices\\15PBHello");
	IoDeleteSymbolicLink(&pSymbolLinkName);
	IoDeleteDevice(pDriver->DeviceObject);


	KdPrint(("Bye Bye\n"));
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pPath)
{
	UNREFERENCED_PARAMETER(pPath);
	DbgBreakPoint();
	NTSTATUS status = 0;
	UNICODE_STRING pDeviceName =
		RTL_CONSTANT_STRING(L"\\Device\\Hello15PB");
	UNICODE_STRING pSymbolLinkName =
		RTL_CONSTANT_STRING(L"\\DosDevices\\15PBHello");
	PDEVICE_OBJECT pDevice = NULL;
	//1 ����һ���豸
	status = IoCreateDevice(
		pDriver,
		0,
		&pDeviceName,
		FILE_DEVICE_UNKNOWN,
		0,
		FALSE,
		&pDevice
		);
	if (NT_SUCCESS(status) == FALSE)
	{
		return status;
	}
	pDevice->Flags |= DO_BUFFERED_IO;
	//pDevice->Flags |= DO_DIRECT_IO;
	//2 ����һ����������
	IoCreateSymbolicLink(&pSymbolLinkName, &pDeviceName);

	//3 ��дIRP������
	for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		pDriver->MajorFunction[i] = CommonProc;
	}

	pDriver->DriverUnload = DriverUnload;

	return STATUS_SUCCESS;
}

//��ȡ������
NTSTATUS ReadProc(PDEVICE_OBJECT objDeivce, PIRP pIrp) 
{
	UNREFERENCED_PARAMETER(objDeivce);
	//��ȡio������
	UCHAR * pIOBuff = NULL;
	if (pIrp->AssociatedIrp.SystemBuffer != NULL)
	{
		pIOBuff = pIrp->AssociatedIrp.SystemBuffer;
	}
	else if (pIrp->MdlAddress != NULL)
	{
		pIOBuff = MmGetSystemAddressForMdlSafe(pIrp->MdlAddress, NormalPagePriority);
	}
	ULONG uThreadID = (ULONG)PsGetCurrentThreadId();
	DbgPrint("threadid:%d\n", uThreadID);

	//���÷�������
	wchar_t szMsg[] = L"this is a ring 0 msg";
	memcpy(pIOBuff, szMsg, wcslen(szMsg) * sizeof(wchar_t)+sizeof(wchar_t));
	// ����IRP���״̬
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	// ����IRP�����˶����ֽ�
	pIrp->IoStatus.Information = wcslen(szMsg) * sizeof(wchar_t)+sizeof(wchar_t);
	// ����IRP
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
//����������
NTSTATUS CreateProc(PDEVICE_OBJECT objDeivce, PIRP pIrp)
{
	UNREFERENCED_PARAMETER(objDeivce);

	// ����IRP���״̬
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	// ����IRP�����˶����ֽ�
	pIrp->IoStatus.Information = 0;
	// ����IRP
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
//д�봦����
NTSTATUS WriteProc(PDEVICE_OBJECT objDeivce, PIRP pIrp)
{
	UNREFERENCED_PARAMETER(objDeivce);
	//1 ��û�������ͨ�ô���
	UCHAR * pIOBuff = NULL;
	if (pIrp->AssociatedIrp.SystemBuffer != NULL)
	{
		pIOBuff = pIrp->AssociatedIrp.SystemBuffer;
	}
	else if (pIrp->MdlAddress != NULL)
	{
		pIOBuff = MmGetSystemAddressForMdlSafe(pIrp->MdlAddress, NormalPagePriority);
	}
	//2 ��û������ж��
	PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
	pStack->Parameters.Write.Length;


	KdPrint(("%s\n", pIOBuff));

	// ����IRP���״̬
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	// ����IRP�����˶����ֽ�
	pIrp->IoStatus.Information = 5;
	// ����IRP
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

//д�봦����
NTSTATUS CommonProc(PDEVICE_OBJECT objDeivce, PIRP pIrp)
{
	//1 �����IRPջ
	PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
	pStack->Parameters.Write.Length;

	switch (pStack->MajorFunction)
	{
	case IRP_MJ_READ:
		ReadProc(objDeivce, pIrp);
		break;
	case IRP_MJ_WRITE:
		WriteProc(objDeivce, pIrp);
		break;
	default:
		// ����IRP���״̬
		pIrp->IoStatus.Status = STATUS_SUCCESS;
		// ����IRP�����˶����ֽ�
		pIrp->IoStatus.Information = 5;
		// ����IRP
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	}
	return STATUS_SUCCESS;

}