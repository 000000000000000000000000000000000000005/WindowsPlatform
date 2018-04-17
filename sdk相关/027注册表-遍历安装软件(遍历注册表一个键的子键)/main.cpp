#include <Windows.h>
#include <tchar.h>
#include <locale.h>

//������װ�����
void EnumInstallSoftWare()
{
	LPCTSTR szSubKey = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	//LPCTSTR szSubKey = _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	HKEY hRootKey = HKEY_LOCAL_MACHINE;
	HKEY hResult = NULL;  //�������մ򿪼��ľ��

	//1. ��һ���Ѿ����ڵ�ע����
	LONG lReturn = RegOpenKeyEx(
		hRootKey,
		szSubKey,
		0,
		KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE,
		&hResult
		);
	DWORD dwIndex = 0;
	//2. ѭ������UninstallĿ¼�µ��Ӽ�
	while (true)
	{
		DWORD dwKeyLen = MAX_PATH;
		TCHAR szNewKeyName[MAX_PATH];

		LONG lReturn = RegEnumKeyEx(
			hResult,
			dwIndex,
			szNewKeyName,
			&dwKeyLen,
			0,
			NULL,
			NULL,
			NULL
			);
		if (ERROR_SUCCESS != lReturn) break;
		//2.1 ͨ���õ��Ӽ�������ƴ�ӳ��µ��Ӽ�·��
		TCHAR szMidReg[MAX_PATH] = { 0 };
		_stprintf_s(szMidReg, _countof(szMidReg), _T("%s%s%s"), szSubKey, _T("\\"), szNewKeyName);
		//2.2 ���µ��Ӽ���ȡ����
		DWORD dwRegType;
		HKEY hValueKey = NULL;
		RegOpenKeyEx(
			hRootKey,
			szMidReg,
			0,
			KEY_QUERY_VALUE,
			&hValueKey);
		//2.3 ��ȡ���ֵ�����֡�
		TCHAR szRegValue[MAX_PATH];
		ZeroMemory(szRegValue, sizeof(szRegValue));
		DWORD dwRealLen = _countof(szRegValue);
		//��ȡ�������
		RegQueryValueEx(
			hValueKey,
			_T("DisplayName"),
			0,
			&dwRegType,
			(LPBYTE)szRegValue,
			&dwRealLen);
		_tprintf(_T("�������:%s\n"), szRegValue);
		//��ȡж��·��
		dwRealLen = _countof(szRegValue);
		ZeroMemory(szRegValue, sizeof(szRegValue));
		RegQueryValueEx(
			hValueKey,
			_T("UninstallString"),
			0,
			&dwRegType,
			(LPBYTE)szRegValue,
			&dwRealLen);
		_tprintf(_T("\tж��·��:%s\n"), szRegValue);
		if (NULL != hValueKey) RegCloseKey(hValueKey);

		dwIndex++;
	}
	if (NULL != hResult) 	RegCloseKey(hResult);
}


int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "chs"); //֧�����ı��ػ�
	_tprintf(_T("�����Ϣ:\n"));
	EnumInstallSoftWare();
	system("pause");
	return 0;
}