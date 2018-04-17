#include "LibaryAnti.h"
#include <windows.h>
#include <tchar.h>
#include <wchar.h>
#include "Dbg.h"
#include "AntiCommon.h"
#include "ProcessOperation.h"
#include "PEOperation.h"
#include "PEAnti.h"
#include "UnDocoumentApi.h"

#include "detours/detours.h"
#pragma comment(lib,"detours/lib.X86/detours.lib")

// BegEngine��ʹ�õ�ʱ����Ҫ������
#define BEA_ENGINE_STATIC
#define BEA_USE_STDCALL
#include "BeaEngine_4.1/Win32/headers/BeaEngine.h"
#pragma comment (lib , "BeaEngine_4.1/Win32/Win32/Lib/BeaEngine.lib")
// ��ֹ�������
#pragma comment(linker, "/NODEFAULTLIB:\"crt.lib\"")



//////////////////////////////���Ͷ���///////////////////////////////////////

typedef NTSTATUS(WINAPI *fpLdrLoadDll)(
	IN PWCHAR PathToFile OPTIONAL,
	IN ULONG Flags OPTIONAL,
	IN PUNICODE_STRING ModuleFileName,
	OUT PHANDLE ModuleHandle);


typedef HMODULE (WINAPI *fpLoadLibraryA)(
	_In_ LPCSTR lpLibFileName
);

typedef HMODULE (WINAPI *fpLoadLibraryW)(
_In_ LPCWSTR lpLibFileName
);

//////////////////////////////�ڲ�����///////////////////////////////////////
static fpLdrLoadDll s_fpSrcLdrDll = NULL;
static fpLoadLibraryA s_fpLoadLibrayA = NULL;
static fpLoadLibraryW s_fpLoadLibrayW = NULL;
static bool s_bShellCode = false;  //�Ƿ�shell code����Ϣ���Ӽ��ض�̬�⡢û��ʹ�ñ�׼�ӿڼ���dll
static bool s_bHidMode = false;   //�Ƿ񣺼��صĶ�̬���Ƿ�������ģ��Ķ���

//��⺯����Ҫ��ʱ�����
static WCHAR s_szLoadlibrayDllName[MAX_PATH] = { 0 };
static LPVOID s_lpCheckStack = NULL;  //����LoadlibraryA����LoadlibraryW�Ķ�ջ��ַ + 4���Ƿ��ص�ַ
static LPVOID s_lpDllNameAddr = NULL; //dll���ֵĵ�ַ
static bool s_bCheckReAddrEnumFuncOk = false; //����ģ�������loadlibary�ķ���ֵ�ĸ�������



//���loadlibary�ĵ��ö�ջ��������õ�ַ�������κ�ģ�飬�϶���shellcodeע��
static bool  CheckReAddrEnumFunc(IN  void *callBackParameter, IN MODULEENTRY32* pModuleEntry)
{
	DWORD dwCmpAddr = (DWORD)callBackParameter;
	IMAGE_NT_HEADERS*pNtHeader = GetNtHeader(pModuleEntry->modBaseAddr);
	IMAGE_SECTION_HEADER* pSectionHeader = NULL;
	pSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);
	for (ULONG i = 0; i < pNtHeader->FileHeader.NumberOfSections; ++i)
	{
		//��������ǿ�ִ�е�
		if (IMAGE_SCN_MEM_EXECUTE & pSectionHeader->Characteristics)
		{
			DWORD dwBegin = (DWORD)pModuleEntry->modBaseAddr + pSectionHeader->VirtualAddress;
			DWORD dwSectionCnt = pSectionHeader->SizeOfRawData / pNtHeader->OptionalHeader.SectionAlignment +
				(pSectionHeader->SizeOfRawData % pNtHeader->OptionalHeader.SectionAlignment ? 1 : 0);
			DWORD dwSectionSize = dwSectionCnt *  pNtHeader->OptionalHeader.SectionAlignment;
			DWORD dwEnd = dwBegin + dwSectionSize;
			if (dwCmpAddr >= dwBegin && dwCmpAddr < dwEnd)
			{
				//��������֪ģ��������ģ��Ŀ�϶����shellcode
				HANDLE hFile = NULL;
				hFile = CreateFile(pModuleEntry->szExePath,
					GENERIC_READ,
					FILE_SHARE_READ,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL
					);
				if (INVALID_HANDLE_VALUE == hFile)
				{
					return false;
				}
				DWORD	dwLowSize = GetFileSize(hFile, NULL);
				PBYTE pFileBuff = new BYTE[dwLowSize];
				ZeroMemory(pFileBuff, dwLowSize);
				DWORD dwRealRead = 0;
				ReadFile(hFile, pFileBuff, dwLowSize, &dwRealRead, NULL);
				DWORD dwRva = dwCmpAddr - (ULONG)(pModuleEntry->modBaseAddr);
				DWORD dwFoa = 0;
				RVA2Foa(pFileBuff, dwRva, &dwFoa);
				BYTE btOrginValue = *(BYTE*)(pFileBuff + dwFoa);
				BYTE btNowValue = *(BYTE*)dwCmpAddr;
				delete[] pFileBuff;
				CloseHandle(hFile);

				//���ԭʼ���ݺ����ڵ�������ȴ���������loadlibary����
				if (btOrginValue == btNowValue) s_bCheckReAddrEnumFuncOk = true;
				return true;
			}

		}
		pSectionHeader += 1;
	}
	return false;
}


