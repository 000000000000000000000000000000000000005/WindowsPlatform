
// 008�����������֤�ļ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy008�����������֤�ļ�App: 
// �йش����ʵ�֣������ 008�����������֤�ļ�.cpp
//

class CMy008�����������֤�ļ�App : public CWinApp
{
public:
	CMy008�����������֤�ļ�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy008�����������֤�ļ�App theApp;