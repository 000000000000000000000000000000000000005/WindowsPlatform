#pragma once

#include <windows.h>


#ifdef MESSAGEHOOKDLL_EXPORTS
#define MESSAGEHOOKDLL_API extern"C" __declspec(dllexport)
#else
#define MESSAGEHOOKDLL_API extern"C" __declspec(dllimport)
#endif

// ��װ����
MESSAGEHOOKDLL_API int InstallHook();

// ж�ع���
MESSAGEHOOKDLL_API int UninstallHook();

//��Ҫ�ҹ����߳�id
MESSAGEHOOKDLL_API extern  DWORD g_tid;