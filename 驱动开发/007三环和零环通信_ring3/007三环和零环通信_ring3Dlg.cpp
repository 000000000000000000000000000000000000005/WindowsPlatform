
// 007�������㻷ͨ��_ring3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "007�������㻷ͨ��_ring3.h"
#include "007�������㻷ͨ��_ring3Dlg.h"
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


// CMy007�������㻷ͨ��_ring3Dlg �Ի���



CMy007�������㻷ͨ��_ring3Dlg::CMy007�������㻷ͨ��_ring3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy007�������㻷ͨ��_ring3Dlg::IDD, pParent),
	m_hDevice(NULL)
	, m_strThreadID(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy007�������㻷ͨ��_ring3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strThreadID);
}

BEGIN_MESSAGE_MAP(CMy007�������㻷ͨ��_ring3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy007�������㻷ͨ��_ring3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy007�������㻷ͨ��_ring3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy007�������㻷ͨ��_ring3Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy007�������㻷ͨ��_ring3Dlg ��Ϣ�������

BOOL CMy007�������㻷ͨ��_ring3Dlg::OnInitDialog()
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
	DWORD dwThreadID =  GetCurrentThreadId();
	m_strThreadID.Format(_T("%d"), dwThreadID);
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy007�������㻷ͨ��_ring3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy007�������㻷ͨ��_ring3Dlg::OnPaint()
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
HCURSOR CMy007�������㻷ͨ��_ring3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#define LINK_NAME L"\\\\.\\15PBHello"

void CMy007�������㻷ͨ��_ring3Dlg::OnBnClickedButton1()
{
	m_hDevice = CreateFileW(
		LINK_NAME,
		GENERIC_ALL,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (NULL == m_hDevice || INVALID_HANDLE_VALUE == m_hDevice)
	{
		AfxMessageBox(_T("�޷����豸"));
	}
}


void CMy007�������㻷ͨ��_ring3Dlg::OnBnClickedButton2()
{
	if (NULL != m_hDevice)
	{
		DWORD dwWrite;
		char szMsg[] = "hello 15pb";
		WriteFile(m_hDevice, szMsg, strlen(szMsg) + 1, &dwWrite, NULL);
		//
		CString strFormat;
		strFormat.Format(_T("real write:%d"), dwWrite);
		AfxMessageBox(strFormat);

	}
}


void CMy007�������㻷ͨ��_ring3Dlg::OnBnClickedButton3()
{
	if (NULL != m_hDevice)
	{
		DWORD dwRealRead;
		wchar_t buff[MAX_PATH] = { 0 };
		ReadFile(m_hDevice, buff, sizeof(buff), &dwRealRead, NULL);
		CString strFormat;
		strFormat.Format(_T("�յ�����:%s,, realread:%d"), buff, dwRealRead);
		AfxMessageBox(strFormat);
	}
}
