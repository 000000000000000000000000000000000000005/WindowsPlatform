#include <windows.h>
#include <stdio.h>
#include "UnDocoumentApi.h"

bool IsDebug()
{
	// ��ȡTEB
	TEB* pTeb = NtCurrentTeb();

	// ��ȡPEB
	PEB* pPeb = pTeb->ProcessEnvironmentBlock;

	printf("NtGlobalFlag : %X\n", pPeb->NtGlobalFlag);

	// ��ȡ�Ƿ����ڵ����ֶε�ֵ.
	//���PEB��NtGlobalFlag�ֶ� , ��������� , ���ֶ�ֵΪx70
	return pPeb->NtGlobalFlag == 0x70;

	int nResult = 0;
	_asm
	{
		push eax;
		push ebx;
		mov eax, FS:[0x30];//�õ�PEB
		xor ebx, ebx;
		mov ebx, [eax + 0x68]; // ���PEB��NtGlobalFlag�ֶ�,���������,���ֶ�ֵΪx70
		mov nResult, ebx;
		pop ebx;
		pop eax;
	}
	if (nResult == 0x70)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main(int argc, char* argv[])
{
	bool bIsDebug = IsDebug();
	if (bIsDebug)
	{
		MessageBoxA(NULL, "���ڱ�����", "����", 0);
	}
	else
	{
		MessageBoxA(NULL, "���ںܰ�ȫ", "��ϲ", 0);
	}
	return 0;
}