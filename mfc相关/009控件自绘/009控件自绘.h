
// 009�ؼ��Ի�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy009�ؼ��Ի�App: 
// �йش����ʵ�֣������ 009�ؼ��Ի�.cpp
//

class CMy009�ؼ��Ի�App : public CWinApp
{
public:
	CMy009�ؼ��Ի�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy009�ؼ��Ի�App theApp;