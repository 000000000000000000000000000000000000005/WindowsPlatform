#pragma once


// DialogTab1 �Ի���

class DialogTab1 : public CDialog
{
	DECLARE_DYNAMIC(DialogTab1)

public:
	DialogTab1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogTab1();

// �Ի�������
	enum { IDD = IDD_DIALOGTAB1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
