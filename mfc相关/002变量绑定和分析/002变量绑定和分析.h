
// 002�����󶨺ͷ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy002�����󶨺ͷ���App: 
// �йش����ʵ�֣������ 002�����󶨺ͷ���.cpp
//

class CMy002�����󶨺ͷ���App : public CWinApp
{
public:
	CMy002�����󶨺ͷ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy002�����󶨺ͷ���App theApp;