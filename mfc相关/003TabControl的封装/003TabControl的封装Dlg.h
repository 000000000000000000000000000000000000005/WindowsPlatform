
// 003TabControl�ķ�װDlg.h : ͷ�ļ�
//

#pragma once
#include "MyTabCtl.h"


// CMy003TabControl�ķ�װDlg �Ի���
class CMy003TabControl�ķ�װDlg : public CDialogEx
{
// ����
public:
	CMy003TabControl�ķ�װDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY003TABCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MyTabCtl m_tabCtl;
};
