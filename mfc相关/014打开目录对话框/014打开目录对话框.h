
// 014��Ŀ¼�Ի���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy014��Ŀ¼�Ի���App: 
// �йش����ʵ�֣������ 014��Ŀ¼�Ի���.cpp
//

class CMy014��Ŀ¼�Ի���App : public CWinApp
{
public:
	CMy014��Ŀ¼�Ի���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy014��Ŀ¼�Ի���App theApp;