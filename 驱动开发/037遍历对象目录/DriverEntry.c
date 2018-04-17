#pragma warning(disable:4101 4100 4055 4152)

#include <ntddk.h>



#define MAX_TABLE                        37
#define MAX_OBJECT_COUNT        0x10000
typedef ULONG DEVICE_MAP;
typedef ULONG EX_PUSH_LOCK;
typedef struct _OBJECT_DIRECTORY_ENTRY{                //Ŀ¼������ı������ С��  dt _OBJECT_DIRECTORY_ENTRY 8a408cc8 
	struct _OBJECT_DIRECTORY_ENTRY *ChainLink;
	PVOID        Object;
	ULONG        HashValue;
}OBJECT_DIRECTORY_ENTRY, *POBJECT_DIRECTORY_ENTRY;
typedef struct _OBJECT_DIRECTORY{                            //Ŀ¼���� ���  dt _object_directory -b 8a405ed0
	POBJECT_DIRECTORY_ENTRY        HashBuckets[MAX_TABLE];
	EX_PUSH_LOCK        Lock;
	DEVICE_MAP                DeviceMap;
	ULONG                        SessionId;
	PVOID                        NamespaceEntry;
	ULONG                        Flags;
}OBJECT_DIRECTORY, *POBJECT_DIRECTORY;
typedef struct _OBJECT_HEADER_NAME_INFO{	//��ѯ�ں˶����ַ ���صĽṹ 
	POBJECT_DIRECTORY        Directory;
	UNICODE_STRING                Name;
	ULONG                                ReferenceCount;
}OBJECT_HEADER_NAME_INFO, *POBJECT_HEADER_NAME_INFO;


typedef PVOID(*OBQUERYNAMEINFO)(IN PVOID Object);//ͨ���ں˶����ַ ��ѯ ����
OBQUERYNAMEINFO ObQueryNameInfo;//�������ö�ٶ���Ŀ¼


