// MyButtonWM_PAINT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "009�ؼ��Ի�.h"
#include "MyButtonWM_PAINT.h"


// MyButtonWM_PAINT

IMPLEMENT_DYNAMIC(MyButtonWM_PAINT, CButton)

MyButtonWM_PAINT::MyButtonWM_PAINT()
{
	m_isLeftButton = FALSE;
	m_isHover = FALSE;
}

MyButtonWM_PAINT::~MyButtonWM_PAINT()
{
}


BEGIN_MESSAGE_MAP(MyButtonWM_PAINT, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// MyButtonWM_PAINT ��Ϣ�������




void MyButtonWM_PAINT::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isLeftButton = TRUE;
	InvalidateRect(NULL, TRUE);
	CButton::OnLButtonDown(nFlags, point);
}


void MyButtonWM_PAINT::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isLeftButton = FALSE;
	InvalidateRect(NULL, TRUE);

	CButton::OnLButtonUp(nFlags, point);
}


void MyButtonWM_PAINT::OnMouseMove(UINT nFlags, CPoint point)
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
void MyButtonWM_PAINT::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isHover = TRUE;
	CButton::OnMouseHover(nFlags, point);
	InvalidateRect(NULL, 0);
	CButton::OnMouseHover(nFlags, point);
}


void MyButtonWM_PAINT::OnMouseLeave()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isHover = FALSE;
	InvalidateRect(0, 0);

	CButton::OnMouseLeave();
}


void MyButtonWM_PAINT::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
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

	// ��Ϊ��ͼ��Ϣ���� CButton::OnPaint()
}
