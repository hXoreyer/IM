#include "Socket.h"
Socket::Socket()
{
}
Socket::~Socket()
{
    if(!close_socket())
    {
        shutdown(m_socket,SD_BOTH);
        closesocket(m_socket);
    }
}
bool Socket::request_server()
{
    if((ret = WSAStartup(MAKEWORD(2,2),&wsaData)) != 0)
    {
        return false;
    }
    if((m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == SOCKET_ERROR)
    {
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4500);
    serverAddr.sin_addr.S_un.S_addr = inet_addr("**.***.**.***");

    if((::connect(m_socket,reinterpret_cast<SOCKADDR *>(&serverAddr),sizeof (serverAddr))) == SOCKET_ERROR)
    {
        closesocket(m_socket);
        return false;
    }
    return true;
}
bool Socket::send_message(void * buff,int size)
{
     int index = 0;
     while (size != 0)
     {
         if (size > 4096)
         {
             ret = send(m_socket,reinterpret_cast<char *>(buff)+index,4096,0);
         }
         else
         {
             ret = send(m_socket,reinterpret_cast<char *>(buff)+index,size,0);
         }
         if (ret == SOCKET_ERROR || ret == 0) break;
         size -= ret;
         index += ret;
     }
     return size == 0 ? true : false;
}
bool Socket::recv_message(void * buff,int size)
{
    int index = 0;
    while (size != 0)
    {
        ret = recv(m_socket,reinterpret_cast<char *>(buff) + index,size,0);
        if(ret == SOCKET_ERROR || ret == 0)
            break;
        size -= ret;
        index += ret;
    }
    return size == 0 ? true :false;
}
bool Socket::close_socket()
{
    shutdown(m_socket,SD_BOTH);
    if(closesocket(m_socket) != 0)
        return false;
    return true;
}
