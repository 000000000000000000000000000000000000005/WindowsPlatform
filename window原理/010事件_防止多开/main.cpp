#include <windows.h>
#include <tchar.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	HANDLE hEvent = NULL;
	hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, _T("010�¼�_��ֹ�࿪_���Ա�SetEvent�ƽ�"));
	//
	if (NULL != hEvent)
	{
		printf("�����Ѿ���һ��ʵ����\n");
		goto __EXIT_END;
	}
	hEvent = CreateEvent(NULL, FALSE, TRUE, _T("010�¼�_��ֹ�࿪_���Ա�SetEvent�ƽ�"));
	//
	printf("����ִ����\n");
	while (true);

__EXIT_END:
	system("pause");
	return 0;
}