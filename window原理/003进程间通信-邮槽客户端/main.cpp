#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	// 1. ���ʲ۶���
	HANDLE hFile = CreateFile(
		L"\\\\.\\mailslot\\Sample", // �ʲ�����
		GENERIC_WRITE,      // ��д����
		FILE_SHARE_READ,       // ��������
		NULL,                       // ��ȫ����
		OPEN_EXISTING,      // �򿪷�ʽ
		FILE_ATTRIBUTE_NORMAL,      // ��־λ
		NULL);                     // �ļ�ģ�壨Ĭ�����գ�
	// 2. ��mailslotд��
	DWORD  dwWritten;
	LPSTR  lpMessage = "�ʲ۲�����Ϣ��";
	DWORD  dwMegLen = strlen(lpMessage) + sizeof(CHAR);
	WriteFile(hFile, lpMessage, dwMegLen, &dwWritten, NULL);
	// 3. ����
	printf("�Ѿ����ʲ�д����Ϣ��\n");
	CloseHandle(hFile);
}