#include <Ntifs.h>
#pragma warning(disable:4189 4100)

#pragma pack(1)
typedef struct _ServiceDesriptorEntry
{
	ULONG *ServiceTableBase;        // ������ַ
	ULONG *ServiceCounterTableBase; // �������ַ
	ULONG NumberOfServices;         // ������ĸ���
	UCHAR *ParamTableBase;          // �������ַ
}SSDTEntry, *PSSDTEntry;
#pragma pack()

//�ɵ�ssdt�������
ULONG *gOldServiceTableBase = NULL;
UCHAR *gOldParamTableBase = NULL;



// ����SSDT
NTSYSAPI SSDTEntry KeServiceDescriptorTable;
VOID DriverUnload(PDRIVER_OBJECT pDriver);
NTSTATUS MyNtReadVirtualMemory(ULONG uFromPid, PVOID  pFromAddress, PVOID pToBuff, ULONG uReadSize);
#pragma  alloc_text(NONE_PAGE, MyNtReadVirtualMemory)


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING path)
{
	DbgBreakPoint();
	pDriver->DriverUnload = DriverUnload;
	//��ssdt���������Լ��ĺ���
	PULONG pNewServiceTableBase = ExAllocatePool(NonPagedPool, (KeServiceDescriptorTable.NumberOfServices  + 1)* sizeof(ULONG));
	PUCHAR pNewParamTableBase = ExAllocatePool(NonPagedPool, (KeServiceDescriptorTable.NumberOfServices +1)* sizeof(UCHAR));
	RtlCopyMemory(pNewServiceTableBase, KeServiceDescriptorTable.ServiceTableBase, (KeServiceDescriptorTable.NumberOfServices + 1)* sizeof(ULONG));
	RtlCopyMemory(pNewParamTableBase, KeServiceDescriptorTable.ParamTableBase, (KeServiceDescriptorTable.NumberOfServices + 1)* sizeof(UCHAR));
	__asm cli
	ULONG uIndex = KeServiceDescriptorTable.NumberOfServices;
	//����һ��
	gOldServiceTableBase = KeServiceDescriptorTable.ServiceTableBase;
	gOldParamTableBase = KeServiceDescriptorTable.ParamTableBase;
	//����Ϊ�µ�
	KeServiceDescriptorTable.ServiceTableBase = pNewServiceTableBase;
	KeServiceDescriptorTable.ParamTableBase = pNewParamTableBase;
	KeServiceDescriptorTable.ServiceTableBase[uIndex] = (ULONG)MyNtReadVirtualMemory;
	KeServiceDescriptorTable.ParamTableBase[uIndex] = 0x10;
	KeServiceDescriptorTable.NumberOfServices++;
	__asm sti


	return STATUS_SUCCESS;
}

NTSTATUS MyNtReadVirtualMemory(ULONG uFromPid, PVOID  pFromAddress, PVOID pToBuff, ULONG uReadSize)
{
	NTSTATUS status = STATUS_SUCCESS;

	//��ȡĿ�������Ϣ
	PEPROCESS pFromEProcess = NULL;
	status = PsLookupProcessByProcessId((HANDLE)uFromPid, &pFromEProcess);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("û�����ݴ���Ľ���id�ҵ���Ӧ��eprocess\n"));
		return status;
	}

	//����������������
	if (!MmIsAddressValid(pToBuff))
	{
		KdPrint(("�����pToBuff����pagefault\n"));
		ObDereferenceObject(pFromEProcess);
		return STATUS_ABANDONED;
	}

	//���̹ҿ�
	KAPC_STATE ks;
	KeStackAttachProcess(pFromEProcess, &ks);

	//�Զ�ȡ�����������
	if (!MmIsAddressValid(pFromAddress))
	{
		KdPrint(("�����pFromAddress����pagefault\n"));
		KeUnstackDetachProcess(&ks);
		ObDereferenceObject(pFromEProcess);
		return STATUS_ABANDONED;
	}
	//������ʱ�ռ�
	PVOID pTmbBuff = ExAllocatePool(NonPagedPool, uReadSize);

	//������ϵͳ�ռ�
	__try
	{
		RtlCopyMemory(pTmbBuff, pFromAddress, uReadSize);
	}
	__except (1)
	{
		KdPrint(("��pFromAddress��ȡ���ݴ���\n"));
		ExFreePool(pTmbBuff);
		KeUnstackDetachProcess(&ks);
		ObDereferenceObject(pFromEProcess);
		return STATUS_ABANDONED;
	}
	KeUnstackDetachProcess(&ks);

	//����ʱ������д��Ŀ��
	__try
	{
		RtlCopyMemory(pToBuff, pTmbBuff, uReadSize);
	}
	__except (1)
	{
		KdPrint(("����ʱ������������Ŀ�껺��������\n"));
		ExFreePool(pTmbBuff);
		KeUnstackDetachProcess(&ks);
		ObDereferenceObject(pFromEProcess);
		return STATUS_ABANDONED;
	}

	//����
	ExFreePool(pTmbBuff);
	ObDereferenceObject(pFromEProcess);
	return status;
}

VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	//�ָ�ssdt��
	PUCHAR pNewParamTableBase = KeServiceDescriptorTable.ParamTableBase;
	PULONG pNewServiceTableBase = KeServiceDescriptorTable.ServiceTableBase;
	__asm cli
	KeServiceDescriptorTable.ServiceTableBase = gOldServiceTableBase;
	KeServiceDescriptorTable.ParamTableBase = gOldParamTableBase;
	KeServiceDescriptorTable.NumberOfServices--;
	__asm sti
	ExFreePool(pNewParamTableBase);
	ExFreePool(pNewServiceTableBase);
	KdPrint(("�ָ�ssdt��\n"));
}