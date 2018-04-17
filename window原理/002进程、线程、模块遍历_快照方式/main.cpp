#include <locale.h>
#include "ProcessOperation.h"
#include <tchar.h>

bool EnumModuleFunc(void *callBackParameter, MODULEENTRY32* pModuleEntry)
{
	_tprintf(_T("\t\thModule:%x, szModule:%s\n"), pModuleEntry->modBaseAddr, pModuleEntry->szModule);
	return false;
}

bool EnumProcessFunc(void *callBackParameter, PROCESSENTRY32* pProcessEntry)
{
	_tprintf(_T("����id:%d, ������:%s\n"), pProcessEntry->th32ProcessID, pProcessEntry->szExeFile);
	//ö��ģ����Ϣ
	EnumModule(pProcessEntry->th32ProcessID, EnumModuleFunc, NULL);
	return false;
}

bool EnumThreadFunc(void *callBackParameter, THREADENTRY32* pThreadEntry)
{
	_tprintf(_T("��������id:%d, �߳�id:%d\n"), pThreadEntry->th32OwnerProcessID, pThreadEntry->th32ThreadID);
	return false;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs");

	//��������
	EnumProcess(EnumProcessFunc, NULL);

	//�����߳�
	EnumThread(EnumThreadFunc, NULL);

	return 0;
}