#include <windows.h>
#include <tchar.h>
#include <Windowsx.h>
#include "resource.h"
#include "Dbg.h"
#include <CommCtrl.h>

#pragma comment(lib,"Comctl32.lib ")

INT_PTR CALLBACK DialogProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	);

void InitImageList();
int  OnInitDialog(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	);


HINSTANCE g_hInstance = NULL;
HIMAGELIST g_hImageList = NULL;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	g_hInstance = hInstance;
	HWND hDlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc, NULL);
	ShowWindow(hDlg, SW_SHOW);

	HACCEL hAccTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	MSG msg = { 0 };
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (!TranslateAccelerator(hDlg, hAccTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

INT_PTR CALLBACK DialogProc(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
						  InitCommonControls();
						  InitImageList();
						  OnInitDialog(hwndDlg, uMsg, wParam, lParam);
						  return 1;
	}
		break;
	case WM_COMMAND:
	{
					   WORD wHigh = HIWORD(wParam);
					   WORD wLow = LOWORD(wParam);
					   return 1;
	}
		break;
	case WM_CLOSE:
	{
					 PrintDbgInfo(_T("WM_CLOSE ��Ϣ������"));
					 PostQuitMessage(0);
					 return 1;
	}
		break;
	case WM_NOTIFY:// ���ӿؼ���֪ͨ��Ϣ
	{
					   NMHDR* pNmhdr = (NMHDR*)lParam;
					   /*List�ؼ������Ϣ*/
					   if (pNmhdr->idFrom == IDC_LIST1 &&
						   pNmhdr->code == NM_CLICK)
					   {
						   LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;
						   TCHAR szList[MAX_PATH] = {};
						   ListView_GetItemText(
							   pNmhdr->hwndFrom,// LIST �ؼ����
							   lpnmitem->iItem, // �к�
							   lpnmitem->iSubItem,//�б�
							   szList, // ��ȡ�����ı�����λ��
							   _countof(szList));
						   MessageBox(hwndDlg, szList, 0, MB_OK);
					   }
	}
	default:
		break;
	}
	return 0;
}

int  OnInitDialog(
	_In_  HWND hwndDlg,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	/*List�ĳ�ʼ��ͨ�����Դ��ڻ����*/
	HWND hListCtrl = GetDlgItem(hwndDlg, IDC_LIST1);
	/*���ÿؼ������ʽ->���пؼ�*/
	// ԭ���ķ��
	LRESULT lStyle = ListView_GetExtendedListViewStyle(hListCtrl);
	// ����µ���չ��� ����ѡ�� ������
	ListView_SetExtendedListViewStyle(hListCtrl, lStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	/*���б�����ͼ������*/
	ListView_SetImageList(hListCtrl, g_hImageList, LVSIL_SMALL);
	/*���������Ϣ*/
	/*
	insertcolumn ������
	insertitem ����X�е�1��
	setitem ����X��Y�е���Ϣ
	*/
	DWORD dwWidth[] = { 80, 120, 200 };
	TCHAR *szCol[] = { TEXT("����"), TEXT("�׶�"), TEXT("״̬") };
	for (int i = 0; i < 3; ++i)
	{
		LVCOLUMN lvc = {};
		lvc.cx = dwWidth[i];// �п�
		lvc.pszText = szCol[i];
		lvc.mask = LVCF_TEXT | LVCF_WIDTH;
		ListView_InsertColumn(
			hListCtrl,
			i,// �к�
			&lvc);
	}
	/*�������Ϣ*/
	for (size_t i = 0; i < 20; i++)
	{
		LVITEM lvi = {};
		lvi.pszText = TEXT("��Ǯ����");
		lvi.iItem = i;// �ڼ���
		/*���ͼ��*/
		lvi.iImage = i % 4;// �����ͼ����ͼ�������е�����������Խ��
		lvi.mask = LVIF_TEXT | LVIF_IMAGE;
		ListView_InsertItem(hListCtrl, &lvi);
		//lvi.iItem = i;// �ڼ���
		lvi.iSubItem = 1;// �ڼ���
		lvi.pszText = TEXT("�ڶ��׶�");
		ListView_SetItem(hListCtrl, &lvi);
		// ���ֻ�ǵ����������ı�
		ListView_SetItemText(hListCtrl, i, 2, TEXT("����"));
	}

	return 0;
}


void InitImageList()
{
	// �ȴ�������
	g_hImageList = ImageList_Create(32, 32, ILC_COLOR32 | ILC_MASK, 4, 1);
	// ��ӳ�Ա
	HINSTANCE hInstance = GetModuleHandle(0);
	for (int i = 0; i < 4; ++i)
	{
		HICON hIcon1 = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1 + i));
		ImageList_AddIcon(g_hImageList, hIcon1);
	}
}
