
// 002�����󶨺ͷ���Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMy002�����󶨺ͷ���Dlg �Ի���
class CMy002�����󶨺ͷ���Dlg : public CDialogEx
{
// ����
public:
	CMy002�����󶨺ͷ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY002_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// //IDC_EDIT1�ؼ����͵ı���	// //IDC_EDIT1�ؼ����͵ı���
	CEdit m_edit;
	CString m_strEdit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
