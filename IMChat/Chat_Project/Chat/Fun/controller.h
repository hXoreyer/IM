#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "worker.h"
#include "serv_thread.h"
#include <QThread>
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void start();
    void stop();

signals:
    void startRunning();
    void serv_startRunning();
    void on_newMessage(const UDP::MSG& msg);
private:
    QThread m_workThread;
    Worker  * m_worker;

    QThread m_servThread;
    serv_Thread * m_serv;
};

#endif // CONTROLLER_H
