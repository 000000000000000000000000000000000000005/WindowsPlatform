
// 013���δ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "013���δ���.h"
#include "013���δ���Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy013���δ���Dlg �Ի���



CMy013���δ���Dlg::CMy013���δ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy013���δ���Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy013���δ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy013���δ���Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CMy013���δ���Dlg ��Ϣ�������

BOOL CMy013���δ���Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	// 1. �����չ���
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, dwStyle | WS_EX_LAYERED);

	// 2. ����͸��ɫ(��Ϊ��ɫ)
	SetLayeredWindowAttributes(RGB(0, 0, 0), 0, LWA_COLORKEY);

	// 3. ��WM_PAIN��,��Ԥ�Ȼ��õ�ͼƬ���Ƶ�����
	m_bgimg.LoadFromResource(AfxGetInstanceHandle(),
		IDB_BITMAP1);

	//4.  ��wm_paint��ͼƬ���쿽����Ŀ��DC��(�ͻ���DC)
	
	//5. OnNcHitTest,��Ҫ������WM_NCHITTEST��Ϣ����Ȼû���϶�����



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy013���δ���Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy013���δ���Dlg::OnPaint()
{
	CClientDC dc(this);
	CRect rt;
	GetClientRect(rt);
	if (IsIconic())
	{
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
		// 4. ��ͼƬ���쿽����Ŀ��DC��(�ͻ���DC)
		m_bgimg.StretchBlt(dc.m_hDC, rt, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy013���δ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CMy013���δ���Dlg::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ScreenToClient(&point);
	if (point.y >= 0 && point.y <= 25)
	{
		return HTCAPTION;
	}
	else
	{
		return HTCLIENT;
	}

}


void CMy013���δ���Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu *pSubMenu = menu.GetSubMenu(0);

	POINT cusorPoint;
	GetCursorPos(&cusorPoint);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, cusorPoint.x, cusorPoint.y, this);

	CDialogEx::OnRButtonDown(nFlags, point);
}
