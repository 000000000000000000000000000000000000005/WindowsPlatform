#include <windows.h>
#include <stdio.h>
#include "MsgHookInterface.h"

int main(int argc, char* argv[])
{
	DWORD dwThreadID = 0;
	printf("��������Ҫhook���߳�id:");
	scanf_s("%d", &dwThreadID);
	g_tid = dwThreadID;
	InstallHook();
	system("pause");
	UninstallHook();
	system("pause");

	return 0;
}