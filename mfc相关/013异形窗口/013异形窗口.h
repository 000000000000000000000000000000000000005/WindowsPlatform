
// 013���δ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy013���δ���App: 
// �йش����ʵ�֣������ 013���δ���.cpp
//

class CMy013���δ���App : public CWinApp
{
public:
	CMy013���δ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void On32771();
};

extern CMy013���δ���App theApp;