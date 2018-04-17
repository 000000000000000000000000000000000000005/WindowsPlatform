#include "RegAnti.h"
#include <windows.h>



//////////////////////////////����ӿ�///////////////////////////////////////
void GetAppInitDll(TCHAR *szDllNameBuff, int nccSize)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	ZeroMemory(szDllNameBuff, sizeof(TCHAR)* nccSize);
	/*
	ע�⣺32λ��64λע���key��һ��
	32λ��"SOFTWARE\\Wow6432Node\\Microsoft\\Windows NT\\CurrentVersion\\Windows"
	64λ��"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows"
	*/
	lResult = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		_T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows NT\\CurrentVersion\\Windows"),
		0,
		KEY_ALL_ACCESS,
		&hKey
		);
	if (ERROR_SUCCESS != lResult) return;

	//��ȡ·������
	DWORD dwRegType = 0;
	TCHAR szRegValue[MAX_PATH];
	ZeroMemory(szRegValue, sizeof(szRegValue));
	DWORD dwRealLen = _countof(szRegValue);
	//��ȡ�������
	RegQueryValueEx(
		hKey,
		_T("AppInit_DLLs"),
		0,
		&dwRegType,
		(LPBYTE)szRegValue,
		&dwRealLen);

	_tcscpy_s(szDllNameBuff, nccSize, szRegValue);
}
