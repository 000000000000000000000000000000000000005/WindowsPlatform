#include <Windows.h>
#include "UnDocoumentApi.h"
#include <stdio.h>
#include <locale.h>

int main(int argc, char* argv[])
{
	// ���ñ����ַ���
	setlocale(LC_ALL, "chs");

	//////////////////////////////////////////////////////////////////////////
	// ����δ�ĵ�����API����������Ϣ
	// ����NtQuerySystemInformation����û���ĵ���, ���,windwos��ͷ�ļ���û�иú�����
	// ����, ���, ��Ҫʹ���������, �����Լ���ȡ.
	// ��ȡ����:
	// 1. �ú�����ntdll.dll�ĵ�������, ���,����ʹ��LoadLibrary�õ�ntdll.dll�ļ��ػ�ַ
	//    ��ͨ��GetProcAddress������ȡ�ú����ĵ�ַ.
	// 2. ���庯��ָ��, ���ոú����ĵ�ַ.
	// 3. ���øú���
	// 4. ����������Ϣ
	//

	//1. �õ�������ַ
	HMODULE hNtdll = LoadLibrary(L"ntdll.dll");
	fnNtQuerySystemInformation ZwQuerySystemInformation;

	ZwQuerySystemInformation = \
		(fnNtQuerySystemInformation)GetProcAddress(hNtdll, "NtQuerySystemInformation");


	//2. ���ú���, ��ε���,��Ϊ�˵õ�������Ϣ�Ļ������ֽ���
	DWORD dwNeedSize = 0;
	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, /*Ҫ��ѯ����Ϣ������*/
		0, /*������Ϣ�Ļ������׵�ַ*/
		0, /*������Ϣ�Ļ�����������ֽ���*/
		&dwNeedSize/*�����������Ϣ������ֽ���*/
		);

	//2.1 ���ݵõ��Ļ�������С����ѿռ�
	SYSTEM_PROCESS_INFORMATION* pProcInfo = NULL;
	pProcInfo = (SYSTEM_PROCESS_INFORMATION *)new BYTE[dwNeedSize];

	//2.2 �ٴε��ú���,��ȡ������Ϣ
	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation,  /*Ҫ��ѯ����Ϣ������*/
		pProcInfo,/*������Ϣ�Ļ������׵�ַ*/
		dwNeedSize,/*������Ϣ�Ļ�����������ֽ���*/
		&dwNeedSize /*�����������Ϣ������ֽ���*/
		);


	//3. ��ʼ����
	while (pProcInfo->NextEntryDelta != 0) {

		// 3.1 �����Ϣ
		wprintf(L"PID: %5d Name:%s\n",
			pProcInfo->InheritedFromProcessId,/*����PID*/
			pProcInfo->ProcessName.Buffer  /*������*/
			);


		// 3.2 ��������һ���ṹ��
		pProcInfo = (SYSTEM_PROCESS_INFORMATION*)((DWORD)pProcInfo + pProcInfo->NextEntryDelta);
	}

}