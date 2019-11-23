#include "server.h"

void server::ConnectEventHandler(int client_sock)
{
    fd_pools[client_sock] = "";
    setNoBlock(client_sock);
    eventAdd(client_sock,EPOLLIN);
}

void server::ReadEventHandler(epoll_data *user_data)
{
    int fd = user_data->fd;
    if(fd_pools.find(user_data->fd) != fd_pools.end())
    {
        struct MSG_CONTENT msg;
        //readInLoop(fd,1024);
        char recv_msg[1024];
        int rlen = recv(fd,recv_msg,sizeof(msg),0);
        memcpy(&msg,recv_msg,sizeof(msg));
        string user_email = msg.user_email;
        string user_pass = msg.user_pass;
        cout<<msg.user_email<<endl;
        cout<<msg.user_pass<<endl;
        char ret[1024];
        
        int flag = login(s,user_email,user_pass);
        if(flag == 0)
        {
            strcpy(ret,"not regist");
        }else if(flag == 1)
        {
            strcpy(ret,"login on");
        }else if(flag == 2)
        {
            strcpy(ret,"password error");
        }else
        {
            strcpy(ret,"others");
        }
        
        send(fd,ret,strlen(ret),0);
        shutdown(fd,SHUT_RDWR);
        fd_pools.erase(fd_pools.find(fd));      
    }
}

void server::readInLoop(int fd, size_t slen)
{
        char recv_msg[1024];
        int rlen = recv(fd,recv_msg,rlen,0);
        slen -= rlen;
        fd_pools[fd].append(recv_msg);

}

void server::initSql()
{
    s = new SQL();
    if(!s->init("localhost","root","199836Keing..","IM"))
        cout<<"mysql init error"<<endl;
    else
    {
        cout<<"mysql init suc"<<endl;
    }
    
}