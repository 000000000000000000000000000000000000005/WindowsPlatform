
// 007״̬��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy007״̬��App: 
// �йش����ʵ�֣������ 007״̬��.cpp
//

class CMy007״̬��App : public CWinApp
{
public:
	CMy007״̬��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy007״̬��App theApp;