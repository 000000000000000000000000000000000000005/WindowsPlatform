
// 006�˵��������Dlg.h : ͷ�ļ�
//

#pragma once


// CMy006�˵��������Dlg �Ի���
class CMy006�˵��������Dlg : public CDialogEx
{
// ����
public:
	CMy006�˵��������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY006_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CMenu	  m_mainMenu;
	CMenu m_menuTest;
// ʵ��
protected:
	HICON m_hIcon;


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDoAction();
};
