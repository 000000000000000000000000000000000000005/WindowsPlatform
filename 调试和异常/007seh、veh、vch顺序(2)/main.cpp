#include <windows.h>
#include <stdio.h>

LONG CALLBACK VehHandler(EXCEPTION_POINTERS* pException) {
	printf("VehHandler����������\n");
	return EXCEPTION_CONTINUE_SEARCH;   //����Ͷ�ݸ�seh  0
}

LONG CALLBACK VchHandler(
	_In_  PEXCEPTION_POINTERS pExceptionInfo
	)
{
	printf("VCH����������\n");
	DWORD dwOldProtect;
	VirtualProtect(pExceptionInfo->ExceptionRecord->ExceptionAddress, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	PBYTE pByte = (PBYTE)pExceptionInfo->ExceptionRecord->ExceptionAddress;
	memset(pByte, 0x90, 10);
	VirtualProtect(pExceptionInfo->ExceptionRecord->ExceptionAddress, 1, dwOldProtect, &dwOldProtect);
//	return EXCEPTION_CONTINUE_EXECUTION;  //����Ͷ�ݸ�seh  -1

	return EXCEPTION_CONTINUE_EXECUTION;
}


EXCEPTION_DISPOSITION  NTAPI SehHandle(
	_EXCEPTION_RECORD* pExceptionRecord,
	PVOID EstablishFrame,
	CONTEXT *ContextRecord,
	PVOID DispatcherContext)
{
	printf("SEH ������\n");

	return ExceptionContinueSearch;
}

typedef struct _MYTEB {
	EXCEPTION_REGISTRATION_RECORD* pExcetionHeader;
}MYTEB, *PMYTEB;


int main()
{
	AddVectoredExceptionHandler(TRUE, &VehHandler);

	AddVectoredContinueHandler(TRUE, &VchHandler);

	PMYTEB pMyTeb = (PMYTEB)NtCurrentTeb();

	EXCEPTION_REGISTRATION_RECORD sehNode = { 0 };
	sehNode.Next = pMyTeb->pExcetionHeader;
	sehNode.Handler = SehHandle;
	//
	pMyTeb->pExcetionHeader = &sehNode;

	//

	*(int*)0 = 0;

	//ժ����ӵ�seh
	pMyTeb->pExcetionHeader = pMyTeb->pExcetionHeader->Next;


	system("pause");
	return 0;
}