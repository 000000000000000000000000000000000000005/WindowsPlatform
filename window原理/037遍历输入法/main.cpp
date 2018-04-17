#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <Imm.h>

#pragma  comment(lib, "Imm32.lib")


//����������
void EnumInputMethod(HKEY hRootKey, LPCTSTR szSubKey)
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
		TCHAR szInputKey[MAX_PATH] = { 0 };
		DWORD InputValueNo = _countof(szInputKey);
		TCHAR szInstallNo[MAX_PATH] = { 0 };
		DWORD dwcbData = sizeof(szInstallNo);
		DWORD dwType = 0;
		LONG lReturn = RegEnumValue(
			hResult,
			dwIndex,
			szInputKey,
			&InputValueNo,
			NULL,
			&dwType,
			(PBYTE)szInstallNo,
			&dwcbData
			);
		if (ERROR_SUCCESS != lReturn) break;

		//��ȡ���뷨������Ϣ
		TCHAR *szPartKeyPath = _T("SYSTEM\\CurrentControlSet\\Control\\Keyboard Layouts\\");
		TCHAR szFullRegKey[MAX_PATH] = { 0 };
		_stprintf_s(szFullRegKey, _countof(szFullRegKey), _T("%s%s"), szPartKeyPath, szInstallNo);
		_tprintf(_T("���뷨��NO:%s\n"), szInstallNo);

		HKEY hValueKey = NULL;
		RegOpenKeyEx(
			HKEY_LOCAL_MACHINE,
			szFullRegKey,
			0,
			KEY_QUERY_VALUE,
			&hValueKey);
		if (NULL != hValueKey)
		{
			TCHAR szRegValue[MAX_PATH] = { 0 };
			ZeroMemory(szRegValue, sizeof(szRegValue));
			DWORD dwRealLen = _countof(szRegValue);
			DWORD dwRegType;

			ZeroMemory(szRegValue, sizeof(szRegValue));
			//��ȡ���뷨��Ime�ļ�
			RegQueryValueEx(
				hValueKey,
				_T("Ime File"),
				0,
				&dwRegType,
				(LPBYTE)szRegValue,
				&dwRealLen);
			if (_tcscmp(szRegValue, _T("")) == 0)
			{
				RegQueryValueEx(
					hValueKey,
					_T("Layout Display Name"),
					0,
					&dwRegType,
					(LPBYTE)szRegValue,
					&dwRealLen);
				_tprintf(_T("���뷨��IME�ļ�:%s\n"), szRegValue);
			}
			else
			{
				_tprintf(_T("���뷨��IME�ļ�:%s\n"), szRegValue);
			}
			//��ȡ���뷨����
			RegQueryValueEx(
				hValueKey,
				_T("Layout Text"),
				0,
				&dwRegType,
				(LPBYTE)szRegValue,
				&dwRealLen);
			_tprintf(_T("���뷨������:%s\n"), szRegValue);

			ZeroMemory(szRegValue, sizeof(szRegValue));
			//��ȡ���뷨��Layout�ļ�
			RegQueryValueEx(
				hValueKey,
				_T("Layout File"),
				0,
				&dwRegType,
				(LPBYTE)szRegValue,
				&dwRealLen);
			_tprintf(_T("���뷨�Ĳ����ļ�:%s\n"), szRegValue);

			RegCloseKey(hValueKey);
		}
		dwIndex++;
	}
	if (NULL != hResult) RegCloseKey(hResult);
}


//��ȡ��ǰ���뷨
void GetCurrentImme()
{
	HKL hkl;
	TCHAR szInputName[MAX_PATH] = { 0 };
	hkl = GetKeyboardLayout(GetCurrentThreadId());
	if (ImmIsIME(hkl))
	{
		//��Ҫ�ڴ��ڳ������Ч
		ImmGetDescription(hkl, szInputName, _countof(szInputName));
		_tprintf(_T("��ǰ��������뷨:%s\n"), szInputName);
	}
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs"); //֧�����ı��ػ�
	system("pause");
	GetCurrentImme();
	EnumInputMethod(HKEY_CURRENT_USER, _T("Keyboard Layout\\Preload"));
	system("pause");
	return 0;
}