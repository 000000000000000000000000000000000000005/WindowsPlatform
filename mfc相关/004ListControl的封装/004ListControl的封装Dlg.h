
// 004ListControl�ķ�װDlg.h : ͷ�ļ�
//

#pragma once
#include "MyListCtl.h"


// CMy004ListControl�ķ�װDlg �Ի���
class CMy004ListControl�ķ�װDlg : public CDialogEx
{
// ����
public:
	CMy004ListControl�ķ�װDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY004LISTCONTROL_DIALOG };

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
	MyListCtl m_listCtl;
	CImageList  m_imageList;
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
