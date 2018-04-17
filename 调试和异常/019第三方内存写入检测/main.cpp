#include <windows.h>
#include <stdio.h>

typedef struct _POSITION_
{
	DWORD dx;
	DWORD dz;
	DWORD dy;
}POSITION, *PPOSITION;

#define BASE_SIZE 0x1000
#define WALK_ADD 10
DWORD WINAPI WatchThread(LPVOID Param)
{
	ULONG size = 0;
	DWORD p = 0;
	UINT  Ret = 0;
	PVOID px[0x400] = { 0 };
	while (1)
	{
		size = 0x400;
		p = 0;
		Ret = GetWriteWatch(WRITE_WATCH_FLAG_RESET, Param, BASE_SIZE, px, &size, &p);
		if (Ret == 0
			&& size != 0)
		{
			MessageBoxW(NULL, L"���ֵ���������޸Ĺؼ��ڴ�", L"���ֵ��������", MB_OK);
		}
	}
	return 0;
}
int __cdecl main(int argc, char *argv[])
{
	//����Base��ַ�ڴ�
	PVOID Base = VirtualAlloc(NULL, BASE_SIZE, MEM_RESERVE | MEM_COMMIT | MEM_WRITE_WATCH, PAGE_READWRITE);
	PPOSITION pos = (PPOSITION)Base;
	//��ʼ������
	pos->dx = pos->dy = pos->dz = 1000;
	//��ռ�ؼ�¼
	ResetWriteWatch(Base, BASE_SIZE);
	//��������߳�
	HANDLE hThread = CreateThread(NULL, 0, WatchThread, Base, 0, NULL);
	while (1)
	{
		//��ͣ����߳�
		SuspendThread(hThread);//Ҳ����ͨ��������ʽ���У���������ͣ�߳�ֻ�Ǽ�ģ��
		//ģ����·����
		pos->dx += WALK_ADD;
		//�������
		ResetWriteWatch(Base, BASE_SIZE);
		ResumeThread(hThread);
		//���X����
		printf("x = %d\n", pos->dx);
		Sleep(1000);
	}
	return 0;
}