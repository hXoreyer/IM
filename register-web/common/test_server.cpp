#include "server.h"
#include <iostream>
using namespace std;

int main()
{
    server *s = new server(4500);
    s->initSql();
    s->start();
    s->eventLoop();
}