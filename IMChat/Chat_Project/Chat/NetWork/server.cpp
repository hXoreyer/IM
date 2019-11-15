#include "server.h"
#include <QDebug>
void serv_common()
{
    WSADATA m_wsaData;
    if(WSAStartup(MAKEWORD(2,2),&m_wsaData)!=0)
    {
        return;
    }

    serv_socket=socket(AF_INET,SOCK_DGRAM,0);
    if(serv_socket == INVALID_SOCKET)
    {
        return;
    }
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(5501);
    serv_addr.sin_addr.S_un.S_addr= htonl(INADDR_ANY);

    if(bind(serv_socket,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == SOCKET_ERROR)
    {
        qDebug()<<"bind error";
        closesocket(serv_socket);
        WSACleanup();
        return;
    }else{
        qDebug()<<"bind sus";
    }
#if 0
    struct timeval tv_out;
    tv_out.tv_sec = 10;
    tv_out.tv_usec = 0;
    setsockopt(serv_socket,SOL_SOCKET,SO_RCVTIMEO,reinterpret_cast<char*>(&tv_out),sizeof (tv_out));
#endif
}
bool serv_recvMessage(char * buff,int size)
{
    int len = sizeof (serv_addr);
    if(recvfrom(serv_socket,buff,size+1,0,(struct sockaddr *)&serv_addr,&len) == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}
void serv_close()
{
    closesocket(serv_socket);
    WSACleanup();
    serv_closed = true;
}
