#ifndef SERV_THREAD_H
#define SERV_THREAD_H
#include <QObject>
#include "Chat/NetWork/server.h"
class serv_Thread : public QObject
{
    Q_OBJECT
public:
    explicit serv_Thread(QObject *parent = nullptr);
    inline void close(bool close){closed = close;}

signals:
    void resultReady(const UDP::MSG& pack);
public slots:
    void on_recvMessage();
private:
    bool closed = false;
};

#endif // SERV_THREAD_H
