#include <windows.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	// 1. �����ʲ۶���
	HANDLE hSlot = CreateMailslot(
		L"\\\\.\\mailslot\\Sample",    // �ʲ���
		0,         // ��������Ϣ��С 
		MAILSLOT_WAIT_FOREVER,         // �޳�ʱ 
		(LPSECURITY_ATTRIBUTES)NULL);  // ��ȫ����
	// 2. ѭ����ȡ�ʲ���Ϣ
	while (true) {
		// 2.1 ��ȡ�ʲ���Ϣ����
		DWORD dwMsgCount = 0, dwMsgSize = 0;
		GetMailslotInfo(     /* ��ȡ�ʲ���Ϣ */
			hSlot,           // �ʲ۾�� 
			(LPDWORD)NULL,// �������Ϣ����
			&dwMsgSize,      // ��һ����Ϣ�Ĵ�С
			&dwMsgCount,     // ��Ϣ������
			(LPDWORD)NULL);// ��ʱ��
		if (dwMsgSize == MAILSLOT_NO_MESSAGE) {
			Sleep(2000);
			continue;
		}
		// 2.2 ѭ����ȡȫ����Ϣ���п��ܲ�ֻһ����
		while (dwMsgCount) {
			PBYTE lpBuffer;
			lpBuffer = new BYTE[dwMsgSize + 0x10];
			// ��ȡ�ʲ��е���Ϣ
			DWORD dwRet;
			ZeroMemory(lpBuffer, dwMsgSize);
			if (!ReadFile(hSlot, lpBuffer, dwMsgSize, &dwRet, NULL)) {
				printf("ReadFile����ִ��ʧ�ܣ������룺%d.\n", GetLastError());
				delete[] lpBuffer;
				return 0;
			}
			// ��ʾ��Ϣ
			printf("�ʲ۵�����: %s\n", lpBuffer);
			// ����ʣ�����Ϣ��
			GetMailslotInfo(hSlot, (LPDWORD)NULL, &dwMsgSize, &dwMsgCount, nullptr);
			delete[] lpBuffer;
		}
	}
	return 0;


	return 0;
}