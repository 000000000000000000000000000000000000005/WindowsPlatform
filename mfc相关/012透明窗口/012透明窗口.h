
// 012͸������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy012͸������App: 
// �йش����ʵ�֣������ 012͸������.cpp
//

class CMy012͸������App : public CWinApp
{
public:
	CMy012͸������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy012͸������App theApp;