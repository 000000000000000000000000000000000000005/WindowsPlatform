#include "ImmAnti.h"
#include <windows.h>
#include <imm.h>

//////////////////////////////�ڲ��ӿ�///////////////////////////////////////
HHOOK s_hHook = NULL;
DWORD s_dwThreadID = 0;


//��Ϣ������
LRESULT CALLBACK MsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PMSG pmsg = (PMSG)lParam;

	if (pmsg->message == WM_IME_NOTIFY)
	{
		//IMN_CHANGECANDIDATE�����Ϣ�����뷨ѡ��ı仯
		if (pmsg->wParam & IMN_CHANGECANDIDATE)
		{
			GUITHREADINFO gui;
			gui.cbSize = sizeof(gui);
			GetGUIThreadInfo(s_dwThreadID, &gui);
		}
	}

	return CallNextHookEx(s_hHook, nCode, wParam, lParam);
}


//////////////////////////////����ӿ�///////////////////////////////////////
void ImmMonitor()
{
	DWORD dwSelfThradID = GetCurrentThreadId();
	s_dwThreadID = dwSelfThradID;
	s_hHook = SetWindowsHookEx(
		WH_GETMESSAGE,
		MsgProc,
		GetModuleHandle(NULL),	
		dwSelfThradID
		);
}
