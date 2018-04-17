#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>

typedef enum NetWorkEvent
{
    e_accetp = 0 ,
    e_recv ,
    e_send
};


class NetWorkOverlappedRecv :public OVERLAPPED
{
public:
    NetWorkOverlappedRecv( );

    ~NetWorkOverlappedRecv( );

public:
    WSABUF          m_buff; // ���ڱ�����յ�������
    NetWorkEvent    m_netWorkEvent; // �����¼�ö��ֵ

    SOCKET          m_hSocket;// ����IO������׽���
    sockaddr_in     m_sockAddress;// �׽��ֵĵ�ַ
};
