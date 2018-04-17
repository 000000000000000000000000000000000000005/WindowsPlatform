#include <ntifs.h>

//wrmsr  �޸�MSR�Ĵ���
//���Ȱ�Ҫ�޸ĵ�ֵ�ŵ�EAX�У���Ҫ�޸ĵĺŷŵ�ECX��
//����wrmsr���ͻ��eax��ֵд�뵽ecx��Ӧ��MSR�Ĵ�����

//rdmsr  ��ȡMSR�Ĵ���
//��Ҫ��ȡ��MSR�ĺţ��ŵ�ECX��
//����rdmsr�ͻ����Ӧ��MSR��ֵ�ŵ�EAX�С�

ULONG g_OldKiFastCallEntry;


PCLIENT_ID g_pClientPID;
PACCESS_MASK g_pAccessMask;
ULONG g_uSSDT_Index;
ULONG g_uProtectPID;
void _declspec(naked) MyKiFastCallEntry()
{
	// 1. ��EDXָ����û��ռ�ջ��ȡ����Ӧ������������ZwOpen-
	//     Process��ջ���죨��ʱ���迼���������ú�����ջ�������
	// +00 �û��ռ�Call���ص�ַ
	// +04 �û��ռ�Call���ص�ַ
	// +08 ����1 ( ProcessHandle�����̾�� )
	// +12 ����2 ( DesiredAccess������Ȩ�� )
	// +16 ����3 ( ObjectName���������� )
	// +20 ����4 ( ClientId�������н���PID���߳�ID�Ľṹ�� )
	_asm push DWORD PTR[EDX + 4 * 5];	// 4*5 = ����4
	_asm pop  g_pClientPID;	// �������4��ClientPID
	_asm push EDX;
	_asm add  DWORD PTR[ESP], 4 * 3;	// 4*3 = ����2
	_asm pop  g_pAccessMask;	// �������2��AccessMask

	// 2. ����ָ��PID�Ľ��̲�������
	_asm pushad;
	// 2.1 �жϷ�ΪZwOpenProcess�ĵ��ú�0xBE������ִ�б���
	_asm mov g_uSSDT_Index, eax;
	if (g_uSSDT_Index == 0xBE) {
		// 2.2 �ж������������Ƿ�Ϊ�ܱ������̣���ͬʱ�жϷ���Ȩ
		//     �����Ƿ�����ɽ�������Ȩ��PROCESS_TERMINATE��
		//     �ǵĻ��޸��������ȥ����Ȩ��
		if (((ULONG)g_pClientPID->UniqueProcess == g_uProtectPID))
		{
			*g_pAccessMask = 0;
		}
	}
	_asm popad;
	// 3. ��ת��ϵͳԭKiFastCallEntry������ִ��ʣ�����
	_asm jmp g_OldKiFastCallEntry;
}

void init()
{
	_asm
	{
		push eax;
		push ecx;
		mov ecx, 0x176;
		rdmsr;
		mov g_OldKiFastCallEntry, eax;
		pop ecx;
		pop eax;
	}
}


void OnHook()
{
	_asm
	{
		push eax;
		push ecx;
		mov ecx, 0x176;
		mov eax, MyKiFastCallEntry;
		wrmsr;
		pop ecx;
		pop eax;
	}
}

void OffHook()
{
	_asm
	{
		push eax;
		push ecx;
		mov ecx, 0x176;
		mov eax, g_OldKiFastCallEntry;
		wrmsr;
		pop ecx;
		pop eax;
	}
}

VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	UNREFERENCED_PARAMETER(pDriver);
	OffHook();
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pPath)
{
	UNREFERENCED_PARAMETER(pPath);
	g_uProtectPID = 3824;
	init();
	OnHook();
	pDriver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}

