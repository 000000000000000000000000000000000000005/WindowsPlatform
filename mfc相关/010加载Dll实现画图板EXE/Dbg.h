#pragma  once
#include <windows.h>


//��ʽ�������Ϣ�ַ�������������� =>��������������԰ѳ������־��Ϣ��λ���ļ���ȥ
void SprintfDbgInfo(TCHAR *pOutBuff, int nMaxOutBuffSize, LPCTSTR lptstrFormat, va_list argList);


//��ӡ��������Ϣ
void PrintDbgInfo(LPCTSTR lptstrFormat, ...);

//��ӡ��������Ϣ��Ϣ
void PrintWindowsMsgInfo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
