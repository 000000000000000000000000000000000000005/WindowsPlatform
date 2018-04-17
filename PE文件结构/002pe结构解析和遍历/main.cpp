#include "PEOperation.h"
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

#define OFFSETOF(t,f)	((SIZE_T)&(((t *)0)->f))


void DatetimeToString(char* szTimeFormat, int nBuffLen, time_t uTimeStamp)
{
	tm time = { 0 };
	time_t t = uTimeStamp + 28800;
	gmtime_s(&time, &t);
	strftime(szTimeFormat, nBuffLen, "%Y-%m-%d/%H:%M:%S", &time);
}

char* pType[] =
{
	"",          // 0
	"���ָ��",   // 1
	"λͼ",   // 2
	"ͼ��",       // 3
	"�˵�",       // 4
	"�Ի���",      //5
	"�ַ����б�",  //6
	"����Ŀ¼",  //7
	"����",      //8
	"��ݼ�",  //9
	"�Ǹ�ʽ����Դ",  //A
	"��Ϣ�б�",  //B
	"���ָ����",  //C
	"",             // D
	"ͼ����",  //E
	"",         // F
	"�汾��Ϣ"//10
};

//������Դ��
void ParseResource(ULONG_PTR upResRoot, IMAGE_RESOURCE_DIRECTORY* pResDir, int nLevel)
{
	IMAGE_RESOURCE_DIR_STRING_U* pResName;
	wchar_t buff[MAX_PATH];
	switch (nLevel)
	{
	case 1:
	{
			  ULONG ulCount = pResDir->NumberOfIdEntries + pResDir->NumberOfNamedEntries;
			  //�������е���ԴĿ¼���
			  IMAGE_RESOURCE_DIRECTORY_ENTRY *pDirEntry = NULL;
			  pDirEntry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResDir + 1);

			  for (ULONG i = 0; i < ulCount; i++)
			  {
				  if (1 == pDirEntry[i].NameIsString)
				  {
					  pResName = (IMAGE_RESOURCE_DIR_STRING_U*)(pDirEntry[i].NameOffset + upResRoot);
					  memset(buff, 0, sizeof(buff));
					  memcpy(buff, pResName->NameString, pResName->Length);
					  wprintf(L"��Դ����:\"%s\"\n", buff);
				  }
				  else
				  {
					  if (pDirEntry[i].Id >= 0 && pDirEntry[i].Id <= 16)
					  {
						  printf("��Դ����:\"%s\"\n", pType[pDirEntry[i].Id]);
					  }
					  else
					  {
						  printf("��Դ����:[%d]\n", pDirEntry[i].Id);
					  }
				  }
				  // ��ȡ��һ���ƫ��
				  if (1 == pDirEntry[i].DataIsDirectory) {
					  // ��ȡ��һ��Ŀ¼(�ڶ���Ŀ¼����ڵ�ַ)
					  IMAGE_RESOURCE_DIRECTORY* pNextDir;
					  pNextDir = (IMAGE_RESOURCE_DIRECTORY*)(pDirEntry[i].OffsetToDirectory + upResRoot);
					  ParseResource(upResRoot, pNextDir, 2);
				  }
			  }

	}
		break;
	case 2:
	{
			  ULONG ulCount = pResDir->NumberOfIdEntries + pResDir->NumberOfNamedEntries;
			  IMAGE_RESOURCE_DIRECTORY_ENTRY* pDirEntry;
			  pDirEntry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResDir + 1);
			  //
			  for (DWORD i = 0; i < ulCount; ++i)
			  {
				  if (1 == pDirEntry[i].NameIsString)
				  {
					  pResName = (IMAGE_RESOURCE_DIR_STRING_U*)(pDirEntry[i].NameOffset + upResRoot);
					  memset(buff, 0, sizeof(buff));
					  memcpy(buff, pResName->NameString, pResName->Length);
					  wprintf(L"|-- ��ԴID:\"%s\"\n", buff);
				  }
				  else
				  {
					  printf("|-- ��ԴID[%d]\n", pDirEntry[i].Id);
				  }

				  if (1 == pDirEntry[i].DataIsDirectory)
				  {
					  IMAGE_RESOURCE_DIRECTORY* pNextDir;
					  pNextDir = (IMAGE_RESOURCE_DIRECTORY*)(pDirEntry[i].OffsetToDirectory + upResRoot);
					  ParseResource(upResRoot, pNextDir, 3);
				  }
			  }

	}
		break;
	case 3:
	{
			  IMAGE_RESOURCE_DIRECTORY_ENTRY* pDirEntry;
			  pDirEntry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResDir + 1);
			  if (0 == pDirEntry->DataIsDirectory)
			  {
				  IMAGE_RESOURCE_DATA_ENTRY* pDataEntry;
				  pDataEntry = (IMAGE_RESOURCE_DATA_ENTRY*)(pDirEntry->OffsetToData + upResRoot);
				  printf("|    |--- RVA:%08X,SIZE:%d\n", pDataEntry->OffsetToData, pDataEntry->Size);
			  }

	}
		break;
	default:
		break;
	}
}


