#include <windows.h>
#include <stdio.h>

LONG CALLBACK UnhandleFilter(EXCEPTION_POINTERS* pException) {
	printf("Ĭ���쳣���˺���������\n");
	ExitProcess(0);
	return 0;
}

typedef struct _MYTEB {
	EXCEPTION_REGISTRATION_RECORD* pExcetionHeader;
}MYTEB, *PMYTEB;

int main(int argc, char* argv[])
{

	// ����Ĭ���쳣������
	SetUnhandledExceptionFilter(&UnhandleFilter);
	printf("Ĭ���쳣��������ַ:0x%X\n", UnhandleFilter);

	PMYTEB pMyTeb = (PMYTEB)NtCurrentTeb();
	PEXCEPTION_REGISTRATION_RECORD pExceptionRecode = pMyTeb->pExcetionHeader;

	while ((PEXCEPTION_REGISTRATION_RECORD)(-1) != pExceptionRecode)
	{
		printf("nowrecord:0x%08X, next record:0x%08X, handle:0x%08X\n", 
			pExceptionRecode, 
			pExceptionRecode->Next,
			pExceptionRecode->Handler);
		pExceptionRecode = pExceptionRecode->Next;
	}
	return 0;
}