
// 002�����󶨺ͷ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "002�����󶨺ͷ���.h"
#include "002�����󶨺ͷ���Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy002�����󶨺ͷ���Dlg �Ի���



CMy002�����󶨺ͷ���Dlg::CMy002�����󶨺ͷ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy002�����󶨺ͷ���Dlg::IDD, pParent)
	, m_strEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy002�����󶨺ͷ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
}

BEGIN_MESSAGE_MAP(CMy002�����󶨺ͷ���Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy002�����󶨺ͷ���Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy002�����󶨺ͷ���Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMy002�����󶨺ͷ���Dlg ��Ϣ�������

BOOL CMy002�����󶨺ͷ���Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy002�����󶨺ͷ���Dlg::OnPaint()
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
HCURSOR CMy002�����󶨺ͷ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy002�����󶨺ͷ���Dlg::OnBnClickedButton1()
{
	CString strOld;
	m_edit.GetWindowText(strOld);
	CString strNew;
	strNew.Format(_T("%s\r\n���Ա����󶨣����� edit���ͱ���"), strOld.GetBuffer(0));
	m_edit.SetWindowText(strNew);
}


void CMy002�����󶨺ͷ���Dlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	CString strOld = m_strEdit;
	m_strEdit.Format(_T("%s\r\n���Ա����󶨣����� Cstring���ͱ���"), strOld.GetBuffer(0));
	UpdateData(FALSE);
}
