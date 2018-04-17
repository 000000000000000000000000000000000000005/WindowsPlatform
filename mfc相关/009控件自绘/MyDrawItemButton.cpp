// MyDrawItemButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "009�ؼ��Ի�.h"
#include "MyDrawItemButton.h"


// CMyDrawItemButton

IMPLEMENT_DYNAMIC(CMyDrawItemButton, CButton)

CMyDrawItemButton::CMyDrawItemButton()
{
	m_isLeftButton = FALSE;
	m_isHover = FALSE;
}

CMyDrawItemButton::~CMyDrawItemButton()
{
}


BEGIN_MESSAGE_MAP(CMyDrawItemButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_DRAWITEM()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CMyDrawItemButton ��Ϣ�������





void CMyDrawItemButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isLeftButton = TRUE;
	InvalidateRect(NULL, TRUE);
	CButton::OnLButtonDown(nFlags, point);
}


void CMyDrawItemButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isLeftButton = FALSE;
	InvalidateRect(NULL, TRUE);

	CButton::OnLButtonUp(nFlags, point);
}



void CMyDrawItemButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.dwHoverTime = 100;
	tme.hwndTrack = m_hWnd;
	TrackMouseEvent(&tme);   //ֻ�������ſ��Է�����ͣ���뿪��Ϣ

	CButton::OnMouseMove(nFlags, point);
}


//�����ͣ
void CMyDrawItemButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isHover = TRUE;
	CButton::OnMouseHover(nFlags, point);
	InvalidateRect(NULL, 0);
	CButton::OnMouseHover(nFlags, point);
}


void CMyDrawItemButton::OnMouseLeave()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isHover = FALSE;
	InvalidateRect(0, 0);

	CButton::OnMouseLeave();
}




void CMyDrawItemButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/) {

	CClientDC dc(this);
	// �ж���û����ͣ
	if (m_isHover == TRUE) {

		// �ж���û�а������
		if (m_isLeftButton == TRUE) {
			// ������갴��ʱ��ť����ʽ
			dc.TextOutW(0, 0, L"��갴��");
		}
		else {
			// ���û����,����ͣ��, ������ͣ����ʽ
			dc.TextOutW(0, 0, L"�����ͣ");
		}
	}
	else {
		// ���û����, Ҳû��ͣ,��������뿪����ʽ
		dc.TextOutW(0, 0, L"����뿪");
	}
}



