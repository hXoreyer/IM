#include "epoll_udp.h"
#include "../common/log.h"

void epollUdp::start()
{
    listenfd = socket(AF_INET,SOCK_DGRAM,0);
    if(listenfd < 0)
    {
        LOG(ERROR,"create udp socket error");
        _exit(-1);
    }
    int _opt = -1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&_opt,sizeof(_opt));
    setNoBlock(listenfd);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listenfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        LOG(ERROR,"bind udp socket error");
        _exit(-1);
    }

    #if 0
    if(listen(listenfd,1000) < 0)
    {
        LOG(ERROR,"listen udp socket error");
        _exit(-1);
    }
    #endif

    epollfd = epoll_create(1000);
    if(epollfd < 0)
    {
        LOG(ERROR,"epoll create error");
        _exit(-1);
    }

    if(!eventAdd(listenfd,EPOLLIN))
    {
        LOG(ERROR,"listenfd add error");
    }

    LOG(INFO,"udp server start");
}

void epollUdp::eventLoop()
{
    const int event_max = 10000;
    epoll_event events[event_max];
    for(;;)
    {
        int event_num = epoll_wait(epollfd,events,event_max,-1);
        if(event_num < 0)
        {
            LOG(WARNING,"epoll wait error");
        }
        for(int i = 0; i < event_max; ++i)
        {
            if(events[i].data.fd == listenfd)
            {
                ConnectEventHandler(events[i].data.fd);               
            }
        }
    }
}


void epollUdp::setNoBlock(int sfd)
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

void epollUdp::ConnectEventHandler(int client_sock)
{
    MSG_CONTENT msg;
    char recv[sizeof(msg)];
    memset(recv,0,sizeof(msg));
    memset(&msg,0,sizeof(msg));
    sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int ret = recvfrom(client_sock,recv,sizeof(msg),0,reinterpret_cast<sockaddr*>(&client_addr),&len);
    memcpy(&msg,recv,sizeof(msg));
    if(ret > 0)
    {
        if(msg.TYPE == LOGIN_)
        {
            user_pools[msg.send_user] = client_addr;
            /*如果某用户上线  将离线消息发送出来*/
            std::string m = "a client connect, now " + std::to_string(user_pools.size()) + " client(s) on line\n";
            for(auto i = user_pools.begin(); i != user_pools.end(); ++i)
            {
                m += i->first;
                m += " : ";
                m += inet_ntoa(i->second.sin_addr);
                m += "\n";
            }
            LOG(INFO,m);
            return;
        }else if(msg.TYPE == CHAT_)
        {
            std::string m = "from:";
            m += msg.send_user;
            m += " chat to: ";
            m += msg.recv_user;
            LOG(INFO,m.c_str());
            char minfo[sizeof(MSG_CONTENT)];
            /*
            memcpy(&msg.addr,&user_pools[msg.recv_user],sizeof(sockaddr_in));
            memset(minfo,0,sizeof(MSG_CONTENT));
            memcpy(minfo,&msg,sizeof(MSG_CONTENT));
            std::cout<<inet_ntoa(msg.addr.sin_addr)<<std::endl;
            SendEventHandler(msg.send_user,minfo,sizeof(MSG_CONTENT));
            */
            memcpy(&msg.addr,&user_pools[msg.recv_user],sizeof(sockaddr_in));
            memset(minfo,0,sizeof(MSG_CONTENT));
            memcpy(minfo,&msg,sizeof(MSG_CONTENT));
            std::cout<<inet_ntoa(msg.addr.sin_addr)<<std::endl;
            SendEventHandler(msg.send_user,minfo,sizeof(MSG_CONTENT));
            
        }
    }else
    {
        std::cout<<"recv error"<<std::endl;
    }   
}

void epollUdp::SendEventHandler(const char* send_user, const char* msg, size_t size)
{
    socklen_t len = sizeof(sockaddr);
    int ret = sendto(listenfd,msg,size,0,reinterpret_cast<sockaddr*>(&user_pools[send_user]),len);
    if(ret > 0)
    {
        std::string s = "send suc";
        s += "to :";
        s += send_user;
        LOG(INFO,s);
    }else
    {
        LOG(WARNING,"send failed");
    }
}
