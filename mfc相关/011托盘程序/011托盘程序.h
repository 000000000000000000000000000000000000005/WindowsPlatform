
// 011���̳���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy011���̳���App: 
// �йش����ʵ�֣������ 011���̳���.cpp
//

class CMy011���̳���App : public CWinApp
{
public:
	CMy011���̳���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy011���̳���App theApp;