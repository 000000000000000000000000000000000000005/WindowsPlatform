
// 006�����������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "006�����������.h"
#include "006�����������Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy006�����������Dlg �Ի���



CMy006�����������Dlg::CMy006�����������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy006�����������Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy006�����������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy006�����������Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMy006�����������Dlg ��Ϣ�������

BOOL CMy006�����������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//
	// ����:����
	m_toolBar.Create(this);

	//HBITMAP hBitmap = LoadBitmap(AfxGetInstanceHandle(), (TCHAR*)IDB_BITMAP1);
	UINT buttonId[] = { WM_USER + 1, WM_USER + 2, WM_USER + 3 };
	m_toolBar.SetButtons(buttonId, 3);
	m_toolBar.LoadBitmap(IDR_TOOLBAR1);
	//���ù�����
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy006�����������Dlg::OnPaint()
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
HCURSOR CMy006�����������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




BOOL CMy006�����������Dlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO:  �ڴ����ר�ô����/����û���
	DWORD dwID = LOWORD(wParam);
	switch (dwID) {
	case WM_USER + 1:
		MessageBox(L"��������ť1"); break;

	case WM_USER + 2:
		MessageBox(L"��������ť2"); break;

	case WM_USER + 3:
		MessageBox(L"��������ť3"); break;

	default:
		break;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}
