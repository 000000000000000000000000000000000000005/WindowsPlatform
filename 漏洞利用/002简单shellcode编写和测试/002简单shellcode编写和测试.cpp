// ��ϰ2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>



int _tmain(int argc, _TCHAR* argv[])
{
	//shell code ����
	__asm
	{
		pushad;
		sub esp, 0x20;
		jmp tag_ShellCode;

		//  [tag_Next - 0x52] "GetProcAddress"
		_asm _emit(0x47)  _asm _emit(0x65)   _asm _emit(0x74)  _asm _emit(0x50)
		_asm _emit(0x72)  _asm _emit(0x6F)   _asm _emit(0x63)  _asm _emit(0x41)
		_asm _emit(0x64)  _asm _emit(0x64)   _asm _emit(0x72)  _asm _emit(0x65)
		_asm _emit(0x73)  _asm _emit(0x73)

		//  [tag_Next - 0x44] "LoadLibraryExA"
		_asm _emit(0x4C)  _asm _emit(0x6F)   _asm _emit(0x61)  _asm _emit(0x64)
		_asm _emit(0x4C)  _asm _emit(0x69)   _asm _emit(0x62)  _asm _emit(0x72)
		_asm _emit(0x61)  _asm _emit(0x72)   _asm _emit(0x79)  _asm _emit(0x45)
		_asm _emit(0x78)  _asm _emit(0x41)  _asm _emit(0x00)

		//  [tag_Next - 0x35] "User32.dll"
		_asm _emit(0x55)  _asm _emit(0x73)   _asm _emit(0x65)  _asm _emit(0x72)
		_asm _emit(0x33)  _asm _emit(0x32)   _asm _emit(0x2E)  _asm _emit(0x64)
		_asm _emit(0x6C)  _asm _emit(0x6C)   _asm _emit(0x00)

		//  [tag_Next - 0x2A] "MessageBoxA"
		_asm _emit(0x4D)  _asm _emit(0x65)   _asm _emit(0x73)  _asm _emit(0x73)
		_asm _emit(0x61)  _asm _emit(0x67)   _asm _emit(0x65)  _asm _emit(0x42)
		_asm _emit(0x6F)  _asm _emit(0x78)   _asm _emit(0x41)  _asm _emit(0x00)

		//  [tag_Next - 0x1E] "ExitProcess"
		_asm _emit(0x45)  _asm _emit(0x78)   _asm _emit(0x69)  _asm _emit(0x74)
		_asm _emit(0x50)  _asm _emit(0x72)   _asm _emit(0x6F)  _asm _emit(0x63)
		_asm _emit(0x65)  _asm _emit(0x73)   _asm _emit(0x73)  _asm _emit(0x00)

		//  [tag_Next - 0x12] "Hello World"
		_asm _emit(0x48)  _asm _emit(0x65)   _asm _emit(0x6C)  _asm _emit(0x6C)
		_asm _emit(0x6F)  _asm _emit(0x20)   _asm _emit(0x31)  _asm _emit(0x35)
		_asm _emit(0x50)  _asm _emit(0x42)   _asm _emit(0x21)  _asm _emit(0x00)

	tag_ShellCode:
		//1. GetPc
		call tag_Next;
		tag_Next :
		pop ebx; // ebx == BaseAddr

		//2 ��ȡ�ؼ�ģ���ַ
		mov esi, dword ptr fs : [0x30];
		mov esi, [esi + 0x0C];
		mov esi, [esi + 0x1C];
		mov esi, [esi];
		mov edx, [esi + 0x08];   //edxΪKernel32.dll�ĵ�ַ

		//3. ��ȡGetProcAddress�ĺ�����ַ
		push ebx;
		push edx;
		call fun_GetProcAddress;
		mov esi, eax;

		//4. ��ȡLoadLibaryExA�ĵ�ַ
		lea  ecx, [ebx - 0x43];   // loadlibaryExa���ַ���
		push ecx;
		push edx;
		call eax;

		//5. ����payload����
		push ebx;   // baseaddr
		push esi;    // Getprocess
		push  eax;  //loadlibraryexa
		push edx;  // kernel32 ����ַ
		call fun_PayLoad;



	fun_GetProcAddress:  //(imageBase, BaseAddr)
		push ebp;
		mov ebp, esp;
		sub esp, 0x0C;
		push edx;

		//1. ��ȡeax,ent, ept�ĵ�ַ
		mov edx, [ebp + 0x8];  // kernel32.dll
		mov esi, [edx + 0x3C];  // image_dos_header.e_lfanew
		lea esi, [edx + esi];   // pe�ļ�ͷ��va
		mov esi, [esi + 0x78]; // esi = �������rva
		lea esi, [edx + esi];  //esi = �������va
		mov edi, [esi + 0x1C];  //edi ������ַ���rva
		lea edi, [edx + edi];  // edi ������ַ���va
		mov[ebp - 0x4], edi;  // [ebp - 0x4]��ŵ��ǵ�����ַ��va
		mov edi, [esi + 0x20];  //edi =�������ֱ��rva
		lea edi, [edx + edi];   // edi =�������ֱ��va
		mov[ebp - 0x8], edi; // [ebp - 0x8]���ڵ������ֱ�
		mov edi, [esi + 0x24]; // edi ������ű��rva
		lea edi, [edx + edi]; // edi �ǵ�����ű��va
		mov[ebp - 0xC], edi;  //[ebp - 0xc]�ǵ�����ű��va

			//2. ѭ���Ա�ent�еĺ�����
		xor eax, eax;
		jmp tag_FistCmp;
	tag_CmpFunNameLoop:
		inc eax;
	tag_FistCmp:
		mov esi, [ebp - 0x8];  // esi == �������ֵı��va
		mov esi, [esi + 4 * eax];
		mov edx, [ebp + 0x8];  // ȡ��imagebase
		lea esi, [edx + esi];  //��ȡ����
		mov ebx, [ebp + 0xC];  // BaseAddr
		lea edi, [ebx - 0x51];  // edi == "GetProcAddress"
		mov ecx, 0x0E;
		cld;
		repe cmpsb;
		jne tag_CmpFunNameLoop;

		//3. �ɹ����ҵ���Ӧ�����
		mov esi, [ebp - 0xC];   // esi = Eot
		xor edi, edi;
		mov di, [esi + eax * 2];

		//4. ʹ�������Ϊ�����ҵ�����������Ӧ�ĺ�����ַ
		mov edx, [ebp - 0x4];   // eat
		mov esi, [edx + edi * 4]; // ������ҵ�������rva
		mov edx, [ebp + 0x8]; //ImageBase

		//5. ���ػ�ȡ�ؼ�������ַ
		lea eax, [edx + esi];  // edx== imagebase, esiΪ���

		pop edx;
		mov esp, ebp;
		pop ebp;
		retn 0x8;


	fun_PayLoad: //(Kernel32_base, LoadLibraryExA, GetProcAddress, BaseAddress)
		push ebp;
		mov ebp, esp;
		sub esp, 0x8;
		mov ebx, [ebp + 0x14]; // ebx = Param_4

		//1. ��ȡMessageBox�ĵ�ַ
		lea ecx, [ebx - 0x34];
		push 0;
		push 0;
		push ecx;  // "user32.dll"
		call[ebp + 0xC];  // loadlibarayExA

		lea ecx, [ebx - 0x29];   //messageboxA
		push ecx;
		push eax;  // user32�ĵ�ַ
		call [ebp + 0x10];   //GetProcAddress
		mov[ebp - 0x4], eax;  //[ebp - 4]��ŵ���MessageBoxA�ĵ�ַ

		//2. ��ȡExitProcess�ĵ�ַ
		lea ecx, [ebx - 0x1D];  // "ExitProcess"
		push ecx;
		push[ebp + 0x8];  // kernel32����ַ
		call[ebp + 0x10];  //GetprocAddress
		mov[ebp - 0x8], eax;

		//3. ��ʾhello 15pb
		lea  ecx, [ebx - 0x11]; //"hello 15pb"
		push 0;
		push ecx;
		push ecx;
		push 0;
		call[ebp - 0x4];

		//4. ִ���˳�
		push 0;
		call[ebp - 0x8];

		mov esp, ebp;
		pop ebp;
		retn 0x10;
	}
	printf("��ֹ�Ż�\n");
	system("pause");
	return 0;
}

