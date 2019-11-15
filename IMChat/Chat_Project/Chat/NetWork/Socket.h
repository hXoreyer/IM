#ifndef Socket_H
#define Socket_H
#include <winsock2.h>
#include <iostream>
#include <vector>
namespace net
{
#pragma pack(4)
    struct MSG{
        char user_type;   // a-login    f-friends
        //self
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
}
class Socket
{
private:
    WSADATA wsaData;
    struct sockaddr_in serverAddr;
    SOCKET m_socket;
    int ret;
public:
    Socket();
    ~Socket();
    bool request_server();
    bool send_message(void * buff,int size);
    bool recv_message(void * buff,int size);
    bool close_socket();
};

#endif // Socket_H
