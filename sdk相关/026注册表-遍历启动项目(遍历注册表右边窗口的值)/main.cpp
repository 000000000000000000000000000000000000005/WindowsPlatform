#include <Windows.h>
#include <tchar.h>
#include <locale.h>

//ö�����������ýṹ
typedef struct
{
	HKEY hRoot;
	LPTSTR lpSubKey;
}EnumStartupItemConfig;

//����������
void EnumStartup(HKEY hRootKey, LPCTSTR szSubKey)
{
	HKEY hResult = NULL;  //�������մ򿪼��ľ��

	LONG lReturn = RegOpenKeyEx(
		hRootKey,
		szSubKey,
		0,
		KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE,
		&hResult
		);
	if (ERROR_SUCCESS != lReturn) return;
	DWORD dwIndex = 0;
	while (true)
	{
		TCHAR szStartupName[MAX_PATH] = { 0 };
		DWORD dwccValueName = _countof(szStartupName);
		TCHAR dwStartupPath[MAX_PATH] = { 0 };
		DWORD dwcbData = sizeof(dwStartupPath);
		DWORD dwType = 0;
		LONG lReturn = RegEnumValue(
			hResult,
			dwIndex,
			szStartupName,
			&dwccValueName,
			NULL,
			&dwType,
			(PBYTE)dwStartupPath,
			&dwcbData
			);
		if (ERROR_SUCCESS != lReturn) break;
		_tprintf(_T("%s\n"), szStartupName);
		dwIndex++;
	}
	if (NULL != hResult) RegCloseKey(hResult);
}

//����������
void EnumStartup()
{
	EnumStartupItemConfig startupItemCfg[] = {
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run") },
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run") },
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce") },
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce") },
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunServices") },
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx") },
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows") },
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\WinLogon") },
		{ HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Policies\\System") },
		//
		{ HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run") },
		{ HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run") },
		{ HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce") },
		{ HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce") },
		{ HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunServices") },
		{ HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx") }
	};

	for (int i = 0; i < _countof(startupItemCfg); i++)
	{
		startupItemCfg[i].hRoot;
		startupItemCfg[i].lpSubKey;
		EnumStartup(startupItemCfg[i].hRoot, startupItemCfg[i].lpSubKey);
	}
}



int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "chs"); //֧�����ı��ػ�
	_tprintf(_T("������Ŀ:\n"));
	EnumStartup();
	system("pause");
	return 0;
}