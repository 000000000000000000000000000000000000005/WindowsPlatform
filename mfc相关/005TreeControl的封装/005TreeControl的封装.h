
// 005TreeControl�ķ�װ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy005TreeControl�ķ�װApp: 
// �йش����ʵ�֣������ 005TreeControl�ķ�װ.cpp
//

class CMy005TreeControl�ķ�װApp : public CWinApp
{
public:
	CMy005TreeControl�ķ�װApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy005TreeControl�ķ�װApp theApp;