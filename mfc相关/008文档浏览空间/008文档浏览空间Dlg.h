
// 008�ĵ�����ռ�Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxshelltreectrl.h"
#include "afxshelllistctrl.h"


// CMy008�ĵ�����ռ�Dlg �Ի���
class CMy008�ĵ�����ռ�Dlg : public CDialogEx
{
// ����
public:
	CMy008�ĵ�����ռ�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY008_DIALOG };

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
	CMFCShellTreeCtrl m_shellTreeCtl;
	CMFCShellListCtrl m_ListCtl;
};
