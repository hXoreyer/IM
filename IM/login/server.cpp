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
        memset(recv_msg,0,1024);
        memset(&msg,0,sizeof(msg));
        int rlen = recv(fd,recv_msg,sizeof(msg),0);
        if(rlen == 0)
        {
            shutdown(fd,SHUT_RDWR);
            fd_pools.erase(fd_pools.find(fd));
            LOG(INFO,"a socket close");
            return;
        }
        memcpy(&msg,recv_msg,sizeof(msg));
        if(msg.user_type == 'a')
        {
            string user_email = msg.user_email;
            string user_pass = msg.user_pass;
            cout<<msg.user_email<<endl;
            cout<<msg.user_pass<<endl;
            
            int flag = login(s,user_email,user_pass);
            
            if(flag == 0)
            {
                msg.login_result = 'c';
            }else if(flag == 1)
            {
               msg.login_result = 'a';
            }else if(flag == 2)
            {
                msg.login_result = 'b';
            }else
            {
                msg.login_result = 'd';
            }
            memset(recv_msg,0,1024);
            memcpy(recv_msg,&msg,sizeof(msg));
            send(fd,recv_msg,sizeof(msg),0);

            vector<map<string,string> > ret;
            if(firnds_list(s,msg.user_email,ret))
            {
                uint32_t size = ret.size();
                for(auto res : ret)
                {
                    struct MSG_CONTENT msgg;
                    memset(&msgg,0,sizeof(msgg));
                    msgg.user_type = 'f';
                    msgg.size = size;
                    strcpy(msgg.friend_email,res["friend_email"].c_str());
                    strcpy(msgg.nick_name,res["friend_remark"].c_str());
                    strcpy(msgg.friend_name,res["friend_remark"].c_str());
                    memset(recv_msg,0,1024);
                    memcpy(recv_msg,&msgg,sizeof(msgg));
                    if(send(fd,recv_msg,sizeof(msgg),0))
                        cout<<"send suc"<<endl;  
                    size--;
                }
                struct MSG_CONTENT msgg;
                memset(&msgg,0,sizeof(msgg));
                msgg.user_type = 'e';
                memset(recv_msg,0,1024);
                memcpy(recv_msg,&msgg,sizeof(msgg));
                send(fd,recv_msg,sizeof(msgg),0); 
                cout<<"send end suc"<<endl; 
            }
        }         

        /*
        shutdown(fd,SHUT_RDWR);
        fd_pools.erase(fd_pools.find(fd));   
        */   
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
        LOG(WARNING,"mysql init error");
    else
    {
         LOG(INFO,"mysql init success");
    }
    
}