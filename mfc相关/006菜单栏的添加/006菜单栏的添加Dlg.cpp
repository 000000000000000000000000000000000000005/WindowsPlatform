
// 006�˵��������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "006�˵��������.h"
#include "006�˵��������Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy006�˵��������Dlg �Ի���



CMy006�˵��������Dlg::CMy006�˵��������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy006�˵��������Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy006�˵��������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy006�˵��������Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CMy006�˵��������Dlg::OnDoAction)
END_MESSAGE_MAP()


BOOL CMy006�˵��������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	////////////////////////////////////////////////////////////////////////
	/////////////////��Ҫ�˵��Ľṹʽʮ������////////////////////////////
	////////////////////////////////////////////////////////////////////////

	//1.1 ���˵�ֱ�Ӽ�����Դ(�и�ȱ����봴��һ���Ӳ˵�)
 	m_mainMenu.LoadMenu(MAKEINTRESOURCE(IDR_MENU1));  // => ֱ�Ӽ�����Դ

	//1.2 ���˵���̬����(�Ƚ����)=>�����Ҫ��������˵��������н⿪ע��
	//m_mainMenu.CreateMenu(); // ��������˵�.
	m_menuTest.CreatePopupMenu(); // ���������˵�
	m_mainMenu.AppendMenu(MF_POPUP, (UINT_PTR)m_menuTest.m_hMenu, _T("��̬��������"));


	//2. ��̬�����˵����Ӳ˵�
	CMenu animalMenu;              //����˵������  
	animalMenu.CreatePopupMenu();  //���������˵�����  
	//m_mainMenu.AppendMenuW(MF_POPUP, (UINT)m_PopupMenu.m_hMenu, _T("����"));  => //����˵���m_mainMenuͬ��
	m_mainMenu.GetSubMenu(1)->AppendMenu(MF_POPUP, (UINT)animalMenu.m_hMenu, _T("����")); //����˵���m_mainMenu�Ӳ˵�

	animalMenu.AppendMenu(MF_POPUP, 10001, _T("è"));            //�����Ӳ˵�  
	animalMenu.AppendMenu(MF_POPUP, 10002, _T("��"));            //�����Ӳ˵�  
	animalMenu.AppendMenu(MF_POPUP, 10003, _T("��"));         //�����Ӳ˵�  
	animalMenu.AppendMenu(MF_POPUP, -1, _T("ֲ��"));                  //�����ֵܲ˵�  
	animalMenu.Detach();                                               //����˵����  
	SetMenu(&m_mainMenu);                                                   //���˵��ʹ��ڽ��й�







	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy006�˵��������Dlg::OnPaint()
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
HCURSOR CMy006�˵��������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy006�˵��������Dlg::OnDoAction()
{
	// TODO:  �ڴ���������������
	MessageBox(_T("�ܵ�����¼�"), _T("��ʾ"), MB_OK);
}
