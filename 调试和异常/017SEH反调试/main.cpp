#include <windows.h>
#include <stdio.h>


#pragma warning(disable: 4733) 

void fun()
{
	printf("helloworld");
}
EXCEPTION_DISPOSITION ExpHandel_B(
	// �쳣״̬����
	EXCEPTION_RECORD              *pExceptionRecord,
	// �쳣ע����
	EXCEPTION_REGISTRATION_RECORD *pEstablisherFrame,
	// �����߳�������
	CONTEXT                       *pContextRecord,
	// �ַ��������ģ�ϵͳʹ�ã������ע��
	PVOID                         pDispatcherContext)
{
	pContextRecord->Eip = (DWORD)fun;
	// ���ء�������һ���쳣��������

	return ExceptionContinueExecution;

}

int main(int argc, char* argv[])
{
	_asm{
		push ExpHandel_B;
		push FS : [0];
		mov FS : [0], esp;
	}
	_asm
	{
		int 3;
	}
	MessageBoxA(0, 0, 0, 0);
	_asm

	{
		mov eax, FS:[0];
		mov eax, [eax];
		mov FS : [0], eax;
		pop eax;
		pop eax;
	}
	return 0;
}

