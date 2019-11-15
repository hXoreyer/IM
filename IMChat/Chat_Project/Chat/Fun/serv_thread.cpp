#include "serv_thread.h"
#include <QDebug>
serv_Thread::serv_Thread(QObject *parent) : QObject(parent)
{
     serv_common();
     qRegisterMetaType<UDP::MSG>("UDP::MSG");
}
void serv_Thread::on_recvMessage()
{
    qDebug()<<"thread 2 running";
    UDP::MSG pack;
    memset(&pack,0,sizeof (pack));
    char recv_msg[sizeof (pack)] = {0};
    while(true)
    {
        if(closed == true)
            break;
        if(serv_recvMessage(recv_msg,sizeof (pack)) == true)
        {
            memcpy(&pack,recv_msg,sizeof (pack));
            qDebug()<<"recv a new mess "<<pack.send_char;
            emit resultReady(pack);
            memset(&pack,0,sizeof (pack));
            memset(recv_msg,0,sizeof (pack));
        }else{
            continue;
        }
        Sleep(0);
     }
}
