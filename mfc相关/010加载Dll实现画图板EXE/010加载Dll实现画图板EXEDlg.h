
// 010����Dllʵ�ֻ�ͼ��EXEDlg.h : ͷ�ļ�
//

#pragma once

#include "FileOperation.h"
#include "DllInterface.h"
#include <map>


// CMy010����Dllʵ�ֻ�ͼ��EXEDlg �Ի���
class CMy010����Dllʵ�ֻ�ͼ��EXEDlg : public CDialogEx
{
// ����
public:
	CMy010����Dllʵ�ֻ�ͼ��EXEDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void DoPluginFile(FileNode *pNode);

// �Ի�������
	enum { IDD = IDD_MY010DLLEXE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	// ʵ��
protected:
	HICON m_hIcon;
	CMenu m_mainMenu;
	CMenu m_pluginMenu;
	int m_nPluginID;
	CShape *m_pShap;
	std::map<int, HMODULE> m_mapPluginDll;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
