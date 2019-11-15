#ifndef FRIENDSLIST_H
#define FRIENDSLIST_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
class FriendsList
{
public:
    FriendsList();
    FriendsList(const QPixmap& head_img, const QString& nick_name, const QString& last_msg,const QString& last_time);

    QWidget* getWidget();


private:
    QWidget* ItemWidget;
    QLabel *headimg;
    QLabel *nickname;
    QLabel *lastmsg;
    QLabel *lasttime;

    QPixmap head_img;
    QString nick_name;
    QString last_msg;
    QString last_time;

private:
    QLayout* getLayout();

};

#endif // FRIENDSLIST_H
