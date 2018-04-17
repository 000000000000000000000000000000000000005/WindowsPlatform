#include <windows.h>
#include <winternl.h>
#include <stdio.h>
#pragma comment(lib,"ntdll.lib")

// ����������Ϣ�ṹ��
typedef struct _OBJECT_TYPE_INFORMATION {
	UNICODE_STRING TypeName; // ������
	ULONG TotalNumberOfHanders;
	ULONG TotalNumberOfObjects;
}OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

// ����������Ϣ����
typedef struct _OBJECT_ALL_INFORMATION {
	ULONG NumberOfObjectsTypes; // ����Ԫ�ظ���
	OBJECT_TYPE_INFORMATION ObjectTypeInfo[1];
}OBJECT_ALL_INFORMATION, *POBJECT_ALL_INFORMATION;


bool NQO__NtQueryObject()
{
	// 1. ��ȡ����ѯ��Ϣ��С
	ULONG uSize = 0;
	NtQueryObject(NULL,
		(OBJECT_INFORMATION_CLASS)0x03,
		&uSize,
		sizeof(uSize),
		&uSize);

	// 2. ��ȡ������Ϣ
	POBJECT_ALL_INFORMATION pObjectAllInfo =
		(POBJECT_ALL_INFORMATION)new BYTE[uSize];

	NtQueryObject(NULL,
		(OBJECT_INFORMATION_CLASS)0x03,
		pObjectAllInfo,
		uSize,
		&uSize);


	// 3. ѭ�����������������Ϣ
	POBJECT_TYPE_INFORMATION pObjType = pObjectAllInfo->ObjectTypeInfo;

	for (ULONG i = 0; i < pObjectAllInfo->NumberOfObjectsTypes; i++)
	{
		wprintf(L"%s\n", pObjType->TypeName.Buffer);

		// 3.1 �鿴�˶���������Ƿ�ΪDebugObject������Ҫ�ж϶��������������0��˵���е��Զ���
		if (wcscmp(L"DebugObject", pObjType->TypeName.Buffer) == 0)
		{
			return pObjType->TotalNumberOfObjects > 0;
		}



		// 3.2 ��ȡ������ռ�ÿռ�Ĵ�С�����ǵ��˽ṹ��������⣩
		ULONG uNameLength = pObjType->TypeName.Length;
		ULONG uDataLength = uNameLength - uNameLength % sizeof(ULONG)+sizeof(ULONG);


		// 3.3 ָ����һ��������Ϣ
		pObjType = (POBJECT_TYPE_INFORMATION)pObjType->TypeName.Buffer;
		pObjType = (POBJECT_TYPE_INFORMATION)((PBYTE)pObjType + uDataLength);

	}


	delete[] pObjectAllInfo;
	return false;
}

//
int main(int argc, char* argv[])
{
	bool bDebug = NQO__NtQueryObject();
	if (bDebug)
	{
		MessageBoxA(NULL, "���ڱ�����", "����", 0);
	}
	else
	{
		MessageBoxA(NULL, "���ںܰ�ȫ", "��ϲ", 0);
	}

	return 0;
}

