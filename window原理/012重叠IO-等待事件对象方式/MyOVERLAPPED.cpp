#include "MyOVERLAPPED.h"


// Ĭ�Ϲ��캯��
MyOVERLAPPED::MyOVERLAPPED()
:pBuff(NULL)
{
	OVERLAPPED::hEvent = 0;
}

//
MyOVERLAPPED::MyOVERLAPPED(int nIoSize, int nFileOffsetLow, int nFileOffsetHight /*= 0 */)
{
	// �����¼�����
	OVERLAPPED::hEvent = CreateEvent(NULL, FALSE, FALSE, NULL); // ����һ���¼�����

	// �����ļ���дƫ��
	OVERLAPPED::Offset = nFileOffsetLow;
	OVERLAPPED::OffsetHigh = nFileOffsetHight;

	// ���뻺���������ļ�����
	pBuff = new char[nIoSize];
}


// ��������,�ͷſռ�,�ͷ��¼�����
MyOVERLAPPED::~MyOVERLAPPED()
{
	// �ͷſռ�
	if (pBuff != NULL) {
		delete[] pBuff;
		pBuff = NULL;
	}

	// �ر��¼�����
	if (hEvent != NULL) {
		CloseHandle(hEvent);
	}
}