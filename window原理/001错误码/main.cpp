#include <windows.h>
#include <tchar.h>
#include <locale.h>

void TestFun()
{
	MessageBox(NULL, _T("TestFun"), _T("��ʾ"), MB_OK);
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs"); //֧�����ı��ػ�
	DWORD dwErrCode = 22;
	LPTSTR lpszErrorMsg;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwErrCode,
		0,
		(LPTSTR)&lpszErrorMsg,
		0,
		NULL
		);

	_tprintf(_T("%s\n"), lpszErrorMsg);
	_tprintf(_T("����id:%d\n"), GetCurrentProcessId());

	LocalFree(lpszErrorMsg);
	TestFun();
	system("pause");
	
	return 0;
}