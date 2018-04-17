// MyTabCtl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "003TabControl�ķ�װ.h"
#include "MyTabCtl.h"


// MyTabCtl

IMPLEMENT_DYNAMIC(MyTabCtl, CTabCtrl)

MyTabCtl::MyTabCtl()
{

}

MyTabCtl::~MyTabCtl()
{
}

void MyTabCtl::AddTab(const CString& tabName, CWnd* pWnd) {
	pWnd->SetParent(this);
	CTabCtrl::InsertItem(m_vecWnd.size(), tabName);
	m_vecWnd.push_back(pWnd);
}

void MyTabCtl::SetCurSel(int nIndex) {
	for (size_t i = 0; i < m_vecWnd.size(); ++i)
	{
		m_vecWnd[i]->ShowWindow(SW_HIDE);
	}
	m_vecWnd[nIndex]->ShowWindow(SW_SHOW);
	CRect rt;
	// ��ȡѡ��Ĵ�С
	GetClientRect(rt);
	rt.top += 20;
	rt.left += 1;
	rt.right -= 1;
	rt.bottom -= 1;
	// ���Ӵ��ڵĴ�С����Ϊ��ѡ��ؼ�һ����.
	m_vecWnd[nIndex]->MoveWindow(rt);
}


BEGIN_MESSAGE_MAP(MyTabCtl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &MyTabCtl::OnTcnSelchange)
END_MESSAGE_MAP()



// MyTabCtl ��Ϣ�������




void MyTabCtl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	
	int nIndex = CTabCtrl::GetCurSel();
	SetCurSel(nIndex);
}
