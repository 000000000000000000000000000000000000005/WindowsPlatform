
// 004ListControl�ķ�װ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy004ListControl�ķ�װApp: 
// �йش����ʵ�֣������ 004ListControl�ķ�װ.cpp
//

class CMy004ListControl�ķ�װApp : public CWinApp
{
public:
	CMy004ListControl�ķ�װApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy004ListControl�ķ�װApp theApp;