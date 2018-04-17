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
						  return OnInitDialog(hwndDlg, uMsg, wParam, lParam);
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


	/***************���ؼ�*****************/
	HWND hTree = GetDlgItem(hwndDlg, IDC_TREE1);
	/*����ͼ������*/
	TreeView_SetImageList(hTree, g_hImageList, TVSIL_NORMAL);
	/*��ӽڵ���Ϣ*/
	// 1. 1���ڵ�1
	TVINSERTSTRUCT tvi = {};
	tvi.hParent = TVI_ROOT;// ���ĸ��ڵ��Ǹ��ڵ�
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.pszText = TEXT("��һ�׶�");
	tvi.item.iImage = 1;
	tvi.item.iSelectedImage = 3;
	tvi.item.mask = TVIF_TEXT | TVIF_IMAGE;
	HTREEITEM hRarent = TreeView_InsertItem(hTree, &tvi);
	// 2���ڵ�1
	TVINSERTSTRUCT tviChild = {};
	tviChild.hParent = hRarent;
	tviChild.hInsertAfter = TVI_LAST;
	tviChild.item.pszText = TEXT("c");
	tviChild.item.mask = TVIF_TEXT | TVIF_IMAGE;
	tviChild.item.iImage = 1;
	tviChild.item.iSelectedImage = 3;
	TreeView_InsertItem(hTree, &tviChild);
	// 2���ڵ�2
	tviChild.item.pszText = TEXT("c++");
	tviChild.item.iImage = 2;
	tviChild.item.iSelectedImage = 3;
	TreeView_InsertItem(hTree, &tviChild);
	// 1 ���ڵ�2
	tvi.item.pszText = TEXT("�ڶ��׶�");
	tvi.item.iImage = 1;
	tvi.item.iSelectedImage = 3;
	hRarent = TreeView_InsertItem(hTree, &tvi);
	// 2 ���ڵ�1
	tviChild.hParent = hRarent;
	tviChild.hInsertAfter = TVI_LAST;
	tviChild.item.pszText = TEXT("SDK");
	tviChild.item.mask = TVIF_TEXT | TVIF_IMAGE;
	tviChild.item.iImage = 1;
	tviChild.item.iSelectedImage = 3;
	TreeView_InsertItem(hTree, &tviChild);
	// 2���ڵ�2
	tviChild.item.pszText = TEXT("MFC");
	tviChild.item.iImage = 2;
	tviChild.item.iSelectedImage = 3;
	TreeView_InsertItem(hTree, &tviChild);

	return  1;
}


void InitImageList()
{
	// �ȴ�������
	g_hImageList = ImageList_Create(32, 32, ILC_COLOR32 | ILC_MASK, 4, 1);  //ILC_MASK������͸��ɫ
	//g_hImageList = ImageList_Create(32, 32, ILC_COLOR32, 4, 1);     //===> ��������͸��ɫ
	// ��ӳ�Ա
	HINSTANCE hInstance = GetModuleHandle(0);
	for (int i = 0; i < 4; ++i)
	{
		HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1 + i));
		ImageList_AddIcon(g_hImageList, hIcon);
	}
}