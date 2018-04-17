#include <windows.h>
#include <stdio.h>

void test() {
	MessageBox(0, L"test", 0, 0);
}

int * g_pNum = nullptr;

int exceptHandler(EXCEPTION_POINTERS* pException) {
	printf("�쳣����:%08X\n",
		pException->ExceptionRecord->ExceptionCode);
	printf("�����쳣�ĵ�ַ:%08X\n",
		pException->ExceptionRecord->ExceptionAddress);
	//pException->ContextRecord->Eip = (DWORD)&test;
	printf("�쳣���˺���������\n");

	// g_pNum = new int(0);
	pException->ContextRecord->Eax = (DWORD)new int(0);

	return EXCEPTION_CONTINUE_EXECUTION;
}

void fun() {
	__try {
		printf("try��\n");
		*g_pNum = 0;
	}
	__except (exceptHandler(GetExceptionInformation())) {
		printf("except�鱻����\n");
	}
}


int main()
{
	__try {
		fun();
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		printf("main::except������\n");
	}



	return 0;
}
