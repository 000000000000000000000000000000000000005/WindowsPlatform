
// 001����_ж������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy001����_ж������App: 
// �йش����ʵ�֣������ 001����_ж������.cpp
//

class CMy001����_ж������App : public CWinApp
{
public:
	CMy001����_ж������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy001����_ж������App theApp;