
// 013���δ���Dlg.h : ͷ�ļ�
//

#pragma once


// CMy013���δ���Dlg �Ի���
class CMy013���δ���Dlg : public CDialogEx
{
// ����
public:
	CMy013���δ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY013_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CImage m_bgimg;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
