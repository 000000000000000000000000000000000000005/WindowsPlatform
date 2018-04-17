#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	HKEY hKey = NULL;
	LONG lResult = 0;

	//1. ��ע�����
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
	if (ERROR_SUCCESS != lResult)
	{
		printf("��ע���ʧ��");
		goto __EXIT;
	}


	//2. ����AppInit_DLLs�ļ�ֵΪ���ǵ�Dll
	TCHAR szDllPath[] = _T("F:\\15pb��ϰ\\Windowsƽ̨\\Debug\\001����ע��Ķ�̬��.dll");
	lResult = RegSetValueEx(hKey,
		_T("AppInit_DLLs"),
		0,
		REG_SZ,
		(BYTE*)szDllPath,
		sizeof(szDllPath)
		);
	if (lResult != ERROR_SUCCESS)
	{
		printf("����ע���ʧ��");
		goto __EXIT;
	}


__EXIT:
	if (hKey != NULL)  RegCloseKey(hKey);


	return 0;
}