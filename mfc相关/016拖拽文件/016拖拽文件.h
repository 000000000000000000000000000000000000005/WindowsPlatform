
// 016��ק�ļ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy016��ק�ļ�App: 
// �йش����ʵ�֣������ 016��ק�ļ�.cpp
//

class CMy016��ק�ļ�App : public CWinApp
{
public:
	CMy016��ק�ļ�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy016��ק�ļ�App theApp;