#include "epollServer.h"
#include "log.h"

void epollServer::start()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
        LOG(ERROR,"create socket erro");
        _exit(-1);
    }
    int opt_ = -1;
    setsockopt(listenfd,SOL_SOCKET, SO_REUSEADDR, &opt_, sizeof(opt_));

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listenfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        LOG(ERROR,"bind socket erro");
        _exit(-1);
    }
    
    if(listen(listenfd,1000) < 0)
    {
        LOG(ERROR,"listen socket error");
        _exit(-1);
    }

    epollfd = epoll_create(1000);
    if(epollfd < 0)
    {
        LOG(ERROR,"epoll create erro");
        _exit(-1);
    }
    if(!eventAdd(listenfd,EPOLLIN))
    {
        LOG(ERROR,"listenfd add erro");
        _exit(-1);
    }

    LOG(INFO,"server start");

}

void epollServer::eventLoop()
{
    const int event_max = 1000;
    struct epoll_event events[event_max];
    for(;;)
    {
        int event_num = epoll_wait(epollfd,events,event_max, -1);

        if(event_num < 0)
        {
            LOG(WARNING,"epoll wait erro");
        }

        for(int i = 0; i < event_num; ++i)
        {
            if(events[i].data.fd == listenfd)
            {
                struct sockaddr_in client_addr;
                socklen_t len = sizeof(client_addr);

                int client_sock = accept(listenfd,(struct sockaddr*)&client_addr,&len);
                if(client_sock < 0)
                {
                    LOG(WARNING,"accept error");
                }
                else
                {
                    char acp[30];
                    sprintf(acp,"new accept: %s",inet_ntoa(client_addr.sin_addr));
                    LOG(INFO,acp);
                    ConnectEventHandler(client_sock);
                }
                
            }
            else if(events[i].events & EPOLLIN)
            {
                ReadEventHandler(&events[i].data);
            }
            else
            {
                LOG(WARNING,"events error");
            }
            
        }
    }
}

void epollServer::setNoBlock(int sfd)
{
    int flags, s;
    flags = fcntl(sfd, F_GETFL, 0);
    if(flags == -1){
        LOG(ERROR, "setnoblock error");
    }

    flags |= O_NONBLOCK;
    if(fcntl(sfd, F_SETFL, flags)){
        LOG(ERROR, "setnoblock error");
    }
}