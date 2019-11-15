#ifndef PERCARD_H
#define PERCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QBitmap>
#include <QPainter>
#include <QLineEdit>
#include <map>
#include "Chat/NetWork/Socket.h"
#include "Chat/NetWork/udp.h"
class PerCard : public QWidget
{
    Q_OBJECT
public:
    //explicit PerCard(QWidget *parent = nullptr);
    PerCard(const QPixmap& heading,const QString& self_email, const std::map<QString,QString>& perMsg,QWidget *parent = nullptr);
    void perCard_ui();

private:
    QLabel * perName;
    QPushButton * perHead;
    QLabel * perRemark;
    QLineEdit* perRemarkCot;
    QLabel* perEmail;
    QLabel * perEmailCot;
    QPushButton * sendBtn;
    QWidget * wid;
    QPixmap m_head;
    std::map<QString,QString> map_perInfo;
    QString m_self_email;


signals:
    void sendMess_onClicked();

public slots:
};

#endif // PERCARD_H
