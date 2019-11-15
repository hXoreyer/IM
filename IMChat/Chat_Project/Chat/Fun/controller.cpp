#include "controller.h"
#include <QDebug>
Controller::Controller(QObject *parent) : QObject(parent)
{
    m_worker = new Worker();
    m_worker->moveToThread(&m_workThread);
    m_serv = new serv_Thread();
    m_serv->moveToThread(&m_servThread);

    connect(this, &Controller::startRunning, m_worker, &Worker::on_recvMessage);
    connect(&m_workThread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(m_worker, &Worker::resultReady, this, [&](const UDP::MSG& msg)
    {
        emit on_newMessage(msg);
    });
    connect(this,&Controller::serv_startRunning,m_serv,&serv_Thread::on_recvMessage);
    connect(&m_servThread,&QThread::finished,m_serv,&QObject::deleteLater);
    connect(m_serv,&serv_Thread::resultReady,this,[&](const UDP::MSG& msg)
    {
        emit on_newMessage(msg);
    });


    m_workThread.start();
    m_servThread.start();
}
Controller::~Controller()
{
    stop();
    m_workThread.quit();
    m_workThread.wait();
    m_servThread.quit();
    m_servThread.wait();
}
void Controller::start()
{
    emit startRunning();
    emit serv_startRunning();
}
void Controller::stop()
{
    m_worker->close(true);
    m_serv->close(true);
}




