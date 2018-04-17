
// 005TreeControl�ķ�װDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "005TreeControl�ķ�װ.h"
#include "005TreeControl�ķ�װDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy005TreeControl�ķ�װDlg �Ի���



CMy005TreeControl�ķ�װDlg::CMy005TreeControl�ķ�װDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy005TreeControl�ķ�װDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy005TreeControl�ķ�װDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeCtl);
}

BEGIN_MESSAGE_MAP(CMy005TreeControl�ķ�װDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMy005TreeControl�ķ�װDlg ��Ϣ�������

BOOL CMy005TreeControl�ķ�װDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_imgList.Create(32, 32, ILC_COLOR32, 1, 1);
	m_imgList.Add(m_hIcon);


	//
	m_treeCtl.SetImageList(&m_imgList, TVSIL_NORMAL);

	// 1. ����ڵ�.
	m_treeCtl.InsertItem(_T("���ڵ�1"), 0/*ͼ�������е�ͼ������*/);

	HTREEITEM hItem2 = m_treeCtl.InsertItem(L"���ڵ�2", 0);
	m_treeCtl.InsertItem(_T("���ڵ�3"), 0);

	m_treeCtl.InsertItem(_T("�ӽڵ�1"), 0, 0,
		hItem2 /*�½ڵ�ĸ��ڵ���*/);

	m_treeCtl.InsertItem(_T("�ӽڵ�2"), 0, 0, hItem2);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy005TreeControl�ķ�װDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy005TreeControl�ķ�װDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

