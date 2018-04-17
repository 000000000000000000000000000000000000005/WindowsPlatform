#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "IPHLPAPI.lib")
#include <iphlpapi.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
/*
ʹ�� GetIfTable2(), GetIfEntry2() �Ⱥ��������ͷ�ļ� iphlpapi.h �� iphlpapi.lib
iphlpapi.h ��Ҫ����ͷ�ļ� ws2tcpip.h

ע�� ws2tcpip.h �� windows.h �İ���˳��
���Ȱ��� ws2tcpip.h �ڰ��� windows.h ������������
*/

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
using namespace std;

ULONG64 GetSpeedDifference(ULONG64 num1, ULONG64 num2) //���ټ��㺯��
{
	//����InOctets�ֶ���32bit����������0xFFFFFFFF����ͷ��0������Ҫע��������㡣
	if (num1 >= num2)
	{
		return num1 - num2;
	}
	else
	{
		return (0xFFFFFFFF - num2) + num1;
	}
}

/*
����ʹ�� GetIfTable2() ��ȡ���е�����������Ϣ, �������� != ����, һ��Ӳ���������ж����������
GetIfTable2() �������һ�� �����������ӵ����� PMIB_IF_TABLE2 , �ĵ�һ���ֶα��������������Ӹ���,�ڶ����ֶα���������������,����ʹ�� PMIB_IF_ROW2 �ṹ�屣��ÿ������������Ϣ,
GetIfTable2() ��������������ӵ� InterfaceLuid, InterfaceIndex, InterfaceAndOperStatusFlags, OperStatus ���ֶ�
ͨ�� InterfaceAndOperStatusFlags, OperStatus �ж����������Ƿ�Ϊ����ʹ�õ�����, ��ͨ�� InterfaceLuid, InterfaceIndex, ��Ϣ���� GetIfEntry2() ������ȡ�����ӵľ�����ϸ��Ϣ
GetIfEntry2() �����ȡ�����ӵ��ۼ������������ۼ��ϴ�����, ͨ������:
(��һʱ�̸����ӵ� �ۼ�����/�ϴ��� - ��ǰʱ�� �ۼ�����/�ϴ���) / ʱ�� = �ɵó�˲ʱ ����/�ϴ�����
*/
int main(void)
{
	PMIB_IF_TABLE2 m_pIfTable;
	PMIB_IF_ROW2 m_pIfRow;
	ULONG64 outSpeed, inSpeed, NowInOctets, NowOutOctets;
	ULONG64 PreInOctets = 0, PreOutOctets = 0;

	while (true)
	{
		// ��ȡ�����б�
		if (GetIfTable2(&m_pIfTable) == NO_ERROR)
			/*
			GetIfTable2() �����������һ�� PMIB_IF_TABLE2 �ṹ��,����ɹ����᷵�� NO_ERROR
			GetIfTable2() �������Ľṹ�彫��ʹ�öѿռ�,ʹ�������Ҫʹ�� FreeMibTable() �ֶ��ͷŽṹ��


			PMIB_IF_TABLE2 �洢���Ǳ�����������������Ϣ:

			typedef struct _MIB_IF_TABLE2
			{
			ULONG NumEntries; //�������ڵ�����������������
			MIB_IF_ROW2 Table[ANY_SIZE]; //һ��PMIB_IF_ROW2�ṹ������,PMIB_IF_ROW2�ṹ�������洢�������Ӿ�����Ϣ
			} MIB_IF_TABLE2, *PMIB_IF_TABLE2;


			MIB_IF_ROW2 �洢�����������ӵľ�����Ϣ:

			typedef struct _MIB_IF_ROW2
			{
			//
			// Key structure.  Sorted by preference.
			//
			NET_LUID InterfaceLuid;     //����ӿڵı���Ψһ��ʶ��(LUID)
			NET_IFINDEX InterfaceIndex;     //��ʶ����ӿڵ�����,�������������������,����������ʱ������ֵ���ܻ����

			//
			// Read-Only fields.
			//
			GUID InterfaceGuid;
			WCHAR Alias[IF_MAX_STRING_SIZE + 1];
			WCHAR Description[IF_MAX_STRING_SIZE + 1];
			ULONG PhysicalAddressLength;
			UCHAR PhysicalAddress[IF_MAX_PHYS_ADDRESS_LENGTH];
			UCHAR PermanentPhysicalAddress[IF_MAX_PHYS_ADDRESS_LENGTH];

			ULONG Mtu;
			IFTYPE Type;                // Interface Type.
			TUNNEL_TYPE TunnelType;     // Tunnel Type, if Type = IF_TUNNEL.
			NDIS_MEDIUM MediaType;
			NDIS_PHYSICAL_MEDIUM PhysicalMediumType;
			NET_IF_ACCESS_TYPE AccessType;
			NET_IF_DIRECTION_TYPE DirectionType;

			struct
			{
			BOOLEAN HardwareInterface : 1;      //����������Ӳ���ӿ�,����Ϊ������������
			BOOLEAN FilterInterface : 1;
			BOOLEAN ConnectorPresent : 1;
			BOOLEAN NotAuthenticated : 1;
			BOOLEAN NotMediaConnected : 1;
			BOOLEAN Paused : 1;
			BOOLEAN LowPower : 1;
			BOOLEAN EndPointInterface : 1;
			} InterfaceAndOperStatusFlags;      //�����ӵ�һЩ��־λ

			IF_OPER_STATUS OperStatus;      //���ӵľ���״̬��Ϣ,���ֶ�Ϊö������,ö��ֵ����

			//  typedef enum
			//  {
			//       IfOperStatusUp = 1,     //��ʾ�������ѿ���
			//       IfOperStatusDown,       //��ʾ�����ӹر�
			//       IfOperStatusTesting,
			//       IfOperStatusUnknown,
			//       IfOperStatusDormant,
			//       IfOperStatusNotPresent,
			//       IfOperStatusLowerLayerDown
			//  } IF_OPER_STATUS;


			NET_IF_ADMIN_STATUS AdminStatus;
			NET_IF_MEDIA_CONNECT_STATE MediaConnectState;
			NET_IF_NETWORK_GUID NetworkGuid;
			NET_IF_CONNECTION_TYPE ConnectionType;

			//
			// Statistics.
			//
			ULONG64 TransmitLinkSpeed;
			ULONG64 ReceiveLinkSpeed;

			ULONG64 InOctets;       //������ӿڵ��ۼ�������
			ULONG64 InUcastPkts;
			ULONG64 InNUcastPkts;
			ULONG64 InDiscards;
			ULONG64 InErrors;
			ULONG64 InUnknownProtos;
			ULONG64 InUcastOctets;
			ULONG64 InMulticastOctets;
			ULONG64 InBroadcastOctets;
			ULONG64 OutOctets;          //������ӿڵ��ۼƷ�����
			ULONG64 OutUcastPkts;
			ULONG64 OutNUcastPkts;
			ULONG64 OutDiscards;
			ULONG64 OutErrors;
			ULONG64 OutUcastOctets;
			ULONG64 OutMulticastOctets;
			ULONG64 OutBroadcastOctets;
			ULONG64 OutQLen;
			} MIB_IF_ROW2, *PMIB_IF_ROW2;
			*/
		{
			for (int i = 0; i < (int)m_pIfTable->NumEntries; i++)
				/*
				�������е���������,������Ϊ MIB_IF_TABLE2 �е� NumEntries
				*/
			{
				m_pIfRow = &m_pIfTable->Table[i];   //��� MIB_IF_TABLE2 �е� Table �����еĵ� i ��Ԫ��

				if (m_pIfRow->InterfaceAndOperStatusFlags.HardwareInterface != 1)
				{
					/*
					������ӽṹ�� PMIB_IF_ROW2 �е� InterfaceAndOperStatusFlags �ֶε� HardwareInterface ��־λ
					HardwareInterface Ϊ1���ʾ������������Ӳ������,����������,
					*/
					continue;   //��Ӳ�����������,������������ѭ�������һ����
				}

				if ((GetIfEntry2(m_pIfRow)) != NO_ERROR)
				{
					/*
					GetIfEntry2() ������ȡ�����ӵľ�����ϸ��Ϣ,�β� MIB_IF_ROW2 �е� InterfaceLuid �ֶλ� InterfaceIndex ����ʶ��ȡ�ĸ�����,�ɹ���ȡ��Ϣ�󽫻�����β� MIB_IF_ROW2 ���͵Ľṹ�岢���� NO_ERROR
					InterfaceLuid �� InterfaceIndex �ֶ��� GetIfTable2()������д
					*/

					//OutputDebugString(L"GetIfEntry2����\n");
					continue;   //��ȡʧ������������ѭ��,�����һ����
				}

				if (m_pIfRow->OperStatus != IfOperStatusUp)
				{
					/*
					��� MIB_IF_ROW2  �е� OperStatus �ֶ��Ƿ�Ϊ IfOperStatusUp ,�����ʾ��������������
					OperStatus �ֶ���һ��ö������,���������������
					//  typedef enum
					//  {
					//       IfOperStatusUp = 1,     //��ʾ�������ѿ���
					//       IfOperStatusDown,       //��ʾ�����ӹر�
					//       IfOperStatusTesting,
					//       IfOperStatusUnknown,
					//       IfOperStatusDormant,
					//       IfOperStatusNotPresent,
					//       IfOperStatusLowerLayerDown
					//  } IF_OPER_STATUS;
					*/
					continue;   //�����ӱ����������,δ��������������ѭ�������һ����
				}

				NowInOctets = m_pIfRow->InOctets;   //��ȡ�����ӵ��ۼ�������
				NowOutOctets = m_pIfRow->OutOctets; //��ȡ�����ӵ��ۼ��ϴ���

				inSpeed = GetSpeedDifference(NowInOctets, PreInOctets) / 1024;  //��������
				outSpeed = GetSpeedDifference(NowOutOctets, PreOutOctets) / 1024;   //��������
				/*
				ʹ�� (��һʱ�̸����ӵ� �ۼ�����/�ϴ��� - ��ǰʱ�� �ۼ�����/�ϴ���) / ʱ�� = �ɵó�˲ʱ ����/�ϴ�����
				*/

				if (inSpeed >= 113072)
				{
					inSpeed = 0;
				}
				if (outSpeed >= 113072)
				{
					outSpeed = 0;
				}

				printf("�ϴ��ٶȣ� %03lldKb\t", outSpeed);
				printf("�����ٶȣ� %03lldKb\r", inSpeed);

				PreInOctets = NowInOctets;
				PreOutOctets = NowOutOctets;

				break;
			}
		}

		FreeMibTable(m_pIfTable);
		/*
		GetIfTable2() ���������ѿռ�,ʹ�ý�������ʹ�� FreeMibTable() �����ֶ��ͷŶѿռ�
		*/

		Sleep(1000);
	}
	return 0;
}
