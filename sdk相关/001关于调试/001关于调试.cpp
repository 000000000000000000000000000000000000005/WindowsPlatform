// 001���ڵ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Dbg.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CreateDbgConsole();
	for (int i = 0; i < 100; i++)
	{
		PrintDbgInfo(_T("����:%s,  ����:%d"), _T("hzh01"), i);
	}
	return 0;

}

