#pragma once


// DialogTab2 �Ի���

class DialogTab2 : public CDialog
{
	DECLARE_DYNAMIC(DialogTab2)

public:
	DialogTab2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogTab2();

// �Ի�������
	enum { IDD = IDD_DIALOGTAB2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
