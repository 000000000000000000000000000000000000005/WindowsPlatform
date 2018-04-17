#include "FileOperation.h"
#include "Dbg.h"
#include <queue>
#pragma comment(lib,"shlwapi.lib")  
#include <shlwapi.h>  


//��ȡ�������ļ����Ϣ
void FileOperation::GetDriverInfo(std::vector<DriverData> OUT &vecDriver)
{
	TCHAR szAllDrive[MAX_FIND_PATH] = { 0 };
	GetLogicalDriveStrings(MAX_FIND_PATH, szAllDrive);
	for (int i = 0; szAllDrive[i] != _T('\0') && i < MAX_FIND_PATH; i++)
	{
		//��ȡ�̷�����
		UINT uDriveType = GetDriveType(&szAllDrive[i]);
		if (!(DRIVE_NO_ROOT_DIR == uDriveType ||
			DRIVE_NO_ROOT_DIR == uDriveType ||
			DRIVE_REMOVABLE == uDriveType)
			)
		{
			DWORD dwSectorsPerCluster;      //ÿ��������
			DWORD dwBytesPerSector;           //ÿ�����������ֽ�
			DWORD dwNumberOfFreeClusters;  //���ٿ��еĴ�
			DWORD dwTotalNumberOfClusters;  //һ���ж��ٴ�
			float fFreeMb;  //�ܹ�����MB
			float fTotalMb; //�ܹ�����MB
			//��ȡ��С��Ϣ
			GetDiskFreeSpace(&szAllDrive[i], &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);
			//
			fFreeMb = (float)dwSectorsPerCluster * dwBytesPerSector * dwNumberOfFreeClusters / 1024 / 1024;
			fTotalMb = (float)dwSectorsPerCluster * dwBytesPerSector * dwTotalNumberOfClusters / 1024 / 1024;
			//���ṹ����Ϣ
			DriverData driverData;
			_tcscpy_s(driverData.szDriverName, _countof(driverData.szDriverName), &szAllDrive[i]);
			driverData.uDriverType = uDriveType;
			driverData.dwSectorsPerCluster = dwSectorsPerCluster;
			driverData.dwBytesPerSector = dwBytesPerSector;
			driverData.dwNumberOfFreeClusters = dwNumberOfFreeClusters;
			driverData.dwTotalNumberOfClusters = dwTotalNumberOfClusters;
			driverData.fFreeMb = fFreeMb;
			driverData.fTotalMb = fTotalMb;

			PrintDbgInfo(_T("��������%s, �ܹ���%lfMb, ʣ��:%lfMb"), &szAllDrive[i], fTotalMb, fFreeMb);
			//�浽������
			vecDriver.push_back(driverData);
		}
		i += _tcslen(&szAllDrive[i]);
	}
}

BOOL FileOperation::IsCdRoomHasMedia(IN LPCTSTR lpCdDriver)
{
	UINT uDriveType = GetDriveType(lpCdDriver);
	if (DRIVE_CDROM != uDriveType) return FALSE;
	if (21 == GetLastError()) return FALSE;
	return TRUE;
}

BOOL FileOperation::GetFileInfo(IN LPCTSTR lpPath, OUT BOOL &bIsDir, SYSTEMTIME &fileSt)
{
	TCHAR szFindPath[MAX_FIND_PATH] = { 0 };
	if (PathIsDirectory(lpPath))
	{
		_stprintf_s(szFindPath, MAX_FIND_PATH, TEXT("%s\\%s"), lpPath, _T("*"));
	}
	else
	{
		_tcscpy_s(szFindPath, _countof(szFindPath), lpPath);
	}
	//
	WIN32_FIND_DATA wfd;
	HANDLE hCheck = FindFirstFile(szFindPath, &wfd);
	if (INVALID_HANDLE_VALUE == hCheck) return FALSE;
	FindClose(hCheck);
	//��ȡϵͳʱ��
	FILETIME ft = {};
	FileTimeToLocalFileTime(&wfd.ftCreationTime, &ft);
	// ���ļ�ʱ��ת��ϵͳʱ��
	FileTimeToSystemTime(&ft, &fileSt);
	//��ȡ�Ƿ���Ŀ¼
	bIsDir = wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? TRUE:FALSE;
	return TRUE;
}

