#include <windows.h>


int main(int argc, char* argv[])
{
	// API�ڲ�ʵ���Ǽ��PEB��BeingDebugged�ֶ�
	BOOL bIsDebug = IsDebuggerPresent();

	/*
		76B938F0 64 A1 18 00 00 00    mov         eax, dword ptr fs : [00000018h]
		76B938F6 8B 40 30             mov         eax, dword ptr[eax + 30h]
		76B938F9 0F B6 40 02          movzx       eax, byte ptr[eax + 2]
		*/

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