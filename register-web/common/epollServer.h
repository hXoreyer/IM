#ifndef EPOLL_SERVER_H
#define EPOLL_SERVER_H
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

class epollServer
{
private:
    int port;
    int listenfd;
    int epollfd;
public:
    epollServer(int port_)
        :port(port_),listenfd(-1),epollfd(-1){}

    virtual ~epollServer()
    {
        if(listenfd)
            close(listenfd);
    }

    void start();
    void eventLoop();

    virtual void ConnectEventHandler(int client_sock) = 0;
    virtual void ReadEventHandler(epoll_data_t * user_data) = 0; 

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