#include <windows.h>
#include <stdio.h>

//1. ����ͷ�ļ�
#include "detours/detours.h"

//2. ������̬��
#ifdef _X64
#pragma comment(lib,"detours/lib.X64/detours.lib")
#else
#pragma comment(lib,"detours/lib.X86/detours.lib")
#endif // _X64

typedef int (WINAPI *fnMessageBox)(
_In_opt_ HWND hWnd,
_In_opt_ LPCWSTR lpText,
_In_opt_ LPCWSTR lpCaption,
_In_ UINT uType);

fnMessageBox g_pSrcMessageBoxW = NULL;

DWORD WINAPI MyMessageBox(HWND hWnd, TCHAR* pText, TCHAR* pTitle, DWORD type) 
{
	g_pSrcMessageBoxW(0, L"�ڵ����MessageBox�е����˿�", L"��ʾ", 0);
	return 0;
}



int main(int argc, char* argv[])
{

	MessageBoxW(0, L"���溯��", L"��ʾ", 0);

	//3. ִ��hook
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	g_pSrcMessageBoxW = MessageBoxW;
	DetourAttach((LPVOID*)&g_pSrcMessageBoxW, MyMessageBox);
	// �ύ���еĸ���(���е�HOOK)
	if (DetourTransactionCommit() == NO_ERROR)
	{
		printf("hook�ɹ�");
	}

	//4. ����hookЧ��
	MessageBoxW(0, L"���溯��", L"��ʾ", 0);


	//5. ж�ع���
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((LPVOID*)&g_pSrcMessageBoxW, &MyMessageBox);
	DetourTransactionCommit();


	//6.�ڴβ���
	MessageBoxW(0, L"���溯��", L"��ʾ", 0);



	return 0;
}