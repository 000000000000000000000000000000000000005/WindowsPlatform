
// 009�ؼ��Ի�Dlg.h : ͷ�ļ�
//

#pragma once
#include "MyButtonWM_PAINT.h"
#include "MyDrawItemButton.h"


// CMy009�ؼ��Ի�Dlg �Ի���
class CMy009�ؼ��Ի�Dlg : public CDialogEx
{
// ����
public:
	CMy009�ؼ��Ի�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY009_DIALOG };

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
	MyButtonWM_PAINT m_WM_PAINT_Button;
	CMyDrawItemButton m_drawItemButton;
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
