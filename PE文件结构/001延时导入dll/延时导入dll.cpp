// ��ʱ����dll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

#include <windows.h>
#include <tchar.h>
#include "DllInterface.h"


void TestFunc()
{
	MessageBox(NULL, _T("��ʱ�������"), _T("����"), MB_OK);
}

