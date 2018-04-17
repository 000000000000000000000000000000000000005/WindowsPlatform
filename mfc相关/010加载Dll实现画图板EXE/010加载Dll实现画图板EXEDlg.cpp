
// 010����Dllʵ�ֻ�ͼ��EXEDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "010����Dllʵ�ֻ�ͼ��EXE.h"
#include "010����Dllʵ�ֻ�ͼ��EXEDlg.h"
#include "afxdialogex.h"
#include "Dbg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy010����Dllʵ�ֻ�ͼ��EXEDlg �Ի���



CMy010����Dllʵ�ֻ�ͼ��EXEDlg::CMy010����Dllʵ�ֻ�ͼ��EXEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy010����Dllʵ�ֻ�ͼ��EXEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy010����Dllʵ�ֻ�ͼ��EXEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy010����Dllʵ�ֻ�ͼ��EXEDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void GetExeRootPath(TCHAR* pszDirPath, int nccLen)
{
	TCHAR szBuff[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, szBuff, sizeof(szBuff)-sizeof(TCHAR));
	::PathRemoveFileSpec(szBuff);
	_stprintf_s(pszDirPath, nccLen - 1, _T("%s%s"), szBuff, "\\");
}


BOOL EnumPlugin(void *Parameter, FileNode *pNode)
{
	CMy010����Dllʵ�ֻ�ͼ��EXEDlg *pDlg = (CMy010����Dllʵ�ֻ�ͼ��EXEDlg*)Parameter;
	pDlg->DoPluginFile(pNode);
	return FALSE;
}

void  CMy010����Dllʵ�ֻ�ͼ��EXEDlg::DoPluginFile(FileNode *pNode)
{
	HMODULE hDll = NULL;
	if (pNode->bIsDir) goto __NORMAL_END;
	// ����DLL�ļ�
	hDll = LoadLibrary(pNode->szFileName);
	if (NULL == hDll) goto __ERROR_END;
	// ��ȡ��������
	typedef const TCHAR*(*GETNAME)();
	GETNAME pfnGetName = (GETNAME)GetProcAddress(hDll, "GetName");
	if (NULL == pfnGetName) goto __ERROR_END;
	//ִ�е���������ȡ����
	const TCHAR* pszDllName = pfnGetName();
	// ��DLL�����뵽�˵�.
	m_pluginMenu.AppendMenu(MF_STRING, m_nPluginID, pszDllName);
	//���뵽kvӳ����
	m_mapPluginDll.insert({ m_nPluginID, hDll });
	++m_nPluginID;
	goto __NORMAL_END;
__ERROR_END:
	if (NULL != hDll) FreeLibrary(hDll);

__NORMAL_END:
	;
}


// CMy010����Dllʵ�ֻ�ͼ��EXEDlg ��Ϣ�������

BOOL CMy010����Dllʵ�ֻ�ͼ��EXEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_mainMenu.CreateMenu(); // ��������˵�.
	m_pluginMenu.CreatePopupMenu(); // ���������˵�

	m_nPluginID = WM_USER + 100;
	//��ȡ���Ŀ¼
	TCHAR szPluginDir[MAX_PATH];
	GetExeRootPath(szPluginDir, _countof(szPluginDir));
	_stprintf_s(szPluginDir, _countof(szPluginDir) - _tcslen(szPluginDir), _T("%s%s"), szPluginDir, _T("plugin\\"));
	//
	FileOperation fOperation;
	FileNode *pRootNode = NULL;
	fOperation.EnumFile(szPluginDir, pRootNode, EnumPlugin, this, 0, _T("*.dll"));
	fOperation.DeleteFileNodeTree(pRootNode);
	//
	m_mainMenu.AppendMenu(MF_POPUP, (UINT_PTR)m_pluginMenu.m_hMenu, _T("���"));
	// ���öԻ���Ĳ˵���
	SetMenu(&m_mainMenu);
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy010����Dllʵ�ֻ�ͼ��EXEDlg::OnPaint()
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
		if (m_pShap) m_pShap->DrawOld(GetDC());
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy010����Dllʵ�ֻ�ͼ��EXEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CMy010����Dllʵ�ֻ�ͼ��EXEDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	WORD  wCtlID = LOWORD(wParam);
	auto ite = m_mapPluginDll.find(wCtlID);
	if (ite != m_mapPluginDll.end())
	{
		typedef  CShape* (*fpTypeGetInstance)();
		fpTypeGetInstance fpGetInstance = (fpTypeGetInstance)GetProcAddress(m_mapPluginDll[wCtlID], "GetInstance");
		m_pShap = fpGetInstance();
	}
	return CDialogEx::OnCommand(wParam, lParam);
}


void CMy010����Dllʵ�ֻ�ͼ��EXEDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_pShap) m_pShap->LButtonDown(point.x, point.y);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMy010����Dllʵ�ֻ�ͼ��EXEDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_pShap) m_pShap->LButtonUp(point.x, point.y);
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMy010����Dllʵ�ֻ�ͼ��EXEDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_pShap && nFlags & MK_LBUTTON)
	{
		m_pShap->MouseMove(this, GetDC(), point.x, point.y);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