//��鶯̬��
static void CheckDll(PWSTR pszDllName)
{
	HMODULE hMod = GetModuleHandleW(pszDllName);
	if (NULL != hMod) return;

	//����û��ʹ��library���ض�̬��
	if (wcscmp(pszDllName, s_szLoadlibrayDllName) != 0)
	{
		s_bShellCode = true;
		return;
	}
	//��ȡ���ص�ַ
	DWORD dwRetAddr = *(DWORD*)((DWORD)s_lpCheckStack - 4);

	//������ǰ����ģ�飬�������ֵ�������κ�ģ�飬�������
	EnumModule(GetCurrentProcessId(), CheckReAddrEnumFunc, (void*)dwRetAddr);
	bool bCheckRetResult = s_bCheckReAddrEnumFuncOk;
	s_bCheckReAddrEnumFuncOk = false;
	if (!bCheckRetResult)  //ģ�����Ƿ�����
	{
		__asm int 3
		s_bShellCode = true;
		return;
	}
}


//ɽկ�汾��ldrloaddll
static NTSTATUS WINAPI MyLdrLoadDll(
	IN PWCHAR PathToFile OPTIONAL,
	IN ULONG Flags OPTIONAL,
	IN PUNICODE_STRING ModuleFileName,
	OUT PHANDLE ModuleHandle)
{
	NTSTATUS ntStatus;
	WCHAR szDllName[MAX_PATH];
	ZeroMemory(szDllName, sizeof(szDllName));
	memcpy(szDllName, ModuleFileName->Buffer, ModuleFileName->Length);
	CheckDll(szDllName);
	//�ڼ���֮ǰ�ж��¸�ģ���Ƿ񱻼��ع�
	HMODULE hPreMod = GetModuleHandleW(szDllName);
	ntStatus = s_fpSrcLdrDll(PathToFile, Flags, ModuleFileName, ModuleHandle);
	DWORD dwLastError = GetLastError();
	//���û�б����ع�����ִ����s_fpSrcLdrDll�ɹ������Ƿ����������Լ��Ĳ���
	if (STATUS_SUCCESS == ntStatus &&NULL == hPreMod)
	{
		//GetModuleHandleW��ʵ�Ƕ�ȡpeb����Ϣ,û��Ҫ�ٱ���һ����
		HMODULE hNowMod = GetModuleHandleW(szDllName);
		if (NULL == hNowMod) s_bHidMode = true;
		//��Ϊ�µ�dll������֪ͨ���¼���md5
		CheckModPEInfo();
	}
	//�ָ�������
	SetLastError(dwLastError);
	return ntStatus;
}

//ɽկ�汾��LoadLibaryA
static HMODULE WINAPI  MyLoadLibraryA(
	_In_ LPCSTR lpLibFileName
	)
{
	if (NULL == lpLibFileName) return NULL;

	WCHAR szTmpBuff[MAX_PATH];
	CHAR_TO_WCHAR(lpLibFileName, szTmpBuff);
	wcscpy_s(s_szLoadlibrayDllName, _countof(s_szLoadlibrayDllName), szTmpBuff);
	s_lpDllNameAddr = (LPVOID)lpLibFileName;
	s_lpCheckStack = (LPVOID)&lpLibFileName;
	return s_fpLoadLibrayA(lpLibFileName);
}

//ɽկ�汾��LoadLibraryW
static HMODULE WINAPI MyLoadLibraryW(
	_In_ LPCWSTR lpLibFileName
	)
{
	if (NULL == lpLibFileName) return NULL;
	wcscpy_s(s_szLoadlibrayDllName, _countof(s_szLoadlibrayDllName), lpLibFileName);
	s_lpDllNameAddr = (LPVOID)lpLibFileName;
	s_lpCheckStack = (LPVOID)&lpLibFileName;
	return s_fpLoadLibrayW(lpLibFileName);



}



//////////////////////////////����ӿ�///////////////////////////////////////
void MonitorLoadDll()
{
	HMODULE hNtDll = LoadLibrary(_T("ntdll.dll"));
	HMODULE hK32 = LoadLibrary(_T("Kernel32.dll"));
	s_fpSrcLdrDll = (fpLdrLoadDll)GetProcAddress(hNtDll, "LdrLoadDll");
	s_fpLoadLibrayA = (fpLoadLibraryA)GetProcAddress(hK32, "LoadLibraryA");
	s_fpLoadLibrayW = (fpLoadLibraryW)GetProcAddress(hK32, "LoadLibraryW");
	//
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID*)&s_fpSrcLdrDll, MyLdrLoadDll);
	DetourAttach((PVOID*)&s_fpLoadLibrayA, MyLoadLibraryA);
	DetourAttach((PVOID*)&s_fpLoadLibrayW, MyLoadLibraryW);
	DetourTransactionCommit();
}

//�ж��Ƿ���shellcodeע��
bool IsFondShellCode()
{
	return s_bShellCode;
}

bool IsFondModHidSelf()
{
	return s_bHidMode;
}
