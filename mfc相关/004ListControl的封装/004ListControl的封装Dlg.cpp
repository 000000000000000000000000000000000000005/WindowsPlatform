
// 004ListControl�ķ�װDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "004ListControl�ķ�װ.h"
#include "004ListControl�ķ�װDlg.h"
#include "afxdialogex.h"
#include "Dbg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy004ListControl�ķ�װDlg �Ի���



CMy004ListControl�ķ�װDlg::CMy004ListControl�ķ�װDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy004ListControl�ķ�װDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy004ListControl�ķ�װDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtl);
}

BEGIN_MESSAGE_MAP(CMy004ListControl�ķ�װDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMy004ListControl�ķ�װDlg::OnClickList1)
END_MESSAGE_MAP()


// CMy004ListControl�ķ�װDlg ��Ϣ�������

BOOL CMy004ListControl�ķ�װDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_imageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 4, 1);
	for (int i = 0; i < 4; i++)
	{
		HICON hIcon1 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1 + i));
		m_imageList.Add(hIcon1);
	}

	//
	m_listCtl.SetGridStyle();
	m_listCtl.SetImageList(&m_imageList, LVSIL_SMALL);
	//
	m_listCtl.InsertColumn(0, _T("PID"), 100);
	m_listCtl.InsertColumn(1, _T("������"), 100);
	m_listCtl.InsertColumn(2, _T("·��"), 200);

	m_listCtl.SetItemText(0, 0, 3, _T("1001"), _T("QQ"), _T("c:\\qq.exe"));
	m_listCtl.SetItemText(1, 1, 3, _T("1002"), _T("Ѹ��"), _T("d:\\thunkder.exe"));
	srand((unsigned int )time(NULL));
	for (int i = 2; i < 100; i++)
	{
		int nRandomValue1 = rand();
		int nRandomValue2 = rand();
		int nRandomValue3 = rand();
		TCHAR szValue1Buff[MAX_PATH];
		TCHAR szValue2Buff[MAX_PATH];
		TCHAR szValue3Buff[MAX_PATH];

		_itot_s(nRandomValue1, szValue1Buff, _countof(szValue1Buff), 10);
		_itot_s(nRandomValue2, szValue2Buff, _countof(szValue2Buff), 10);
		_itot_s(nRandomValue3, szValue3Buff, _countof(szValue3Buff), 10);

		m_listCtl.SetItemText(i, i % 4, 3, szValue1Buff, szValue2Buff, szValue3Buff);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy004ListControl�ķ�װDlg::OnPaint()
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
HCURSOR CMy004ListControl�ķ�װDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy004ListControl�ķ�װDlg::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	PrintDbgInfo(_T("��ǰ�б����:%d��, %d��"), m_listCtl.GetRowNum(), m_listCtl.GetColNum());

	//
	std::vector<int > vecRow;
	m_listCtl.GetSelectedRow(vecRow);
	for (size_t i = 0; i < vecRow.size(); i++)
	{
		PrintDbgInfo(_T("��ǰѡ�е�Ϊ%d��"), vecRow[i]);
	}
	//
	for (int i = 0; i < m_listCtl.GetColNum(); i++)
	{
		CString strText = m_listCtl.GetSpecItemText(vecRow[0], i);
		PrintDbgInfo(_T("%d��%d�е��ı�Ϊ:%s"), vecRow[0], i, strText);
	}




}
