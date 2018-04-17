#pragma warning(disable:4101 4100 4055 4152 4214)

#include <ntddk.h>

/*
*IDT�Ĵ����ṹ
*IDTR�Ĵ�������48λ����32λ��IDT��Ļ���ַ����16λ��IDT��ĳ��ȣ�Limit)
*IDT��ʾһ��λ�������ڴ��е����Ա�����256�����
*/
typedef struct _IDT_INFO{
	UINT16 uIdtLimit;
	UINT16 uLowIdtBase;
	UINT16 uHighIdBase;
}IDT_INFO, *PIDT_INFO;
/* ----------------ѡ����-----------------------
|   1   |     0    |  �ֽ�
|7654321076543 2 10|  ����
|-------------|-|--|  ռλ
|    INDEX    |T|R |  ����
|             |I|P |
|             | |L |
*Index : ��GDT�����LDT�����������
*TI:Table Indicator ,���ֵΪ0��ʾ����GDT,1��ʾ����LDT
*RPL:������Ȩ������ʲô����Ȩ��ȥ���ʶΡ�
*/
typedef struct _SELECTOR{
	int PRL : 2;
	int TI : 1;
	int Index : 13;
}SELECTOR, *PSELECTOR;
/*----------------------���������ṹ--------------------
|   7    |     6       |     5     |   4    |   3    |   2    |   1    |   0    |  �ֽ�
|76543210|7 6 5 4 3210 |7 65 4 3210|76543210|76543210|76543210|76543210|76543210|  ����
|--------|-|-|-|-|---- |-|--|-|----|--------|--------|--------|--------|--------|  ռλ
|  BASE  |G|D|0|A|LIMIT|P|D |S|TYPE|<------- BASE 23-0 ------>|<-- LIMIT 15-0 ->|  ����
|  31-24 | |/| |V|19-16| |P |
|B| |L|     | |L |

BASE: �λ�ַ������ͼ�е�������(BASE 31-24 �� BSE23-0)���
G��LIMIT�ĵ�λ����λ 0 ��ʾ��λ���ֽڣ�1��ʾ��λ�� 4KB
D/B: ��λΪ 0 ��ʾ����һ�� 16 λ�ĶΣ�1 ��ʾ����һ�� 32 λ��
AVL: ��λ���û�λ�����Ա��û�����ʹ��
LIMIT: �εĽ��ޣ���λ�� G λ��������ֵ�ϣ�������λ������ֵ�����ڶεĳ��ȣ��ֽڣ�- 1��
P: �δ���λ����λΪ 0 ��ʾ�öβ����ڣ�Ϊ 1 ��ʾ���ڡ�
DPL����Ȩ��
S: ��λΪ 1 ��ʾ����һ�����ݶλ��ߴ���Ρ�Ϊ 0 ��ʾ����һ��ϵͳ�Σ���������ţ��ж��ŵȣ�
TYPE: ���� S λ�Ľ�����ٴζԶ����ͽ���ϸ�֡�
*/
typedef struct _GDT{
	INT64 Limit0_15 : 16;
	INT64 base0_23 : 24;
	INT64 TYPE : 4;
	INT64 S : 1;
	INT64 DPL : 2;
	INT64 P : 1;
	INT64 Limit16_19 : 4;
	INT64 AVL : 1;
	INT64 O : 1;
	INT64 D_B : 1;
	INT64 G : 1;
	INT64 Base24_31 : 8;
}GDT, *PGDT;//830089f700000068
/*------------------IDT��----------
|   7    |     6       |     5     |   4    |   3    |   2    |   1    |   0    |  �ֽ�
|76543210|76543210|7 65 43210|76543210 |76543210|76543210|76543210     |76543210|  ����
|-----------------|-|---|----|-------- |-----------------|----------------------|  ռλ
|  uOffsetHigh    |P|DPL|type|reserve_1|    selector     | uOffsetLow       |  ����
type ������������;�ж϶���������0b00101(b����Ķ������������ж��ŵ�������0b0D110,����DΪ����
��ʾ��������16λ�ǣ�0������32λ�ţ�1���������ŵ�������0b0D111.
*0x05 : 32 λ��������
*0x06 :��16λ���ж���
*0x07 :��16λ��������
*0x0E :��32λ���ж���
*0x0F : 32λ��������
*/
typedef struct  _IDT{
	UINT16 uOffsetLow;  //�������͵�ַ����
	UINT16 selector;    //��ѡ����
	UINT8 reserve_1;    //����
	UINT8 type : 5; //�ж�����
	UINT8 DPL : 2;  //��Ȩ��
	UINT8 P : 1;  //��δʹ���жϿ���Ϊ0
	INT16 uOffsetHigh;     //�������ߵ�ַƫ��
}IDT, *PIDT;

#define MAKE_LONG(Low,High) ((UINT32) (((UINT16)(Low))|((UINT32)((UINT16)(High)))<<16) )


VOID DriverUnload(PDRIVER_OBJECT objDriver)
{
	//�����������Ϊ���ò����ľ���
	UNREFERENCED_PARAMETER(objDriver);
	DbgPrint("My Driver is unloading ...\n");
}
NTSTATUS DriverEntry(
	PDRIVER_OBJECT objDriver,
	PUNICODE_STRING strRegPath
	)
{
	UNREFERENCED_PARAMETER(strRegPath);
	objDriver->DriverUnload = DriverUnload;
	DbgPrint("My first Driver\n");
	KdBreakPoint();
	IDT_INFO stcIdtInfo = { 0 };
	PIDT pIdt = NULL;
	_asm sidt stcIdtInfo;

	pIdt = (PIDT)MAKE_LONG(
		stcIdtInfo.uLowIdtBase, stcIdtInfo.uHighIdBase);
	for (UINT32 uCount = 0; uCount <= 256; uCount++)
	{
		//��Ҫ��16�����Ž������⴦������μ��������275ҳ
		//�����̣�TSS��ѡ���ӣ�GDT��TSS�η���
		PIDT  pIndex = &pIdt[uCount];
		UINT32 uAddr = MAKE_LONG(pIndex->uOffsetLow, pIndex->uOffsetHigh);
		DbgPrint("Interrput %d: ISR 0x%08X\n", uCount, uAddr);
	}
	return STATUS_SUCCESS;
}