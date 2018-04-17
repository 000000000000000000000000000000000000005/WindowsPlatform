#include <windows.h>
#include <tchar.h>
#include   <stdarg.h>  
#include <Shlwapi.h>
#include "resource.h"
#pragma  comment(lib, "Shlwapi.lib")

void PrintDbgInfo(LPCTSTR lptstrFormat, ...);

INT_PTR CALLBACK DialogProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	);



//////////////////////////////////////////////
HINSTANCE g_hIntance = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_hIntance = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN_DLG), NULL, DialogProc);
	return 0;
}

INT_PTR CALLBACK DialogProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{

	}
		break;
	case WM_COMMAND:
	{
					   WORD wNotifyCode = HIWORD(wParam);
					   WORD wCtlID = LOWORD(wParam);
					   switch (wCtlID)
					   {
					   case IDC_BUTTON1:   //��ѡ��ķ���
					   {
											   /*
											    �����Ϊһ�飬��һ����group����Ϊtrue������Ϊfalse
											   */
											   for (int i = 0; i < 2; i++)
											   {
												   LRESULT lResult = SendDlgItemMessage(hwndDlg, IDC_RADIO6 + i, BM_GETCHECK, 0, 0);
												   if (lResult == BST_CHECKED)
												   {
													   TCHAR *szSex[] = { _T("��"), _T("Ů")};
													   MessageBox(hwndDlg, szSex[i], _T("�Ա�"), MB_OK);
													   break;
												   }
											   }


											   for (int i = 0; i < 2; i++)
											   {
												   LRESULT lResult = SendDlgItemMessage(hwndDlg, IDC_RADIO8 + i, BM_GETCHECK, 0, 0);
												   if (lResult == BST_CHECKED)
												   {
													   TCHAR *szSex[] = { _T("�й���"), _T("�����") };
													   MessageBox(hwndDlg, szSex[i], _T("����"), MB_OK);
													   break;
												   }
											   }





					   }
						   break;
					   default:
						   break;
					   }

	}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		break;
	default:
		break;
	}
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ���ַ�ת��Ϊ���ַ�(Unicode  --> ASCII)
#define  WCHAR_TO_CHAR(lpW_Char, lpChar) \
	WideCharToMultiByte(CP_ACP, NULL, lpW_Char, -1, lpChar, _countof(lpChar), NULL, FALSE);

// ���ַ�ת��Ϊ���ַ�(ASCII --> Unicode)
#define  CHAR_TO_WCHAR(lpChar, lpW_Char) \
	MultiByteToWideChar(CP_ACP, NULL, lpChar, -1, lpW_Char, _countof(lpW_Char));

//��ʽ�������Ϣ�ַ��������������
void SprintfDbgInfo(TCHAR *pOutBuff, int nMaxOutBuffSize, LPCTSTR lptstrFormat, va_list argList)
{
	//
	const int nFileBuffSize = 256;
	TCHAR fileNameBuff[nFileBuffSize];

	//�����ļ������к�
#ifdef UNICODE
	CHAR_TO_WCHAR(__FILE__, fileNameBuff);
	TCHAR *pFileName = PathFindFileName(fileNameBuff);
	_stprintf_s(pOutBuff, nMaxOutBuffSize - sizeof(TCHAR), _T("[mod:%s:line:%d]  ::  "), pFileName, __LINE__);
#else
	_tcscpy_s(fileNameBuff, __FILE__);
	TCHAR *pFileName = PathFindFileName(fileNameBuff);
	_stprintf_s(pOutBuff, nMaxOutBuffSize - sizeof(TCHAR), _T("[mod:%s:line:%d]  ::"), pFileName, __LINE__);
#endif

	//����������Ϣ
	int nHeadLen = _tcslen(pOutBuff);
	_vstprintf_s(pOutBuff + nHeadLen, nMaxOutBuffSize - sizeof(TCHAR)-nHeadLen * sizeof(TCHAR), lptstrFormat, argList);

	//���û���
	int nBodyLen = _tcslen(pOutBuff);
	_stprintf_s(pOutBuff + nBodyLen, nMaxOutBuffSize - sizeof(TCHAR)-nBodyLen * sizeof(TCHAR), _T("\r\n"));
}

//��ӡ��������Ϣ
void PrintDbgInfo(LPCTSTR lptstrFormat, ...)
{
	const int c_nMaxBuffSize = 4096;
	TCHAR outBuff[c_nMaxBuffSize];

	//�ѽ�������������
	va_list argList;
	va_start(argList, lptstrFormat);
	SprintfDbgInfo(outBuff, c_nMaxBuffSize, lptstrFormat, argList);
	va_end(argList);

	//�����Ϣ
	OutputDebugString(outBuff);
}
