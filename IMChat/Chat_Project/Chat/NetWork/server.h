#ifndef SERVER_H
#define SERVER_H
#include "Chat/Fun/common.h"
static SOCKET  serv_socket;
static sockaddr_in serv_addr;
static bool serv_closed;
void serv_common();
bool serv_recvMessage(char * buff,int size);

void serv_close();
#endif // SERVER_H
