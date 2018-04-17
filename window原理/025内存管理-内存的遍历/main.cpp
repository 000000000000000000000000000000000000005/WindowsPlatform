#include <windows.h>
#include <vector>
#include <map>

//�ڴ�״̬��(state)
// #define MEM_COMMIT                  0x1000
// #define MEM_RESERVE                 0x2000
// #define MEM_DECOMMIT                0x4000
// #define MEM_RELEASE                 0x8000
// #define MEM_FREE                    0x10000

//�ڴ����ͣ�(type)
// #define MEM_PRIVATE                 0x20000
// #define MEM_MAPPED                  0x40000
// #define MEM_RESET                   0x80000

//�ڴ����ԣ�protect��
// #define PAGE_NOACCESS          0x01     
// #define PAGE_READONLY          0x02     
// #define PAGE_READWRITE         0x04     
// #define PAGE_WRITECOPY         0x08   

typedef struct  
{
	//region ����Ԥ�����ڴ�����
	PVOID lpAllocationBase;
	DWORD dwAllocationProtect;
	//���ڴ�����
	LPVOID lpRegionBase;
	ULONG ulRegionSize;
	DWORD dwState;
	DWORD dwProtect;
	DWORD dwType;
}MemRegionInfo;




void EnumMemoryInfo(HANDLE hProcess, std::map<PVOID, std::vector<MemRegionInfo>> &mapInfoList);

int main(int argc, char* argv[])
{
	std::map<PVOID, std::vector<MemRegionInfo>> mapInfoList;
	EnumMemoryInfo(GetCurrentProcess(), mapInfoList);
	

	for (auto &mapIte : mapInfoList)
	{
		printf("lpAllocationBase:0x%08X\n", mapIte.first);
		for (auto &vecIte : mapIte.second)
		{
			printf("\tlpRegionBase:0x%08X\n", vecIte.lpRegionBase);
			printf("\tulRegionSize:0x%08X\n", vecIte.ulRegionSize);
			printf("\tdwState:0x%08X\n", vecIte.dwState);
			printf("\tdwProtect:0x%08X\n", vecIte.dwProtect);
			printf("\tdwType:0x%08X\n", vecIte.dwType);
			printf("\n");
		}

	}
	return 0;
} 

void EnumMemoryInfo(HANDLE hProcess, std::map<PVOID, std::vector<MemRegionInfo>> &mapInfoList)
{
	MEMORY_BASIC_INFORMATION mbi;
	LPVOID lpStartAddress = (LPVOID)0;
	BOOL bQureRet = FALSE;

	while (true)
	{
		ZeroMemory(&mbi, sizeof(mbi));
		bQureRet = VirtualQueryEx(hProcess, lpStartAddress, &mbi, sizeof(mbi));
		if (FALSE == bQureRet) break;
		//
		MemRegionInfo reginInfo = { 0 };
		reginInfo.lpAllocationBase = mbi.AllocationBase;
		reginInfo.dwAllocationProtect = mbi.AllocationProtect;
		reginInfo.lpRegionBase = mbi.BaseAddress;
		reginInfo.ulRegionSize = mbi.RegionSize;
		reginInfo.dwState = mbi.State;
		reginInfo.dwProtect = mbi.Protect;
		reginInfo.dwType = mbi.Type;

		if (reginInfo.dwState != MEM_FREE)
		{
			if (mapInfoList.find(mbi.AllocationBase) != mapInfoList.end())
			{
				std::vector<MemRegionInfo> vecRegion = mapInfoList[mbi.AllocationBase];
				vecRegion.push_back(reginInfo);
				mapInfoList[mbi.AllocationBase] = vecRegion;
			}
			else
			{
				std::vector<MemRegionInfo> vecRegion;
				vecRegion.push_back(reginInfo);
				mapInfoList[mbi.AllocationBase] = vecRegion;
			}
		}

		// ������һ�������ڴ�.
		lpStartAddress = (LPVOID)((ULONG_PTR)lpStartAddress + mbi.RegionSize);
	}
}