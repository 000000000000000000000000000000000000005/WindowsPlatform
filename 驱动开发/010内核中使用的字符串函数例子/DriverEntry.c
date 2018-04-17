#include <Ntifs.h>

/*
���� 	��ʽ˵���� 	����
%c, %lc 	ANSI�ַ� 	char
%C, %wc 	���ַ� 	wchar_t
%d, %i 	ʮ�����з������� 	int
%D 	ʮ����__int64 	__int64
%L 	ʮ�����Ƶ�LARGE_INTEGER 	LARGE_INTEGER
%s, %ls 	NULL��ֹ��ANSI�ַ��� 	char*
%S, %ws 	NULL��ֹ�Ŀ��ַ��� 	wchar_t*
%Z 	ANSI_STRING�ַ��� 	ANSI_STRING
%wZ 	UNICODE_STRING�ַ��� 	UNICODE_STRING
%u 	ʮ���Ƶ�ULONG 	ULONG
%x 	Сд�ַ�ʮ�����Ƶ�ULONG 	ULONG
%X 	��д�ַ�ʮ�����Ƶ�ULONG 	ULONG
%p 	ָ��Pointer 32/64λ
*/
VOID DriverUnload(PDRIVER_OBJECT pDriver);

NTSTATUS DriverEntry(
	PDRIVER_OBJECT pDriver,
	PUNICODE_STRING pPath
	)
{
	pPath;
	pDriver->DriverUnload = DriverUnload;

	DbgBreakPoint();

	//��ʼ���ַ���,��ʽ1
	UNICODE_STRING strTest = RTL_CONSTANT_STRING(L"Hello World");
	KdPrint(("RTL_CONSTANT_STRING:%wZ\n", strTest));

	//�˴������ͷ�
	//RtlFreeUnicodeString(&strTest);

	//��ʼ���ַ���,��ʽ2
	UNICODE_STRING strTest2;
	RtlInitUnicodeString(&strTest2, L"RtlInitUnicodeString");
	KdPrint(("RtlInitUnicodeString:%wZ\n", strTest2));


	//�ַ�������
	UNICODE_STRING strTest3;
	WCHAR dst_buf[256];
	RtlInitEmptyUnicodeString(&strTest3, dst_buf, sizeof(dst_buf));
	RtlCopyUnicodeString(&strTest3, &strTest);
	KdPrint(("RtlCopyUnicodeString:%wZ\n", &strTest3));


	//ճ���ַ���
	RtlAppendUnicodeStringToString(&strTest3, &strTest);
	KdPrint(("RtlAppendUnicodeStringToString :%wZ\n", &strTest3));

	//�ַ����Ƚ�
	LONG lCompareResult = RtlCompareUnicodeString(&strTest2, &strTest3, TRUE);
	KdPrint(("RtlCompareUnicodeString :%d\n", lCompareResult));


	//�ַ���ת��������
	UNICODE_STRING strToInteger = RTL_CONSTANT_STRING(L"9521123");
	ULONG uValue;
	RtlUnicodeStringToInteger(&strToInteger, 0, &uValue);
	KdPrint(("RtlUnicodeStringToInteger:%d\n", uValue));


	//����ת�����ַ���
	UNICODE_STRING strInteger2;
	WCHAR buff[256] = { 0 };
	RtlInitEmptyUnicodeString(&strInteger2, buff, sizeof(buff));
	uValue = 12345678;
	RtlIntegerToUnicodeString(uValue, 10, &strInteger2);
	KdPrint(("RtlIntegerToUnicodeString:%wZ\n", &strInteger2));

	//ת��ansi
	ANSI_STRING ansiString;
	RtlUnicodeStringToAnsiString(&ansiString, &strInteger2, TRUE);
	KdPrint(("RtlUnicodeStringToAnsiString:%Z\n", &ansiString));


	//�ͷ��ַ���
	RtlFreeAnsiString(&ansiString);
	return STATUS_SUCCESS;
}

VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	pDriver;
}