
// 003TabControl�ķ�װ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy003TabControl�ķ�װApp: 
// �йش����ʵ�֣������ 003TabControl�ķ�װ.cpp
//

class CMy003TabControl�ķ�װApp : public CWinApp
{
public:
	CMy003TabControl�ķ�װApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy003TabControl�ķ�װApp theApp;