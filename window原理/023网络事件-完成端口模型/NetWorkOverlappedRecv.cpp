#include "NetWorkOverlappedRecv.h"
#pragma comment(lib,"ws2_32.lib")


NetWorkOverlappedRecv::NetWorkOverlappedRecv( )
    :m_hSocket( ) ,
    m_sockAddress( ) ,
    m_netWorkEvent( e_recv ) // �������ݵ���·�¼�
{
    OVERLAPPED::hEvent = NULL;
    m_buff.buf = NULL;
}


NetWorkOverlappedRecv::~NetWorkOverlappedRecv( )
{
    if( m_buff.buf != NULL ) { // �ͷŻ�����
        delete[ ] m_buff.buf;
    }
    if( m_hSocket != NULL ) { // �ر��׽���
        closesocket( m_hSocket );
    }
}
