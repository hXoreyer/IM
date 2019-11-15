#include "udp.h"
#include <QDebug>

bool common(const char * ip,int port)
{
    WSADATA wsd;
    if(WSAStartup(MAKEWORD(2,2),&wsd) != 0)
    {
        return false;
    }
    m_socket = socket(AF_INET,SOCK_DGRAM,0);
    if(m_socket == INVALID_SOCKET)
        return false;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.S_un.S_addr = inet_addr(ip);
#if 0
    struct timeval tv_out;

    tv_out.tv_sec = 10;
    tv_out.tv_usec = 0;
    setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,reinterpret_cast<char*>(&tv_out),sizeof (tv_out));
#endif
    return true;
}
bool sento_message(char *buff, int size)
{
    socklen_t len = sizeof (servAddr);
    if(sendto(m_socket,buff,size+1,0,reinterpret_cast<struct sockaddr *>(&servAddr),len) == SOCKET_ERROR)
    {
        //printf("sendto failed: %d \n",WSAGetLastError());
        qDebug()<<"sendto error:"<<WSAGetLastError();
        return false;
    }
    return true;
}
bool recv_message(char *buff, int size)
{
    socklen_t len = sizeof (servAddr);
    if (recvfrom(m_socket,buff, size, 0,reinterpret_cast<struct sockaddr *>(&servAddr),&len) == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}
void close_socket()
{
    closesocket(m_socket);
    WSACleanup();
    closed = true;
}
