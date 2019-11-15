#ifndef EPOLL_UDP
#define EPOLL_UDP
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#pragma pack(4)

enum MSG_TYPE
{
    LOGIN_,
    CHAR_,
    FILE_,
    IMG_,
    CHAT_
};

struct MSG_CONTENT
{
    MSG_TYPE TYPE;
    char send_char[1024];
    char recv_user[20];
    char send_user[20];
    sockaddr_in addr;
};
#pragma pack()

class epollUdp
{
private:
    int port;
    int listenfd;
    int epollfd;
    std::map<std::string,struct sockaddr_in> user_pools;
public:
    epollUdp(int port_)
        :port(port_),listenfd(-1),epollfd(-1){}
    
    virtual ~epollUdp()
    {
        if(listenfd)
        {
            close(listenfd);
        }
    }


    void start();
    void eventLoop();

    void ConnectEventHandler(int client_sock);
    void SendEventHandler(const char* send_user, const char* msg, size_t size); 

protected:
    bool eventAdd(int fd, int events)
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = events;

        if(epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event) < 0)
        {
            return false;
        }
        return true;
    }

    bool eventDel(int fd)
    {
        if(epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,NULL) < 0)
        {
            return false;
        }
        return true;
    }

    bool eventMod(int fd, int events)
    {
        struct epoll_event event;
        event.events = events;
        event.data.fd = fd;
        if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event) < 0)
        {
            return false;
        }
        return true;
    }

    void setNoBlock(int sfd);
};

#endif