
// 005TreeControl�ķ�װDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMy005TreeControl�ķ�װDlg �Ի���
class CMy005TreeControl�ķ�װDlg : public CDialogEx
{
// ����
public:
	CMy005TreeControl�ķ�װDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY005TREECONTROL_DIALOG };

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
	CTreeCtrl m_treeCtl;
	CImageList m_imgList;
};
