// DialogTab1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "003TabControl�ķ�װ.h"
#include "DialogTab1.h"
#include "afxdialogex.h"


// DialogTab1 �Ի���

IMPLEMENT_DYNAMIC(DialogTab1, CDialog)

DialogTab1::DialogTab1(CWnd* pParent /*=NULL*/)
	: CDialog(DialogTab1::IDD, pParent)
{
	CreateDlg(MAKEINTRESOURCE(DialogTab1::IDD), pParent);
}

DialogTab1::~DialogTab1()
{
}

void DialogTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogTab1, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogTab1::OnBnClickedButton1)
END_MESSAGE_MAP()


// DialogTab1 ��Ϣ�������


void DialogTab1::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
