// DialogTab2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "003TabControl�ķ�װ.h"
#include "DialogTab2.h"
#include "afxdialogex.h"


// DialogTab2 �Ի���

IMPLEMENT_DYNAMIC(DialogTab2, CDialog)

DialogTab2::DialogTab2(CWnd* pParent /*=NULL*/)
	: CDialog(DialogTab2::IDD, pParent)
{
	CreateDlg(MAKEINTRESOURCE(DialogTab2::IDD), pParent);
}

DialogTab2::~DialogTab2()
{
}

void DialogTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogTab2, CDialog)
END_MESSAGE_MAP()


// DialogTab2 ��Ϣ�������
