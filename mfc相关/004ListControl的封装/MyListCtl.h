#pragma once
#include <vector>


// MyListCtl

class MyListCtl : public CListCtrl
{
	DECLARE_DYNAMIC(MyListCtl)

public:
	MyListCtl();
	virtual ~MyListCtl();
	//����������
	void SetGridStyle();
	//��ȡ������
	int GetColNum();
	//��ȡ������
	int GetRowNum();

	//��ȡ��ǰѡ����
	void GetSelectedRow(std::vector<int> &vecSelectRow);

	//��ȡnItem�к�nColumnNum�е��ı�
	CString GetSpecItemText(int nRow, int nColNum);
	//����nItem��nSubItem�е��ı�
	void SetItemText(int nRow, int nCol, CString strText, int nImage = -1);

	//����nItem�е�nColNum��Ԫ��,���������ͼƬnImage ����Ϊ-1
	void SetItemText(int nRow, int nImage, int nColNum, ...);
	//������
	void InsertColumn(int nCol, LPCTSTR lpszColName, int nWidth);


private:
	int m_nColumnNum;

protected:
	DECLARE_MESSAGE_MAP()
};


