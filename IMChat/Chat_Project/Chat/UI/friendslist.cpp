#include "friendslist.h"

FriendsList::FriendsList()
{

}

FriendsList::FriendsList(const QPixmap& head_img, const QString& nick_name, const QString& last_msg,const QString& last_time)
    :head_img(head_img),nick_name(nick_name),last_msg(last_msg),last_time(last_time)
{

    if(this->last_msg.size() > 8)
    {
        this->last_msg.resize(11);
        this->last_msg[8]='.';
        this->last_msg[9]='.';
        this->last_msg[10]='.';
    }

    ItemWidget = new QWidget;
    ItemWidget->setLayout(getLayout());
}

QLayout* FriendsList::getLayout()
{
    QHBoxLayout* mainlayout = new QHBoxLayout;
    headimg = new QLabel;
    headimg->setPixmap(head_img.scaled(50,50));
    mainlayout->addWidget(headimg);

    QVBoxLayout* nick_msg = new QVBoxLayout;

    nickname = new QLabel;
    nickname->setText(nick_name);
    nickname->setObjectName("nick_name");
    nickname->setFont(QFont("Consolas",11));

    lastmsg = new QLabel;
    lastmsg->setText(last_msg);
    lastmsg->setFont(QFont("Consolas",9));
    lastmsg->setStyleSheet("color:#5f5f5f");

    nick_msg->addWidget(nickname);
    nick_msg->addWidget(lastmsg);

    QVBoxLayout *time = new QVBoxLayout;
    lasttime = new QLabel;
    lasttime->setText(last_time);
    lasttime->setFont(QFont("MicrosoftYaHei",9));
    lasttime->setStyleSheet("color:#5f5f5f");

    time->addWidget(lasttime,0,Qt::AlignRight|Qt::AlignTop);

    mainlayout->addLayout(nick_msg);
    mainlayout->addLayout(time);

    return mainlayout;
}

QWidget* FriendsList::getWidget()
{
    return ItemWidget;
}
