#include <windows.h>
#include <stdio.h>
#include "InlineHook.h"
#include <tchar.h>



void Func1()
{
	MessageBox(0, _T("ԭʼ����"), _T("��ʾ"), MB_OK);
}

void _stdcall HookedProc(HookContex* hookContex)
{
	TCHAR szHookBuff[MAX_PATH] = { 0 };

	_stprintf_s(szHookBuff, _countof(szHookBuff),
		_T("��ִ�е�hook���ʱ������Ĵ�����ֵ:\n\
		Eax = 0x%08X\n\
		Ecx = 0x%08X\n\
		Edx = 0x%08X\n\
		Ebx = 0x%08X\n\
		Esi = 0x%08X\n\
		Edi = 0x%08X\n\
		Ebp = 0x%08X\n\
		Esp = 0x%08X\n\
		EFlags = 0x%08X\n,�����ֱ��������������޸ļĴ�������ִ��ԭ���ĵ�ַ��ʱ�򣬼Ĵ������������޸ĵ�ֵ\n"),
		hookContex->uEax,
		hookContex->uEcx,
		hookContex->uEdx,
		hookContex->uEbx,
		hookContex->uEsi,
		hookContex->uEdi,
		hookContex->uEbp,
		hookContex->uEsp,
		hookContex->uEflags
		);

	MessageBox(0, szHookBuff, _T("��ʾ"), MB_OK);
}


int main()
{
	InlineHookSt inlineSt;
	InitInlineHook(&inlineSt, Func1, HookedProc);
	InstallInlineHook(&inlineSt);

	//���԰�װhook��Ч��
	Func1();

	//ж�ع��ӵ�ִ��Ч��
	UninstallInlineHook(&inlineSt);
	Func1();
	return 0;
}
