#include <windows.h>
#include <stdio.h>

LONG CALLBACK VehHandler(EXCEPTION_POINTERS* pException) {
	printf("VehHandler����������\n");
// 	DWORD dwOldProtect;
// 	VirtualProtect(pException->ExceptionRecord->ExceptionAddress, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect);
// 	PBYTE pByte = (PBYTE)pException->ExceptionRecord->ExceptionAddress;
// 	memset(pByte, 0x90, 10);
// 	VirtualProtect(pException->ExceptionRecord->ExceptionAddress, 1, dwOldProtect, &dwOldProtect);
// 	//return EXCEPTION_CONTINUE_EXECUTION;  //����Ͷ�ݸ�seh  -1
	return EXCEPTION_CONTINUE_SEARCH;   //����Ͷ�ݸ�seh  0
}

LONG CALLBACK VchHandler(
	_In_  PEXCEPTION_POINTERS ExceptionInfo
	)
{
	printf("VCH����������\n");
	return EXCEPTION_CONTINUE_SEARCH;
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

// 	PMYTEB pMyTeb = (PMYTEB)NtCurrentTeb();
// 
// 	EXCEPTION_REGISTRATION_RECORD sehNode = { 0 };
// 	sehNode.Next = pMyTeb->pExcetionHeader;
// 	sehNode.Handler = SehHandle;
// 	//
// 	pMyTeb->pExcetionHeader = &sehNode;

	//
	__try
	{
		*(int*)0 = 0;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		printf("VC ��SEH ������\n");
	}



	//ժ����ӵ�seh
	//pMyTeb->pExcetionHeader = pMyTeb->pExcetionHeader->Next;


	system("pause");
	return 0;
}