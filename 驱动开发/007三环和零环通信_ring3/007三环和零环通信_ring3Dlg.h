
// 007�������㻷ͨ��_ring3Dlg.h : ͷ�ļ�
//

#pragma once


// CMy007�������㻷ͨ��_ring3Dlg �Ի���
class CMy007�������㻷ͨ��_ring3Dlg : public CDialogEx
{
// ����
public:
	CMy007�������㻷ͨ��_ring3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY007_RING3_DIALOG };

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
	afx_msg void OnBnClickedButton1();

private:
	HANDLE m_hDevice;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CString m_strThreadID;
};
