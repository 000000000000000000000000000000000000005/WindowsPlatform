#include <stdio.h>
#include <windows.h>

int main(int argc, char* argv[])
{
	LPVOID pBuff = NULL;
	LPVOID pReserveBuff = NULL;
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	//�ڴ�ķ�������Ϊ64k
	pReserveBuff = VirtualAlloc(
		NULL,
		1024 * 64 * 3,
		MEM_RESERVE,
		PAGE_NOACCESS
		);

	if (NULL == pBuff)
	{
		printf("Ԥ�����ڴ�ʧ��\n");
	}

	// ����д��ո�Ԥ�����ڴ�,
	__try {
		*(DWORD*)pBuff = 0;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		printf("Ԥ�����ڴ���뾭���ύ����ʹ��\n");
	}

	//�ڴ�ķ�ҳ����Ϊ4k�����ڴ�������Ȳ���һ��Ŷ������
	pBuff = VirtualAlloc(pReserveBuff,
		4096, 
		MEM_COMMIT,
		PAGE_READWRITE
		);

	pBuff = VirtualAlloc((LPVOID)((DWORD)pBuff + 4096), 
		4096,  
		MEM_COMMIT,
		PAGE_READWRITE
		);

	VirtualAlloc((LPVOID)((DWORD)pBuff + 4096),
		4090,
		MEM_COMMIT,
		PAGE_READWRITE
		);

	ZeroMemory(&mbi, sizeof(mbi));

	//�ڴ�״̬��
	// #define MEM_COMMIT                  0x1000
	// #define MEM_RESERVE                 0x2000
	// #define MEM_DECOMMIT                0x4000
	// #define MEM_RELEASE                 0x8000

	//�ڴ����ͣ�
	// #define MEM_FREE                    0x10000
	// #define MEM_PRIVATE                 0x20000
	// #define MEM_MAPPED                  0x40000
	// #define MEM_RESET                   0x80000

	//�ڴ�����
	// #define PAGE_NOACCESS          0x01     
	// #define PAGE_READONLY          0x02     
	// #define PAGE_READWRITE         0x04     
	// #define PAGE_WRITECOPY         0x08   

	// 	typedef struct _MEMORY_BASIC_INFORMATION {
	// 		PVOID BaseAddress;        =>VirtualQuery��һ����������ҳ���׵�ַ4k����
	// 		PVOID AllocationBase;     =>Ԥ���׵�ַ����ַ��������Ϊ64k
	// 		DWORD AllocationProtect; =>Ԥ��ʱ������ڴ�����
	// 		SIZE_T RegionSize;    => ��BaseAddress��ʼ������ͬ���ԣ���/д/ִ�У����ڴ�
	// 		DWORD State;   =>MEM_RESERVE��MEM_DECOMMIT��MEM_RELEASE��MEM_COMMIT
	// 		DWORD Protect;  =>�ύʱ������ڴ�����
	// 		DWORD Type;  => MEM_PRIVATE��MEM_MAPPED��MEM_RESET
	// 	} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;
	

	//
	VirtualQuery((LPVOID)((DWORD)pBuff  + 24),
		&mbi,
		sizeof(mbi)
		);

	VirtualFree(pBuff,  /*��ʼ��ַ*/
		4096,   /*ȡ���ύ���ֽ���*/
		MEM_DECOMMIT  /*ȡ���ύ�ı�־*/
		);

	*(DWORD*)pBuff = 0;

	//
	VirtualFree(pReserveBuff,
		0,
		MEM_RELEASE);

	//���Ա���
	//*(DWORD*)pBuff = 0;

	system("pause");
	return 0;
}