void EnumObjectDirectory()
{
	UCHAR                                type_index;
	ULONG                                u_index;
	ULONG                                u_front, u_rear;
	UNICODE_STRING                str_func_name;
	POBJECT_DIRECTORY        ObpRootDirectoryObject;
	POBJECT_DIRECTORY_ENTRY*        queue;
	POBJECT_HEADER_NAME_INFO        pobject_name_info;//��ѯ�ں˶����ַ ���صĽṹ  	//ObQueryNameInfo�ǲ�ѯ�������֣���ʱ����ֻ��vista�Ժ��ϵͳ�����������
	RtlInitUnicodeString(&str_func_name, L"ObQueryNameInfo");
	ObQueryNameInfo = (OBQUERYNAMEINFO)MmGetSystemRoutineAddress(&str_func_name);
	if (!MmIsAddressValid(ObQueryNameInfo))
	{
		KdPrint(("ObQueryNameInfo is null."));
		return;
	}
	ObpRootDirectoryObject = (POBJECT_DIRECTORY)0x8a205ed0;//��Ŀ¼���ַ  dd ObpRootDirectoryObject		//������ֱ��Ӳ�����ˣ�ʵ��Ӧ��ͨ���������ȡObpRootDirectoryObject ��ֵ�ġ�ע�������õ�ʱ��һ��Ҫ�ģ���Ȼ����
	//��Ϊ���ö��б����������������38������������������������ڴ档����������Ϊʲô���������أ���Ϊ�ں���������̫��������ܵ����ں�ջ���ƻ��������Ҳ�������
	queue = (POBJECT_DIRECTORY_ENTRY*)ExAllocatePool(NonPagedPool, MAX_OBJECT_COUNT*sizeof(ULONG));
	if (!MmIsAddressValid(queue))
	{
		KdPrint(("queue is null.\n"));
		return;
	}
	u_front = u_rear = 0;
	for (u_index = 0; u_index < MAX_TABLE; u_index++)//dt _object_directory -b 8a405ed0		//�Ȱ�ObpRootDirectoryObject->HashBuckets��37��Ԫ�ؼ������
	{
		if (MmIsAddressValid(ObpRootDirectoryObject->HashBuckets[u_index]))
		{
			u_rear = (u_rear + 1) % MAX_OBJECT_COUNT;//�����β����  ���еĵ�0��� �Ӷ��еĵ�һ�ʼ����
			queue[u_rear] = (POBJECT_DIRECTORY_ENTRY)ObpRootDirectoryObject->HashBuckets[u_index];//����β��ֵ ���37���
			//KdPrint(("%x\n", queue[u_rear]));
		}
	}
	while (u_front != u_rear)	//������ͷ׷�϶���β��ʱ�����ǽ���ѭ����˵����������  ����ͷ��ʼ���ƣ�׷�϶���β
	{
		u_front = (u_front + 1) % MAX_OBJECT_COUNT;
		pobject_name_info = (POBJECT_HEADER_NAME_INFO)ObQueryNameInfo(queue[u_front]->Object);//ȡ�����е�Ԫ�أ�Ȼ��õ�object��Ȼ���ȡobject������
		if (MmIsAddressValid(pobject_name_info))
		{
			//Ϊ�˰�ȫ�������ж���pobject_name_info�Ƿ���Ч�ٴ�ӡ
			//KdPrint(("%X:::%wZ\n", queue[u_front]->Object, &pobject_name_info->Name));//�ں˶����ַ  37��Ĵ�����
		}
		//type_index ��ʾ�����Ӧ�Ķ���������ObTypeIndexTable�е��±�ֵ���������Directory���������±�ֵ��3������д��Ӳ���룬�����õ�ʱ������Ҫע�⣬���ܺ��ҵĲ�ͬ����ֻ����ʾ����û�кú��ж�(һ��Ƚ��������)��
		type_index = *(UCHAR*)((ULONG)queue[u_front]->Object - 0xc);//-0x18+c����-c
		//���̺��̶߳���ĵ�ַ
		if (type_index == 0x7 && type_index == 0x8)
		{
			KdPrint(("%X : index:%d\n", queue[u_front]->Object, type_index));//�ں˶����ַ  37��Ĵ�����
		}
		if (type_index == 0x3)//�ڵ���ں˶����ַ������ ����3��Ŀ¼����
		{
			//�����ж϶�����Ŀ¼�������ô���ǽ�һ����ȡ���Ŀ¼��������������ӽڵ���뵽������
			for (u_index = 0; u_index < MAX_TABLE; u_index++)
			{
				if (MmIsAddressValid(((POBJECT_DIRECTORY)queue[u_front]->Object)->HashBuckets[u_index]))
				{
					u_rear = (u_rear + 1) % MAX_OBJECT_COUNT;
					queue[u_rear] = (POBJECT_DIRECTORY_ENTRY)((POBJECT_DIRECTORY)queue[u_front]->Object)->HashBuckets[u_index];//��37������
				}
			}
		}
		if (queue[u_front]->ChainLink != NULL) //dt _OBJECT_DIRECTORY_ENTRY    ChainLink    Object    HashValue 
		{
			//��������38������һ���ӽڵ㣬��Ч�Ļ�Ҳ�������
			u_rear = (u_rear + 1) % MAX_OBJECT_COUNT;
			queue[u_rear] = queue[u_front]->ChainLink;//��һ���ڵ�
		}
	}
	ExFreePool(queue);
}
VOID MyUnload(PDRIVER_OBJECT        pDriverObject)
{
	KdPrint(("����ж�� �ɹ�\n"));
}
NTSTATUS DriverEntry(PDRIVER_OBJECT        pDriverObject, PUNICODE_STRING Reg_Path)
{
	EnumObjectDirectory();
	pDriverObject->DriverUnload = MyUnload;
	return STATUS_SUCCESS;
}

