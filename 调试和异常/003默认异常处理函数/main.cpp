#include <windows.h>
#include <tchar.h>
#include <stdio.h>


LONG CALLBACK UnhandleFilter(EXCEPTION_POINTERS* pException)
{

	DWORD dwRet = (DWORD)&pException;
	dwRet -= 4;
	dwRet = *(DWORD*)dwRet;
	printf("addr:0x%X\n", dwRet);
	printf("Ĭ���쳣���˺���������\n");
	system("pause");
	ExitProcess(0);
	return 0;
}

typedef PVOID(__stdcall *fpTypeRtlDecodePointer)(PVOID Pointer);

int main()
{	
	HMODULE hK32 = GetModuleHandle(_T("kernel32.dll"));
	HMODULE hNtdll = GetModuleHandle(_T("ntdll.dll"));
	DWORD dwValue = 0;
	fpTypeRtlDecodePointer  fpRtlDecodePointer = NULL;
	LPVOID lpResultAddr = NULL;


	dwValue = *((DWORD*)((DWORD)hK32 + 0xE0074));
	fpRtlDecodePointer = (fpTypeRtlDecodePointer)GetProcAddress(hNtdll, "RtlDecodePointer");
	lpResultAddr = fpRtlDecodePointer((LPVOID)dwValue);
	printf("Ĭ���쳣��������ַ:0x%0X\n", lpResultAddr);
	// ���ö�����˴�����ʽ
	SetUnhandledExceptionFilter(&UnhandleFilter);

	dwValue = *((DWORD*)((DWORD)hK32 + 0xE0074));
	fpRtlDecodePointer = (fpTypeRtlDecodePointer)GetProcAddress(hNtdll, "RtlDecodePointer");
	lpResultAddr = fpRtlDecodePointer((LPVOID)dwValue);
	printf("�����쳣����:0x%0X\n", lpResultAddr);
	if (lpResultAddr == (LPVOID)UnhandleFilter)
	{
		printf("���ҵ�UnhandleFilter\n");
	}



	//����Ϊ�ǵ���״̬
// 	__asm
// 	{
// 			mov  eax, dword ptr fs : [0x00000018]
// 			mov         eax, dword ptr[eax + 0x30]
// 			mov  byte ptr[eax + 0x2], 0
// 	}
// 
 	*(int*)0 = 0;
	system("pause");
	return 0;
}
