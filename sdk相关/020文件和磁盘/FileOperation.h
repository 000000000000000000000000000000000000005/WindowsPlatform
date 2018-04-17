#pragma once
#include <windows.h>
#include <tchar.h>
#include <vector>

//·���Ϊ
#define  MAX_FIND_PATH 1024

typedef struct
{
	UINT uDriverType;
	TCHAR szDriverName[MAX_FIND_PATH];
	DWORD dwSectorsPerCluster;      //ÿ��������
	DWORD dwBytesPerSector;           //ÿ�����������ֽ�
	DWORD dwNumberOfFreeClusters;  //���ٿ��еĴ�
	DWORD dwTotalNumberOfClusters;  //һ���ж��ٴ�
	float fFreeMb;  //�ж��ٿ���(MB)
	float fTotalMb; //�ܹ�������(MB)
}DriverData;

typedef struct __FileNode
{
	TCHAR szFileName[MAX_FIND_PATH];
	BOOL bIsDir;  //�Ƿ���Ŀ¼
	SYSTEMTIME sysTime;  //�ļ�����ʱ��
	__FileNode* pParentFile; //���ڵ���˭
	int nLevel; //��ǰ�����Ĳ��
	std::vector<__FileNode*> vecSubFile; //�����ǰ�ļ�ΪĿ¼��Ŀ¼�����ļ�
}FileNode;


//�����ļ��Ļص�����,���bool��������false����������true��������
typedef BOOL (EnumFileCallBack)(void *Parameter, FileNode *pNode);

class FileOperation
{
public:
	//��ȡ��������Ϣ
	void GetDriverInfo(OUT std::vector<DriverData> &vecDriver);

	//�жϹ����Ƿ��й���
	BOOL IsCdRoomHasMedia(IN LPCTSTR lpCdDriver);

	//��ȡ�ļ���Ϣ,�������false������һ���ļ�
	BOOL GetFileInfo(IN LPCTSTR lpPath, OUT BOOL &bIsDir, SYSTEMTIME &fileSt);

	//��ȡ�ļ���С,�������false������һ���ļ�������һ��Ŀ¼
	//dwSizeLow:  �ļ���С�ĵ�4���ֽ�
	//dwSizeHigh�� �ļ���С�ĸ��ĸ��ֽ�
	BOOL GetFileSize(IN LPCTSTR lpPath, OUT DWORD &dwSizeLow, OUT DWORD &dwSizeHigh);

	//�����ļ��Ĳ���˵����
	//lpRoot:�����ĸ��ڵ�
	//pRootNode:������洢������
	//fpCallBack�����ļ��Ļص����������bool��������false����������true��������������Ϊ��
	//callBackParameter�ص������Ĳ���
	//nMaxLevel:�����ٲ�
	//lpExtenName�������ļ�ƥ�����չ��
	BOOL EnumFile(
		IN LPCTSTR lpRoot,
		OUT FileNode* &pRootNode,
		IN EnumFileCallBack fpCallBack,
		IN void* callBackParameter,
		IN int nMaxLevel,
		IN LPCTSTR lpExtenName = _T("*"));

	//������Ϊ����new�������ļ���
	void DeleteFileNodeTree(IN FileNode* &pRootNode);

	//�ļ�����
	BOOL CopyFile(
		IN  LPCTSTR lpExistingFileName,
		IN  LPCTSTR lpNewFileName,
		IN  BOOL bFailIfExists);

	//�ļ��ƶ�
	BOOL MoveFile(
		IN LPCTSTR lpExistingFileName,
		IN LPCTSTR lpNewFileName
		);

	//ɾ���ļ�
	BOOL DeleteFile(IN LPCTSTR lpFileName);

};

