
// 011���̳���Dlg.h : ͷ�ļ�
//

#pragma once


// CMy011���̳���Dlg �Ի���
class CMy011���̳���Dlg : public CDialogEx
{
// ����
public:
	CMy011���̳���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY011_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_nid;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
protected:
	afx_msg LRESULT On����֪ͨ(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void On32771();
};
