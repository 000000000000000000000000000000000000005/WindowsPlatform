#include "FileOperation.h"

int main(int argc, char* argv[])
{
	//1. ��ȡ����������
	std::vector<DriverData> vecDriver;
	FileOperation fOperation;
	fOperation.GetDriverInfo(vecDriver);

	//2. �����ļ�
	FileNode *pRoot = NULL;
	fOperation.EnumFile(vecDriver[0].szDriverName, pRoot, NULL, NULL, 0);

	//3.�ͷű�����Դ
	fOperation.DeleteFileNodeTree(pRoot);
}