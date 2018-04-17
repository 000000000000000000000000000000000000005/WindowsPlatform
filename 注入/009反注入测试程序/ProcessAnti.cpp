#include "ProcessAnti.h"
#include "ProcessOperation.h"



//////////////////////////////�ڲ�����///////////////////////////////////////
static DWORD s_dwSelfID = 0; //��ǰ����id
static DWORD s_dwExplorerProcessID = 0; //������id
static bool s_bSuspendCreateProcess = false;

//
static bool EnumProcessFunc(IN  void *callBackParameter, IN PROCESSENTRY32* pProcessEntry)
{
	if (pProcessEntry->th32ProcessID == s_dwSelfID)
	{
		if (pProcessEntry->th32ParentProcessID != s_dwExplorerProcessID)
		{
			s_bSuspendCreateProcess = true;
			return true;
		}
	}
	return false;
}


//////////////////////////////����ӿ�///////////////////////////////////////
//��⸸����
void CheckSuspendCreateProcess()
{
	s_dwSelfID = GetCurrentProcessId();
	GetWindowThreadProcessId(FindWindow(TEXT("Progman"), NULL), &s_dwExplorerProcessID);
	EnumProcess(EnumProcessFunc, NULL);
}

bool IsNormalCreateProcess()
{
	return s_bSuspendCreateProcess;
}