BOOL FileOperation::GetFileSize(IN LPCTSTR lpPath, OUT DWORD &dwSizeLow, OUT DWORD &dwSizeHigh)
{
	//1.�ж��Ƿ���һ����ͨ�ļ�
	OUT BOOL bIsDir;
	SYSTEMTIME fileSt;
	//��������ļ�
	if (!GetFileInfo(lpPath, bIsDir, fileSt)) return FALSE;
	//�����Ŀ¼
	if (bIsDir) return FALSE;
	
	//2.��ȡ�ļ���С
	HANDLE hFile = ::CreateFile(
		lpPath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	dwSizeHigh = 0;
	dwSizeLow = ::GetFileSize(hFile, &dwSizeHigh);
	return TRUE;
}

BOOL FileOperation::EnumFile(
	IN LPCTSTR lpRoot,
	OUT FileNode* &pRootNode,
	IN EnumFileCallBack fpCallBack,
	IN void* callBackParameter,
	IN int nMaxLevel,
	IN LPCTSTR lpExtenName)
{
	//1. �жϸ��ڵ��Ƿ����
	BOOL bRootIsDir = FALSE;
	SYSTEMTIME rootSt = { 0 };
	if (!GetFileInfo(lpRoot, bRootIsDir, rootSt)) return FALSE;

	//2. �����ڵ�
	pRootNode = new FileNode;
	pRootNode->bIsDir = bRootIsDir;
	_tcscpy_s(pRootNode->szFileName, _countof(pRootNode->szFileName), lpRoot);
	pRootNode->sysTime = rootSt;
	pRootNode->pParentFile = NULL;
	pRootNode->nLevel = 0;

	//3. �����Ƿ��Ƿ�Ŀ¼������Ҫ��������
	if (!pRootNode->bIsDir) return TRUE;

	//4.��ʼ������
	int nLevelCount = 0;  //��μ��
	std::queue<FileNode*> enumQue;
	enumQue.push(pRootNode);
	while (!enumQue.empty())
	{
		//��ȡ��Ҫ������Ŀ¼
		FileNode *pCurrentNode = enumQue.front();
		enumQue.pop();

		//��������ַ���
		TCHAR szFindPath[MAX_FIND_PATH] = { 0 };
		_stprintf_s(szFindPath, _countof(szFindPath), TEXT("%s\\%s"), pCurrentNode->szFileName, lpExtenName);

		//ִ�в���
		WIN32_FIND_DATA wfd = { 0 };
		HANDLE hFind = FindFirstFile(szFindPath, &wfd);
		if (INVALID_HANDLE_VALUE == hFind) continue;
		//
		do
		{
			//��ȡȫ·����
			TCHAR szFullPath[MAX_FIND_PATH] = { 0 };
			_stprintf_s(szFullPath, _countof(szFullPath), TEXT("%s\\%s"), pCurrentNode->szFileName, wfd.cFileName);
			PrintDbgInfo(_T("��ǰ�ļ�:%s"), szFullPath);
			// ת���ɱ���ʱ��
			FILETIME ft = {};
			FileTimeToLocalFileTime(&wfd.ftCreationTime, &ft);
			// ���ļ�ʱ��ת��ϵͳʱ��
			SYSTEMTIME st = {};
			FileTimeToSystemTime(&ft, &st);

			// ����ǵ�ǰĿ¼���ϼ�Ŀ¼  ��  . .. ������
			if (!_tcscmp(wfd.cFileName, TEXT(".")) || !_tcscmp(wfd.cFileName, TEXT(".."))) continue;

			//���ڵ�
			FileNode *pNode = new FileNode;
			pNode->bIsDir =wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? TRUE : FALSE;
			_tcscpy_s(pNode->szFileName, _countof(pNode->szFileName), szFullPath);
			pNode->sysTime = st;
			pNode->pParentFile = pCurrentNode;
			pRootNode->nLevel;

			//���뵽��ǰĿ¼�����ļ���
			pCurrentNode->vecSubFile.push_back(pNode);

			//ִ�лص�����
			if (NULL != fpCallBack)
			{
				//����ص���������false����������true��������
				if (fpCallBack(callBackParameter, pNode)) break;
			}

			// �ж��Ƿ���Ŀ¼
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				enumQue.push(pNode);
			}

		} while (FindNextFile(hFind, &wfd));
		FindClose(hFind);
		//
		++nLevelCount;
		//��������涨�Ĳ�Σ�ֱ��������0����ֱ���������
		if (nLevelCount >= nMaxLevel && nMaxLevel != 0) break;

	}
	return TRUE;
}

void FileOperation::DeleteFileNodeTree(OUT FileNode* &pRootNode)
{
	std::queue<FileNode*> enumQue;
	enumQue.push(pRootNode);

	//��ʼ�ͷ��ڴ�
	while (!enumQue.empty())
	{
		FileNode* pCurrentNode = enumQue.front();
		enumQue.pop();
		//
		for (size_t i = 0; i < pCurrentNode->vecSubFile.size(); i++)
		{
			FileNode* pSubNode = (pCurrentNode->vecSubFile)[i];
			enumQue.push(pSubNode);
		}
		delete pCurrentNode;
	}
	//
	pRootNode = NULL;

}

BOOL FileOperation::CopyFile(IN LPCTSTR lpExistingFileName, IN LPCTSTR lpNewFileName, IN BOOL bFailIfExists)
{
	return ::CopyFile(lpExistingFileName, lpNewFileName, bFailIfExists);
}

BOOL FileOperation::MoveFile(IN LPCTSTR lpExistingFileName, IN LPCTSTR lpNewFileName)
{
	return ::MoveFile(lpExistingFileName, lpNewFileName);
}

BOOL FileOperation::DeleteFile(IN LPCTSTR lpFileName)
{
	return ::DeleteFile(lpFileName);
}
