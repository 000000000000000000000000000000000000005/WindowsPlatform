#include <windows.h>
#include <tchar.h>

int main(int argc, char* argv[])
{

	BYTE *pNewBuff = new BYTE[4];
	//���һ:new�����ڴ���debug��release�¹���
	/*
		pNewBuff ��debug��:fd fd fd fd��ʼ��fd fd fd fd����
		δ��ʼ��:fd fd fd fd
		0x0045755C  fd fd fd fd  ????
		0x00457560  cd cd cd cd  ????
		0x00457564  fd fd fd fd  ????

		pNewBuff ��release��:û���κι���
		0x004D7BAC  2f 77 00 1c  /w..
		0x004D7BB0  0d f0 ad ba  .???
		0x004D7BB4  ab ab ab ab  ????
	*/

	//�����:delete new�������ڴ���debug��release�µĹ���
	delete [] pNewBuff;
	/*
		pNewBuff��debug�Ĺ���
		0x0044755C  ee fe ee fe  ????
		0x00447560  ee fe ee fe  ????
		0x00447564  ee fe ee fe  ????

		pNew��release��,��ǰ��ַ����ee fe ee fe,����������ee fe ee fe
		0x007C7BB0  f0 8f 7c 00  ??|.
		0x007C7BB4  c4 00 7c 00  ?.|.
		0x007C7BB8  ee fe ee fe  ????
		0x007C7BBC  ee fe ee fe  ????
		0x007C7BC0  ee fe ee fe  ????
	*/

	//�����:�ֲ�����
	BYTE byArry[100];
	/*
		byArry ��debug��release��:
		0x0040FB8C  cc cc cc cc  ????
		0x0040FB90  cc cc cc cc  ????
		0x0040FB94  cc cc cc cc  ????
		0x0040FB98  cc cc cc cc  ????
		0x0040FB9C  cc cc cc cc  ????
	*/

	//�����:VirtualAlloc�����ַ
	LPVOID lpVirtualAlloc = VirtualAlloc(NULL, 1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	/*
		1. lpVirtualAlloc ����������ڴ���64k����
		2. Ŀǰ��debug��release�¶�Ϊ0
	*/

	for (int i = 0; i < 1000; i++)
	{
		((BYTE*)lpVirtualAlloc)[i] = 0xFF;
	}

	VirtualFree(lpVirtualAlloc, 1000, MEM_RELEASE | MEM_DECOMMIT);

	//�����:HeapAlloc
	HANDLE	hHeap = NULL;
	hHeap = HeapCreate(0, 0, 0);

	LPVOID lpHeap = HeapAlloc(hHeap,	
		HEAP_ZERO_MEMORY, 
		100);
	HeapFree(hHeap, 0, lpHeap);

	/*
		1. hHeap ��64k����,���Ե����� VirtualAlloc
		2. lpHeap �Ƕ�hHeap����������ڴ��ַ�Ĺ���,��ַû�й���
	*/

	//�����:��������
	float fNum = 12.5;
	_tprintf(_T("fNum addr:%08X\n"), &fNum);

	/*
		�������ص�:
		1. ��λ����,��λ����Ϊ0
	*/


	_tprintf(_T("pNewBuff:%08X\n"), pNewBuff);
	_tprintf(_T("byArry:%08X\n"), byArry);
	system("pause");
	return 0;
}