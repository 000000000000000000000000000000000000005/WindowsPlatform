
// 015���ļ��Ի���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy015���ļ��Ի���App: 
// �йش����ʵ�֣������ 015���ļ��Ի���.cpp
//

class CMy015���ļ��Ի���App : public CWinApp
{
public:
	CMy015���ļ��Ի���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy015���ļ��Ի���App theApp;