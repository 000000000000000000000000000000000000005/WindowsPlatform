#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <map>
#include <string>


///////////////////////////////�ڲ�����/////////////////////////////////////
//��������
static std::map<DWORD, TCHAR*> s_mapSrvType = {
	{ SERVICE_FILE_SYSTEM_DRIVER, _T("SERVICE_FILE_SYSTEM_DRIVER") },
	{ SERVICE_KERNEL_DRIVER, _T("SERVICE_KERNEL_DRIVER") },
	{ SERVICE_WIN32_OWN_PROCESS, _T("SERVICE_WIN32_OWN_PROCESS") },
	{ SERVICE_WIN32_SHARE_PROCESS, _T("SERVICE_WIN32_SHARE_PROCESS") },
};

//����״̬
static std::map<DWORD, TCHAR*> s_mapSrvState = {
	{ SERVICE_CONTINUE_PENDING, _T("SERVICE_CONTINUE_PENDING") },
	{ SERVICE_PAUSE_PENDING, _T("SERVICE_PAUSE_PENDING") },
	{ SERVICE_PAUSED, _T("SERVICE_PAUSED") },
	{ SERVICE_RUNNING, _T("SERVICE_RUNNING") },
	{ SERVICE_START_PENDING, _T("SERVICE_START_PENDING") },
	{ SERVICE_STOP_PENDING, _T("SERVICE_STOP_PENDING") },
	{ SERVICE_STOPPED, _T("SERVICE_STOPPED") },
};

//������������
static std::map<DWORD, TCHAR*> s_mapSrvStartType = {
	{ SERVICE_AUTO_START, _T("SERVICE_AUTO_START") },
	{ SERVICE_BOOT_START, _T("SERVICE_BOOT_START") },
	{ SERVICE_DEMAND_START, _T("SERVICE_DEMAND_START") },
	{ SERVICE_DISABLED, _T("SERVICE_DISABLED") },
	{ SERVICE_SYSTEM_START, _T("SERVICE_SYSTEM_START") },
};



//��������
static void EnumSrv()
{
	//1. ��Զ�̼����������ƹ���
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == hSCM) return;

	//2. ��һ�ε�����Ҫ��ȡ�ڴ��С
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatusEx(
		hSCM,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		NULL,
		0,
		&dwSize,
		&dwServiceNum,
		NULL,
		NULL
		);

	//3. ������Ҫ���ڴ�
	LPENUM_SERVICE_STATUS_PROCESS pEnumService = (LPENUM_SERVICE_STATUS_PROCESS)new char[dwSize];

	//4. �ڶ���ö��
	BOOL bStatus = FALSE;
	bStatus = EnumServicesStatusEx(
		hSCM,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		(PBYTE)pEnumService,
		dwSize,
		&dwSize,
		&dwServiceNum,
		NULL,
		NULL
		);

	//5. ������Ϣ
	for (DWORD i = 0; i < dwServiceNum; i++)
	{
		_tprintf(_T("��������:%s\n\t����״̬:%s\n\t��������:%s\n"),
			pEnumService[i].lpServiceName,
			s_mapSrvState[pEnumService[i].ServiceStatusProcess.dwCurrentState],
			s_mapSrvType[pEnumService[i].ServiceStatusProcess.dwServiceType]
			);

		//��һ������
		SC_HANDLE hService = OpenService(
			hSCM,
			pEnumService[i].lpServiceName,
			SERVICE_QUERY_CONFIG
			);
		if (NULL == hService) continue;

		//��һ�ε��û�ȡ��Ҫ�Ļ�������С
		QueryServiceConfig(hService, NULL, 0, &dwSize);

		//�����ڴ�
		LPQUERY_SERVICE_CONFIG pServiceConfig = (LPQUERY_SERVICE_CONFIG) new char[dwSize];

		//�ڶ��ε��ã���ȡ��Ϣ
		QueryServiceConfig(hService, pServiceConfig, dwSize, &dwSize);
		_tprintf(_T("\t��������:%s\n"), s_mapSrvStartType[pServiceConfig->dwStartType]);
		_tprintf(_T("\t·��:%s\n"), pServiceConfig->lpBinaryPathName);

		delete[] pServiceConfig;
		CloseServiceHandle(hService);
	}

	//6. �����ڴ�
	CloseServiceHandle(hSCM);
	delete[] pEnumService;
}

