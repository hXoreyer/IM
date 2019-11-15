#include "epoll_udp.h"
#include <iostream>

int main()
{
    epollUdp *us = new epollUdp(5500);
    us->start();
    us->eventLoop();
}