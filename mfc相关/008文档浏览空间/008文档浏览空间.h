
// 008�ĵ�����ռ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy008�ĵ�����ռ�App: 
// �йش����ʵ�֣������ 008�ĵ�����ռ�.cpp
//

class CMy008�ĵ�����ռ�App : public CWinApp
{
public:
	CMy008�ĵ�����ռ�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy008�ĵ�����ռ�App theApp;