#pragma once
#include <windows.h>


struct MyOVERLAPPED :public OVERLAPPED
{
public:
	char *pBuff; //���������׵�ַ
	int nIndex;  //���ڱ���IO��������

	MyOVERLAPPED();
	MyOVERLAPPED(int nIoSize, int nFileOffsetLow, int nFileOffsetHight = 0);
	~MyOVERLAPPED();
};