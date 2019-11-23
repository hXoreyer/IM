#ifndef SERVER_H
#define SERVER_H
#include "epollServer.h"
#include <iostream>
#include <map>
#include <vector>
#include "sql_do.h"
using namespace std;


#pragma pack(4)
struct MSG_CONTENT
{
    char user_type;
    char user_email[20];
    char user_pass[20];
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