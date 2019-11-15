#include "worker.h"
#include <QDebug>
Worker::Worker(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<UDP::MSG>("UDP::MSG");
}
void Worker::on_recvMessage()
{
    qDebug()<<"thread 1 running";
    UDP::MSG m_msg;
    memset(&m_msg,0,sizeof(m_msg));
    char recv_msg[sizeof (m_msg)] = {0};
    while (true)
    {
        if(closed == true)
            break;
        bool flag =  recv_message(recv_msg,sizeof (m_msg));
        if(flag == true)
        {
            qDebug()<<"recv a new mess from client_thread";
            memcpy(&m_msg,recv_msg,sizeof(m_msg));
            emit resultReady(m_msg);
            memset(&m_msg,0,sizeof (m_msg));
            memset(recv_msg,0,sizeof (m_msg));
        }else{
            continue;
        }
        Sleep(0);
        /*
        Sleep(10000);
        UDP::MSG m_msg;
        memset(&m_msg,0,sizeof(m_msg));
        QString recv_user = "1724236802@qq.com";
        QString send_user = "xiazeshuang@hotmail.com";
        QString send_char = "你好呀，我是新消息哟";
        strcpy(m_msg.recv_user,recv_user.toUtf8().data());
        strcpy(m_msg.send_user,send_user.toUtf8().data());
        strcpy(m_msg.send_char,send_char.toUtf8().data());
        char recv_msg[sizeof (m_msg)] = {0};
        memcpy(recv_msg,&m_msg,sizeof (m_msg));
        emit resultReady(m_msg);
        qDebug()<<"send a new mess due to thread";
        */
    }
}
