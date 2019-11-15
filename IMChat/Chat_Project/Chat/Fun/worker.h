#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMetaType>
#include "Chat/NetWork/udp.h"
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    inline void close(bool close){closed = close;}

signals:
    void resultReady(const UDP::MSG& pack);
public slots:
    void on_recvMessage();
private:
    bool closed = false;

};

#endif // WORKER_H