//�򿪷���
static void OpenSrv()
{
	char pszServiceName[MAX_PATH] = { 0 };
	SC_HANDLE hSCM = NULL;
	SC_HANDLE hService = NULL;
	DWORD dwSize = 0;
	SERVICE_STATUS serviceStatus = { 0 };

	printf("������򿪷������֣�");
	scanf_s("%s", pszServiceName, _countof(pszServiceName));
	fflush(stdin);

	//
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == hSCM)
		goto __EXIT;
	hService = OpenServiceA(
		hSCM,
		pszServiceName,
		SERVICE_ALL_ACCESS
		);
	if (NULL == hService)
	{
		printf("�޷��򿪷���:%s\n", pszServiceName);
		goto __EXIT;
	}

	//��ȡ����ǰ��״̬
	QueryServiceStatus(hService, &serviceStatus);
	if (ERROR_ACCESS_DENIED == GetLastError())
	{
		printf("Ȩ�޲���\n");
		goto __EXIT;
	}

	if (SERVICE_STOPPED != serviceStatus.dwCurrentState)
	{
		printf("�����ǹر�״̬,�޷�����!~\n");
		goto __EXIT;
	}
	//��������
	StartService(hService, NULL, NULL);
__EXIT:
	if (NULL != hService) CloseServiceHandle(hService);
	if (NULL != hSCM) 	CloseServiceHandle(hSCM);
}

//�رշ���
static void CloseSrv()
{

	char pszServiceName[MAX_PATH] = { 0 };
	SC_HANDLE hSCM = NULL;
	SC_HANDLE hService = NULL;
	DWORD dwSize = 0;
	SERVICE_STATUS serviceStatus = { 0 };

	printf("������رշ������֣�");
	scanf_s("%s", pszServiceName, _countof(pszServiceName));
	fflush(stdin);

	//
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == hSCM)
		goto __EXIT;
	hService = OpenServiceA(
		hSCM,
		pszServiceName,
		SERVICE_ALL_ACCESS
		);
	if (NULL == hService)
	{
		printf("�޷��򿪷���:%s\n", pszServiceName);
		goto __EXIT;
	}

	//��ȡ����ǰ��״̬
	QueryServiceStatus(hService, &serviceStatus);
	if (ERROR_ACCESS_DENIED == GetLastError())
	{
		printf("Ȩ�޲���\n");
		goto __EXIT;
	}

	if (SERVICE_RUNNING != serviceStatus.dwCurrentState)
	{
		printf("�����ǿ���״̬,�޷��ر�!~\n");
		goto __EXIT;
	}
	//�رշ���
	ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);
__EXIT:
	if (NULL != hService) CloseServiceHandle(hService);
	if (NULL != hSCM) 	CloseServiceHandle(hSCM);

}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs"); //֧�����ı��ػ�
	while (true)
	{
		printf("-----------------------------------------------------\n");
		printf("\t1. ��������\n");
		printf("\t2. �򿪷���\n");
		printf("\t3. �رշ���\n");
		printf("\t4. �˳�\n");
		printf("-----------------------------------------------------\n");

		int nChoice;
		printf("���������ѡ��(1~4):");
		scanf_s("%d", &nChoice);
		fflush(stdin);
		if (!(nChoice >= 1 && nChoice <= 4))
		{
			printf("����������������룡");
			system("cls");
			continue;
		}
		switch (nChoice)
		{
		case 1:
			EnumSrv();
			break;
		case 2:
			OpenSrv();
			break;
		case 3:
			CloseSrv();
			break;
		}
		system("pause");
		system("cls");
	}
	return 1;

}
