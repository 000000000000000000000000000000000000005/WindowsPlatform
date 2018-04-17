
// 001����_ж������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "001����_ж������.h"
#include "001����_ж������Dlg.h"
#include "afxdialogex.h"
#include <Winsvc.h>
#include <shlwapi.h>  
#pragma comment(lib,"shlwapi.lib")  

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


// CMy001����_ж������Dlg �Ի���



CMy001����_ж������Dlg::CMy001����_ж������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy001����_ж������Dlg::IDD, pParent)
	, m_strSysPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy001����_ж������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strSysPath);
}

BEGIN_MESSAGE_MAP(CMy001����_ж������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy001����_ж������Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy001����_ж������Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy001����_ж������Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy001����_ж������Dlg ��Ϣ�������

BOOL CMy001����_ж������Dlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy001����_ж������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy001����_ж������Dlg::OnPaint()
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
HCURSOR CMy001����_ж������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy001����_ж������Dlg::OnBnClickedButton1()
{
	OPENFILENAME	openFile;
	TCHAR szFindFile[MAX_PATH] = { 0 };
	ZeroMemory(&openFile, sizeof(openFile));
	openFile.lStructSize = sizeof(openFile);
	openFile.lpstrFilter = _T("�����ļ�(*.sys)\0*.sys\0�����ļ�(*.*)\0*.*\0\0");
	openFile.lpstrFile = szFindFile;
	openFile.nMaxFile = MAX_PATH;
	openFile.nFilterIndex = 1;
	openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (!GetOpenFileName(&openFile))
	{
		DWORD dwErrCode = GetLastError();
		if (0 != dwErrCode)
		{
			CString strErrMsg;
			strErrMsg.Format(_T("���ļ�ʧ�ܣ�������:%d"), dwErrCode);
			AfxMessageBox(strErrMsg);
		}
		return;
	}
	m_strSysPath = szFindFile;
	UpdateData(FALSE);
}


void CMy001����_ж������Dlg::OnBnClickedButton2()
{

	SC_HANDLE hServiceMgr = NULL;//SCM�������ľ��  
	SC_HANDLE hServiceDDK = NULL;//NT��������ķ�����  
	DWORD dwRtn = 0;
	BOOL bRet = 0;

	if (m_strSysPath.IsEmpty())
	{
		AfxMessageBox(_T("����ѡ����������"));
		goto __EXIT;
	}

	hServiceMgr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == hServiceMgr)
	{
		AfxMessageBox(_T("����������ʧ��"));
		goto __EXIT;
	}

	TCHAR szDriverName[MAX_PATH] = { 0 };
	_tcscpy_s(szDriverName, _countof(szDriverName), m_strSysPath);
	PathStripPath(szDriverName);


	hServiceDDK = CreateService(hServiceMgr,
		szDriverName, //�����������ע����е�����    
		szDriverName, // ע������������ DisplayName ֵ    
		SERVICE_ALL_ACCESS, // ������������ķ���Ȩ��    
		SERVICE_KERNEL_DRIVER,// ��ʾ���صķ�������������    
		SERVICE_DEMAND_START, // ע������������ Start ֵ    
		SERVICE_ERROR_IGNORE, // ע������������ ErrorControl ֵ    
		m_strSysPath, // ע������������ ImagePath ֵ    
		NULL,  //GroupOrder HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\GroupOrderList  
		NULL,
		NULL,
		NULL,
		NULL);

	//�жϷ����Ƿ�ʧ��  
	if (NULL == hServiceDDK)
	{
		dwRtn = GetLastError();
		if (dwRtn != ERROR_IO_PENDING && dwRtn != ERROR_SERVICE_EXISTS)
		{
			//��������ԭ�򴴽�����ʧ��  
			AfxMessageBox(_T("CrateService() Faild"));
			goto __EXIT;
		}
		else
		{
			// ���������Ѿ����أ�ֻ��Ҫ��    
			hServiceDDK = OpenService(hServiceMgr, szDriverName, SERVICE_ALL_ACCESS);
			if (hServiceDDK == NULL)
			{
				AfxMessageBox(_T("OpenService() Faild! \n"));
				goto __EXIT;
			}
		}
	}
	//�����������  
	bRet = StartService(hServiceDDK, NULL, NULL);

	if(!bRet)
	{
		DWORD dwRtn = GetLastError();
		if (dwRtn != ERROR_IO_PENDING && dwRtn != ERROR_SERVICE_ALREADY_RUNNING)
		{
			AfxMessageBox(_T("StartService() Faild! \n"));
			goto __EXIT;
		}
		else
		{
			if (dwRtn == ERROR_IO_PENDING)
			{
				//�豸����ס  
				AfxMessageBox(_T("StartService() Faild ERROR_IO_PENDING ! \n"));
				goto __EXIT;
			}
			else
			{
				//�����Ѿ�����  
				AfxMessageBox(_T("StartService() Faild ERROR_SERVICE_ALREADY_RUNNING ! \n"));
				goto __EXIT;
			}
		}
	}
	else
	{
		AfxMessageBox(_T("StartService() Succ\n"));
	}

__EXIT:
	if (NULL != hServiceMgr) CloseServiceHandle(hServiceMgr);
	if (NULL != hServiceDDK) CloseServiceHandle(hServiceDDK);

}


void CMy001����_ж������Dlg::OnBnClickedButton3()
{
	SC_HANDLE hServiceMgr = NULL;//SCM�������ľ��  
	SC_HANDLE hServiceDDK = NULL;//NT��������ķ�����  
	if (m_strSysPath.IsEmpty())
	{
		AfxMessageBox(_T("����ѡ����������"));
		goto __EXIT;
	}

	SERVICE_STATUS SvrSta;
	//��SCM������  
	hServiceMgr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hServiceMgr == NULL)
	{
		//����SCM������ʧ��  
		AfxMessageBox(_T("OpenSCManager() Faild! \n"));
		goto __EXIT;
	}

	//����������Ӧ�ķ���  
	TCHAR szDriverName[MAX_PATH] = { 0 };
	_tcscpy_s(szDriverName, _countof(szDriverName), m_strSysPath);
	PathStripPath(szDriverName);
	hServiceDDK = OpenService(hServiceMgr, szDriverName, SERVICE_ALL_ACCESS);
	if (NULL==hServiceDDK)
	{
		//����������Ӧ�ķ���ʧ��  
		AfxMessageBox(_T("OpenService() Faild! \n"));
		goto __EXIT;
	}

	if (!ControlService(hServiceDDK, SERVICE_CONTROL_STOP, &SvrSta))
	{
		AfxMessageBox(_T("ControlService() Faild!\n"));
		goto __EXIT;
	}

	//��̬ж����������    
	if (!DeleteService(hServiceDDK))
	{
		//ж��ʧ��  
		AfxMessageBox(_T("DeleteSrevice() Faild!\n"));
	}
	else
	{
		AfxMessageBox(_T("DeleteService() Succ\n"));
	}


__EXIT:
	if (NULL != hServiceMgr) CloseServiceHandle(hServiceMgr);
	if (NULL != hServiceDDK) CloseServiceHandle(hServiceDDK);

}
