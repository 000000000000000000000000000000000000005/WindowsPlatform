#include "PEOperation.h"
#include <tchar.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	TCHAR szFilePath[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = _T("ִ���ļ�(*.exe)(*.dll)(*.sys)\0");
	ofn.lpstrInitialDir = _T("./");
	ofn.lpstrFile = szFilePath;
	ofn.nMaxFile = sizeof(szFilePath) / sizeof(*szFilePath);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
	if (!GetOpenFileName(&ofn))
	{
		return 1;
	}
	if (_tcscmp(szFilePath, _T("")) == 0)
	{
		return 1;
	}


	HANDLE hReadFile = CreateFile(szFilePath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hReadFile == INVALID_HANDLE_VALUE) {
		printf("�ļ�������\n");
		system("pause");
		return 1;
	}
	ULONG ulHigh = 0;
	ULONG ulFileSize = GetFileSize(hReadFile, &ulHigh);
	BYTE* pFileBuff = new BYTE[ulFileSize];
	ReadFile(hReadFile, pFileBuff, ulFileSize, &ulFileSize, NULL);

	if (!IsPEFile(pFileBuff))
	{
		printf("����һ��pe�ļ�");
		system("pause");
		return 1;
	}


	BYTE* pNewBuffOfAddress; //����½ں󻺳���
	int nNewFileSize;   //�����ӵĽڻ�������С
	IMAGE_SECTION_HEADER newSectionInfo = { 0 }; //�µķֽ���Ϣ
	ULONG ulRealWrite;
	//�ѵ�����ƶ����µķֽ�
	ZeroMemory(&newSectionInfo, sizeof(newSectionInfo));
	MoveImport(
		pFileBuff,
		ulFileSize,
		"myimp",
		IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE,
		&pNewBuffOfAddress,
		&nNewFileSize,
		&newSectionInfo
		);

	//���ӵ���dll
	AddImportDll(
		pNewBuffOfAddress,
		//"002pe�ṹ������ӵ�����Dll.dll",
		"AntiCheat.dll",
		1
		);

	TCHAR szMovImport[MAX_PATH] = { 0 };
	_stprintf_s(szMovImport, _countof(szMovImport), _T("%s�ƶ���������޸ĵ���dll.exe"), szFilePath);

	HANDLE hMoveImport = CreateFile(szMovImport,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	WriteFile(hMoveImport, pNewBuffOfAddress, nNewFileSize, &ulRealWrite, NULL);
	CloseHandle(hMoveImport);
	delete[]  pNewBuffOfAddress;
	pNewBuffOfAddress = NULL;


	//��β����
	delete[] pFileBuff;

	printf("�޸ĳɹ�����ȷ����002pe�ṹ������ӵ�����Dll.dll����exe��ͬһ��Ŀ¼\n");

	system("pause");

	return 0;
}
