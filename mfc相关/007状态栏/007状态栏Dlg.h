
// 007״̬��Dlg.h : ͷ�ļ�
//

#pragma once


// CMy007״̬��Dlg �Ի���
class CMy007״̬��Dlg : public CDialogEx
{
// ����
public:
	CMy007״̬��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY007_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CStatusBar	m_statusBar;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
