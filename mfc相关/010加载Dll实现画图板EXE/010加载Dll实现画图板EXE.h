
// 010����Dllʵ�ֻ�ͼ��EXE.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy010����Dllʵ�ֻ�ͼ��EXEApp: 
// �йش����ʵ�֣������ 010����Dllʵ�ֻ�ͼ��EXE.cpp
//

class CMy010����Dllʵ�ֻ�ͼ��EXEApp : public CWinApp
{
public:
	CMy010����Dllʵ�ֻ�ͼ��EXEApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy010����Dllʵ�ֻ�ͼ��EXEApp theApp;