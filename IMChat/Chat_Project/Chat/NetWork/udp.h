#ifndef UDP_H
#define UDP_H
#include "Chat/Fun/common.h"

static SOCKET m_socket;
static SOCKADDR_IN servAddr;
static bool closed;

bool sento_message(char * buff,int size);

bool recv_message(char * buff,int size);
bool common(const char * ip,int port);
void close_socket();

#endif // UDP_H
