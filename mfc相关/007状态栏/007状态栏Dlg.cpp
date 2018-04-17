
// 007״̬��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "007״̬��.h"
#include "007״̬��Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy007״̬��Dlg �Ի���



CMy007״̬��Dlg::CMy007״̬��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy007״̬��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy007״̬��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy007״̬��Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMy007״̬��Dlg ��Ϣ�������

BOOL CMy007״̬��Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	// ���״̬��
	// ʹ�õĲ���:
	// 1. ����һ��״̬�� : Create
	// 2. ��ӷ���(���÷�����ID):SetIndicators( panelId , 2 );
	// 3. ���÷�������Ϣ:SetPaneInfo
	//  3.1 ���÷����Ŀ��
	//  3.2 ���÷�������ʾ�ı�

	// 1. ����һ��״̬��
	m_statusBar.Create(this);

	// 2. ��״̬���ϴ�����ʾ�ı��ķ���
	UINT panelId[] = { WM_USER + 4, WM_USER + 5 };
	m_statusBar.SetIndicators(panelId, 2);

	m_statusBar.SetPaneInfo(0, WM_USER + 4, SBPS_NORMAL, 100);
	m_statusBar.SetPaneInfo(1, 0, SBPS_NORMAL, 500);
	m_statusBar.SetPaneText(0, L"״̬���ı�1");
	m_statusBar.SetPaneText(1, L"״̬���ı�2");

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy007״̬��Dlg::OnPaint()
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
HCURSOR CMy007״̬��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

