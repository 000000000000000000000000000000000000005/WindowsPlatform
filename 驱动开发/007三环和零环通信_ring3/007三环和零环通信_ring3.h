
// 007�������㻷ͨ��_ring3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy007�������㻷ͨ��_ring3App: 
// �йش����ʵ�֣������ 007�������㻷ͨ��_ring3.cpp
//

class CMy007�������㻷ͨ��_ring3App : public CWinApp
{
public:
	CMy007�������㻷ͨ��_ring3App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy007�������㻷ͨ��_ring3App theApp;