// 010����Dllʵ�ֻ�ͼ��_��ֱ��.h : 010����Dllʵ�ֻ�ͼ��_��ֱ�� DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App
// �йش���ʵ�ֵ���Ϣ������� 010����Dllʵ�ֻ�ͼ��_��ֱ��.cpp
//

class CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App : public CWinApp
{
public:
	CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
