#ifndef SERVER_H
#define SERVER_H
#include "../common/epollServer.h"
#include <iostream>
#include <map>
#include <vector>
#include "sql_do.h"
#include "../common/log.h"
using namespace std;


#pragma pack(4)
struct MSG_CONTENT
{
    char user_type;   // a-login    f-friends
    char user_email[20];
    char user_pass[20];
    char user_name[20];
    //friends
    char nick_name[20];
    char friend_email[20];
    char friend_name[20];
    //others
    char login_result;
    uint32_t size;
};
#pragma pack()
class server: public epollServer
{
public:
    server(int port)
        :epollServer(port){}

    virtual void ConnectEventHandler(int client_sock);
    virtual void ReadEventHandler(epoll_data_t * user_data) ; 



    void initSql();
    void readInLoop(int fd, size_t slen);

private:
    map<int,string> fd_pools;
    SQL *s;
};

#endif