
// 006�����������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy006�����������App: 
// �йش����ʵ�֣������ 006�����������.cpp
//

class CMy006�����������App : public CWinApp
{
public:
	CMy006�����������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy006�����������App theApp;