int main(int argc, char* argv[])
{
	TCHAR szFilePath[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = _T("ִ���ļ�(*.exe)(*.dll)(*.sys)\0");
	ofn.lpstrInitialDir = _T("./");
	ofn.lpstrFile = szFilePath;
	ofn.nMaxFile = sizeof(szFilePath) / sizeof(*szFilePath);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
	if (!GetOpenFileName(&ofn))
	{
		return 1;
	}
	if (_tcscmp(szFilePath, _T("")) == 0)
	{
		return 1;
	}



	HANDLE hReadFile = CreateFile(szFilePath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hReadFile == INVALID_HANDLE_VALUE) {
		printf("�ļ�������\n");
		system("pause");
		return 1;
	}
	ULONG ulHigh = 0;
	ULONG ulFileSize = GetFileSize(hReadFile, &ulHigh);
	BYTE* pFileBuff = new BYTE[ulFileSize];
	ReadFile(hReadFile, pFileBuff, ulFileSize, &ulFileSize, NULL);

	if (!IsPEFile(pFileBuff))
	{
		printf("����һ��pe�ļ�");
		system("pause");
		return 1;
	}

	//��ȡ�ļ�ͷ����չͷ
	IMAGE_NT_HEADERS *pNtHeader = GetNtHeader(pFileBuff);

	char szDateBuff[MAX_PATH] = { 0 };
	DatetimeToString(szDateBuff, _countof(szDateBuff), pNtHeader->FileHeader.TimeDateStamp);
	//��ӡ�ļ�ͷ����Ϣ
	printf("�ļ�ͷ����Ϣ Machine:%x\n", pNtHeader->FileHeader.Machine);
	printf("�ļ�ͷ����Ϣ NumberOfSections:%x\n", pNtHeader->FileHeader.NumberOfSections);
	printf("�ļ�ͷ����Ϣ TimeDateStamp:%s\n", szDateBuff);
	printf("�ļ�ͷ����Ϣ SizeOfOptionalHeader:%x\n", pNtHeader->FileHeader.SizeOfOptionalHeader);
	printf("�ļ�ͷ����Ϣ Characteristics:%x\n", pNtHeader->FileHeader.Characteristics);
	printf("\n\n");

	//��ӡ��չͷ��Ϣ
	printf("��չͷ��Ϣ Magic:%x\n", pNtHeader->OptionalHeader.Magic);
	printf("��չͷ��Ϣ SizeOfCode:%x\n", pNtHeader->OptionalHeader.SizeOfCode);
	printf("��չͷ��Ϣ SizeOfInitializedData:%x\n", pNtHeader->OptionalHeader.SizeOfInitializedData);
	printf("��չͷ��Ϣ SizeOfUninitializedData:%x\n", pNtHeader->OptionalHeader.SizeOfUninitializedData);
	printf("��չͷ��Ϣ AddressOfEntryPoint:%x\n", pNtHeader->OptionalHeader.AddressOfEntryPoint);
	printf("��չͷ��Ϣ BaseOfCode:%x\n", pNtHeader->OptionalHeader.BaseOfCode);
	printf("��չͷ��Ϣ ImageBase:%x\n", pNtHeader->OptionalHeader.ImageBase);
	printf("��չͷ��Ϣ SectionAlignment:%x\n", pNtHeader->OptionalHeader.SectionAlignment);
	printf("��չͷ��Ϣ FileAlignment:%x\n", pNtHeader->OptionalHeader.FileAlignment);
	printf("��չͷ��Ϣ SizeOfImage:%x\n", pNtHeader->OptionalHeader.SizeOfImage);
	printf("��չͷ��Ϣ SizeOfHeaders:%x\n", pNtHeader->OptionalHeader.SizeOfHeaders);
	printf("��չͷ��Ϣ Subsystem:%x\n", pNtHeader->OptionalHeader.Subsystem);
	printf("��չͷ��Ϣ DllCharacteristics:%x\n", pNtHeader->OptionalHeader.DllCharacteristics);
	printf("��չͷ��Ϣ SizeOfStackReserve:%x\n", pNtHeader->OptionalHeader.SizeOfStackReserve);
	printf("��չͷ��Ϣ SizeOfStackCommit:%x\n", pNtHeader->OptionalHeader.SizeOfStackCommit);
	printf("��չͷ��Ϣ SizeOfHeapReserve:%x\n", pNtHeader->OptionalHeader.SizeOfHeapReserve);
	printf("��չͷ��Ϣ SizeOfHeapCommit:%x\n", pNtHeader->OptionalHeader.SizeOfHeapCommit);
	printf("��չͷ��Ϣ NumberOfRvaAndSizes:%x\n", pNtHeader->OptionalHeader.NumberOfRvaAndSizes);
	printf("\n\n");
	//���������rvaתoffset
	ULONG ulFileOffset = 0;
	ULONG ulRva = 0;
	RVA2Foa(pFileBuff, pNtHeader->OptionalHeader.BaseOfCode, &ulFileOffset);
	Foa2RVA(pFileBuff, pNtHeader->OptionalHeader.BaseOfCode, &ulRva);

	//����Ŀ¼
	IMAGE_DATA_DIRECTORY *pDirectory = GetDirectory(pFileBuff);


	for (ULONG i = 0; i < pNtHeader->OptionalHeader.NumberOfRvaAndSizes; i++)
	{
		printf("����Ŀ¼ ��%d������ Size:%x, VirtualAddress:%x\n", i, pDirectory[i].Size, pDirectory[i].VirtualAddress);
	}
	printf("\n\n");

	//�ֽ���Ϣ
	IMAGE_SECTION_HEADER* pSectionHeader = NULL;
	pSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);
	for (ULONG i = 0; i < pNtHeader->FileHeader.NumberOfSections; ++i)
	{
		printf("��%d���ֽ� Name:%s\n", i, pSectionHeader->Name);
		printf("��%d���ֽ� VirtualAddress:%x\n", i, pSectionHeader->VirtualAddress);
		printf("��%d���ֽ� SizeOfRawData:%x\n", i, pSectionHeader->SizeOfRawData);
		printf("��%d���ֽ� PointerToRawData:%x\n", i, pSectionHeader->PointerToRawData);
		printf("��%d���ֽ� Characteristics:%x\n", i, pSectionHeader->Characteristics);
		pSectionHeader += 1;
	}


	//��ȡ��������Ϣ
	IMAGE_EXPORT_DIRECTORY *pExportTable = GetExportTable(pFileBuff);
	if (NULL != pExportTable)
	{
		ULONG ulNameFoa;
		RVA2Foa(pFileBuff, pExportTable->Name, &ulNameFoa);
		printf("������ Name:%s\n", (char*)((ULONG_PTR)ulNameFoa + pFileBuff));
		printf("������ Base:%d\n", pExportTable->Base);
		printf("������ NumberOfFunctions:%d\n", pExportTable->NumberOfFunctions);
		printf("������ NumberOfNames:%d\n", pExportTable->NumberOfNames);

		ULONG ulAddressOfFunctionFoa = 0;
		ULONG  ulAddressOfNamesFoa = 0;
		ULONG  ulAddressOfNameOrdinalsFoa = 0;
		RVA2Foa(pFileBuff, pExportTable->AddressOfFunctions, &ulAddressOfFunctionFoa);
		RVA2Foa(pFileBuff, pExportTable->AddressOfNames, &ulAddressOfNamesFoa);
		RVA2Foa(pFileBuff, pExportTable->AddressOfNameOrdinals, &ulAddressOfNameOrdinalsFoa);
		//
		PULONG_PTR upAddressOfFunction = (PULONG_PTR)(pFileBuff + ulAddressOfFunctionFoa);
		PULONG_PTR upAddressOfName = (PULONG_PTR)(pFileBuff + ulAddressOfNamesFoa);
		WORD* upAddressOfNameOrdinals = (WORD*)(pFileBuff + ulAddressOfNameOrdinalsFoa);

		for (ULONG i = 0; i < pExportTable->NumberOfFunctions; i++)
		{
			if (0 == upAddressOfFunction[i]) continue;
			printf("�������ַ:%x\n", upAddressOfFunction[i]);

			ULONG ulIndex = 0;
			for (; ulIndex < pExportTable->NumberOfNames; ++ulIndex)
			{
				if (i == upAddressOfNameOrdinals[ulIndex]) break;
			}

			if (ulIndex == pExportTable->NumberOfNames)
			{
				printf("��������ŵ���:%x\n", i + pExportTable->Base);
				continue;
			}
			ULONG ulNameFoa = 0;
			RVA2Foa(pFileBuff, upAddressOfName[ulIndex], &ulNameFoa);
			char* pFunName = (char*)(pFileBuff + (ULONG_PTR)ulNameFoa);
			printf("������������Ϊ:%s\n", pFunName);
		}
	}
	printf("\n\n");

	//��ȡ�������Ϣ
	IMAGE_IMPORT_DESCRIPTOR* pImportTable = GetImportTable(pFileBuff);
	if (NULL != pImportTable)
	{
		while (pImportTable->Name != 0)
		{
			ULONG ulNameFoa = 0;
			RVA2Foa(pFileBuff, pImportTable->Name, &ulNameFoa);
			char* szImportDllName = (char*)((ULONG_PTR)pFileBuff + (ULONG_PTR)ulNameFoa);
			printf("���뺯����:%s\n", szImportDllName);

			ULONG ulIntFoa = 0;
			RVA2Foa(pFileBuff, pImportTable->OriginalFirstThunk, &ulIntFoa);
			//��ȡInt���ļ��еĵ�ַ
			ULONG_PTR* pInt = (ULONG_PTR*)(ulIntFoa + (ULONG_PTR)pFileBuff);
			while (*pInt != 0)
			{
				if (IMAGE_SNAP_BY_ORDINAL(*pInt))
				{
					printf("����Ž��е���, %x\n", *pInt & 0xFFFF);
				}
				else
				{
					IMAGE_IMPORT_BY_NAME* pImpByName = NULL;
					ULONG ulNameFoa = 0;
					RVA2Foa(pFileBuff, *pInt, &ulNameFoa);
					pImpByName = (IMAGE_IMPORT_BY_NAME*)(ulNameFoa + (ULONG_PTR)pFileBuff);
					printf("�����Ƶ���, ���:%d, ����:%s\n", pImpByName->Hint, pImpByName->Name);
				}
				++pInt;
			}
			++pImportTable;
		}
	}
	printf("\n\n");
	//��ȡ��Դ����Ϣ
	IMAGE_RESOURCE_DIRECTORY* pResourceDirectory = GetResourceDirectory(pFileBuff);
	if (NULL != pResourceDirectory)
	{
		ParseResource((ULONG_PTR)pResourceDirectory, pResourceDirectory, 1);
	}

	printf("\n\n");
	//��ȡ�ض�λ����Ϣ
	IMAGE_BASE_RELOCATION *pRelocationTab = GetBaseRelocation(pFileBuff);
	if (NULL != pRelocationTab)
	{
		struct TypeOffset
		{
			WORD Offset : 12;  // (1) ��СΪ12Bit���ض�λƫ��
			WORD Type : 4;    // (2) ��СΪ4Bit���ض�λ��Ϣ����ֵ
		};

		while (pRelocationTab->SizeOfBlock != 0)
		{

			TypeOffset* pTypeOffset;
			pTypeOffset = (TypeOffset*)(pRelocationTab + 1);
			ULONG ulCount = (pRelocationTab->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);

			for (ULONG i = 0; i < ulCount; ++i)
			{
				if (pTypeOffset[i].Type == 3)
				{
					//printf("RVA:%04X",pRelocationTab->VirtualAddress + pTypeOffset[i].Offset);

					ULONG dwFixAddr = pRelocationTab->VirtualAddress + pTypeOffset[i].Offset;
					ULONG dwFixAddrOffset = 0;
					RVA2Foa(pFileBuff, dwFixAddr, &dwFixAddrOffset);
					printf("��Ҫ�޸ĵĵ�ַ:RVA:0x%08X , OFS: 0x%08X\n", dwFixAddr, dwFixAddrOffset);
				}
			}
			//�¸��ض�λ���λ��
			pRelocationTab = (IMAGE_BASE_RELOCATION*)((ULONG_PTR)pRelocationTab + pRelocationTab->SizeOfBlock);
		}
	}

	//��ʱ�����
	IMAGE_DELAYLOAD_DESCRIPTOR* pDelayLoadDescriptor = GetDelayLoadDescriptor(pFileBuff);
	if (NULL != pDelayLoadDescriptor)
	{
		while (pDelayLoadDescriptor->DllNameRVA != 0)
		{
			ULONG ulNameFoa = 0;
			RVA2Foa(pFileBuff, pDelayLoadDescriptor->DllNameRVA, &ulNameFoa);
			char* szImportDllName = (char*)((ULONG_PTR)pFileBuff + (ULONG_PTR)ulNameFoa);
			printf("��ʱ���뺯����:%s\n", szImportDllName);

			ULONG ulIntFoa = 0;
			RVA2Foa(pFileBuff, pDelayLoadDescriptor->ImportNameTableRVA, &ulIntFoa);
			//��ȡInt���ļ��еĵ�ַ
			ULONG_PTR* pInt = (ULONG_PTR*)(ulIntFoa + (ULONG_PTR)pFileBuff);
			while (*pInt != 0)
			{
				if (IMAGE_SNAP_BY_ORDINAL(*pInt))
				{
					printf("��ʱ���� ����Ž��е���, %x\n", *pInt & 0xFFFF);
				}
				else
				{
					IMAGE_IMPORT_BY_NAME* pImpByName = NULL;
					ULONG ulNameFoa = 0;
					RVA2Foa(pFileBuff, *pInt, &ulNameFoa);
					pImpByName = (IMAGE_IMPORT_BY_NAME*)(ulNameFoa + (ULONG_PTR)pFileBuff);
					printf("��ʱ���� �����Ƶ���, ���:%d, ����:%s\n", pImpByName->Hint, pImpByName->Name);
				}
				++pInt;
			}

			++pDelayLoadDescriptor;
		}
	}

	//����tls��
	IMAGE_TLS_DIRECTORY* pTlsDirectory = GetImageTls(pFileBuff);
	if (NULL != pTlsDirectory)
	{
		printf("tls ���� StartAddressOfRawData:%x\n", pTlsDirectory->StartAddressOfRawData);
		printf("tls ���� EndAddressOfRawData:%x\n", pTlsDirectory->EndAddressOfRawData);
		if (pTlsDirectory->AddressOfCallBacks > 0)
		{
			ULONG uptAdressOfCallBackRva = pTlsDirectory->AddressOfCallBacks - pNtHeader->OptionalHeader.ImageBase;
			ULONG uAdressOfCallBackFoa = 0;
			RVA2Foa(pFileBuff, uptAdressOfCallBackRva, &uAdressOfCallBackFoa);
			ULONG_PTR* uptAdressOfCallBack = (ULONG_PTR*)((ULONG_PTR)pFileBuff + uAdressOfCallBackFoa);

			while (*uptAdressOfCallBack)
			{
				printf("tls ���� �ص�������ַ:%x\n", *uptAdressOfCallBack);
				uptAdressOfCallBack++;
			}
		}
	}

	//����ǩ����
	WIN_CERTIFICATE *pWinCertificate = GetCertificate(pFileBuff);
	if (pWinCertificate)
	{
		DWORD dwCertificateSize = pWinCertificate->dwLength - OFFSETOF(WIN_CERTIFICATE, bCertificate);
		PBYTE pTmpBuff = new BYTE[dwCertificateSize];
		memcpy(pTmpBuff, pWinCertificate->bCertificate, dwCertificateSize);
		HANDLE hAnsiFile = CreateFile(_T("d:/Certificate.ansi"),
			GENERIC_ALL,
			FILE_SHARE_READ,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		DWORD dwTmp;
		WriteFile(hAnsiFile, pTmpBuff, dwCertificateSize, &dwTmp, NULL);
		CloseHandle(hAnsiFile);
		delete[] pTmpBuff;
	}

	//�رն����
	CloseHandle(hReadFile);

	//�޸�imageBase
	ModifyImageBase(pFileBuff, 0x400000);
	ULONG ulRealWrite = 0;
	TCHAR szModifyBaseFile[MAX_PATH] = { 0 };
	_stprintf_s(szModifyBaseFile, _countof(szModifyBaseFile), _T("%s�޸�ImageBase.exe"), szFilePath);
	HANDLE hModifiImageBase = CreateFile(szModifyBaseFile,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	WriteFile(hModifiImageBase, pFileBuff, ulFileSize, &ulRealWrite, NULL);
	CloseHandle(hModifiImageBase);



	//���ӷֽ�
	BYTE pFillBuff[] =
	{
		"\xE8\x00\x00\x00\x00"	// call $+5
		"\x58"					// pop	eax
		"\x6A\x00"				// push	0
		"\x83\xC0\x17"			// add eax,0x17
		"\x50"					// push eax
		"\x83\xC0\x14"			// add eax,0x14
		"\x50"					// push eax
		"\x6A\x00"				// push 0
		"\xB8\x30\x88\x20\x74"	// mov eax,MessageBoxA
		"\xFF\xD0"				// call eax
		"\xC2\x04\x00"			// ret 0x04
		"����shellcode���ʺ�\0"  //20���ֽ�
		"��Һ�,����shellcode!!!" //24���ֽ�
	};

	// ��MessageBoxA�����ĵ�ַд�뵽shellcode��.
	*(DWORD*)(pFillBuff + 19) = (DWORD)&MessageBoxA;
	BYTE* pNewBuffOfAddress; //����½ں󻺳���
	int nNewFileSize;   //�����ӵĽڻ�������С
	IMAGE_SECTION_HEADER newSectionInfo = { 0 }; //�µķֽ���Ϣ
	AddSection(
		pFileBuff,
		ulFileSize,
		"hzh01",
		pFillBuff,
		sizeof(pFillBuff),
		IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE,
		&pNewBuffOfAddress,
		&nNewFileSize, 
		&newSectionInfo);

	IMAGE_NT_HEADERS *pNewNtHeader = GetNtHeader(pNewBuffOfAddress);
	pNewNtHeader->OptionalHeader.AddressOfEntryPoint = newSectionInfo.VirtualAddress;

	TCHAR szAddSectionFile[MAX_PATH] = { 0 };
	_stprintf_s(szAddSectionFile, _countof(szAddSectionFile), _T("%s���ӷֽ�.exe"), szFilePath);

	HANDLE hAddSectionFile = CreateFile(szAddSectionFile,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	WriteFile(hAddSectionFile, pNewBuffOfAddress, nNewFileSize, &ulRealWrite, NULL);
	CloseHandle(hAddSectionFile);
	delete[]  pNewBuffOfAddress;
	pNewBuffOfAddress = NULL;

	//�ѵ�����ƶ����µķֽ�
	ZeroMemory(&newSectionInfo, sizeof(newSectionInfo));
	MoveImport(
		pFileBuff,
		ulFileSize,
		"myimp",
		IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE,
		&pNewBuffOfAddress,
		&nNewFileSize,
		&newSectionInfo
		);

	//���ӵ���dll
	AddImportDll(
		pNewBuffOfAddress,
		"002pe�ṹ������ӵ�����Dll.dll",
		1
		);



	TCHAR szMovImport[MAX_PATH] = { 0 };
	_stprintf_s(szMovImport, _countof(szMovImport), _T("%s�ƶ���������޸ĵ���dll.exe"), szFilePath);

	HANDLE hMoveImport = CreateFile(szMovImport,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	WriteFile(hMoveImport, pNewBuffOfAddress, nNewFileSize, &ulRealWrite, NULL);
	CloseHandle(hMoveImport);
	delete[]  pNewBuffOfAddress;
	pNewBuffOfAddress = NULL;


	//��β����
	delete[] pFileBuff;

	system("pause");
	return 0;
}
