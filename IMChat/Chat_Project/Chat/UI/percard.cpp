#include "percard.h"
#include <QDebug>
PerCard::PerCard(const QPixmap& heading,const QString& self_email,const std::map<QString,QString>& perMsg,QWidget * parent)
    :QWidget(parent),m_head(heading),map_perInfo(perMsg),m_self_email(self_email)
{
    perCard_ui();
}
void  PerCard::perCard_ui()
{
    perName = new QLabel;
    perName->setText(map_perInfo["friend_name"]);
    perName->setFont(QFont("Microsoft YaHei",13,QFont::Normal));
    QHBoxLayout * hlay1 = new QHBoxLayout;
    hlay1->addWidget(perName);
    hlay1->addStretch();
    perHead = new QPushButton;
    perHead->setIcon(m_head);
    perHead->setFixedSize(75,75);
    perHead->setIconSize(QSize(75,75));
    hlay1->addWidget(perHead);

    QVBoxLayout * vlay2 = new QVBoxLayout;
    QVBoxLayout * vlay3 = new QVBoxLayout;


    perRemark = new QLabel("备注");
    perRemark->setStyleSheet("QLabel{color:	#BEBEBE}");
    perRemark->setFont(QFont("Consolas",10));
    perRemarkCot = new QLineEdit;
    if(map_perInfo["friend_remark"].isEmpty())
        perRemarkCot->setText(QString("点击添加备注"));
    else
        perRemarkCot->setText(map_perInfo["friend_remark"]);
    perRemarkCot->setStyleSheet("QLineEdit{border-style:none;background-color:#fafafa;}"
                                "QLineEdit:focus{border-bottom:1px solid #87CEFA;border-style:outset}");
    perRemarkCot->setFont(QFont("Microsoft YaHei",11));

    perEmail = new QLabel("邮箱");
    perEmail->setStyleSheet("QLabel{color:#BEBEBE}");
    perEmail->setFont(QFont("Consolas",10));
    perEmailCot = new QLabel(map_perInfo["friend_email"]);
    perEmailCot->setFont(QFont("Consolas",11));

    vlay2->addWidget(perRemark);
    vlay2->addWidget(perEmail);
    vlay3->addWidget(perRemarkCot);
    vlay3->addWidget(perEmailCot);

    QHBoxLayout * hblay = new QHBoxLayout;
    hblay->addLayout(vlay2);
    hblay->addLayout(vlay3);
    hblay->setSpacing(30);

    QHBoxLayout * hlay4 = new QHBoxLayout;
    sendBtn = new QPushButton("发送消息");
    sendBtn->setFont(QFont("Consolas",12));
    sendBtn->setFixedSize(QSize(180,35));
    sendBtn->setStyleSheet("QPushButton{border-radius:3px;background-color:#008B00;border-style:none;color:white}"
                           "QPushButton:hover{background-color:#00CD66;color:white}");
    connect(sendBtn,&QPushButton::clicked,this,[&]()
    {
        /*
        UDP::MSG pack;
        memset(&pack,0,sizeof (pack));
        pack.type = UDP::CHAT;
        strcpy(pack.send_user,m_self_email.toUtf8().data());
        strcpy(pack.recv_user,map_perInfo["friend_email"].toUtf8().data());
        char m_send[sizeof (pack)] = {0};
        memcpy(m_send,&pack,sizeof (pack));
        sento_message(m_send,sizeof (pack));
        */
        emit sendMess_onClicked();
    });

    hlay4->addWidget(sendBtn);

    QVBoxLayout * vlay = new QVBoxLayout;
    vlay->addStretch();
    vlay ->addLayout(hlay1);
    vlay->addLayout(hblay);
    vlay->addLayout(hlay4);
    vlay->addStretch();
    vlay->setMargin(0);
    vlay->setSpacing(50);

    wid = new QWidget;
    wid->setFixedSize(QSize(370,270));
    wid->setLayout(vlay);
    QHBoxLayout * mainLay = new QHBoxLayout;
    mainLay->addStretch();
    mainLay->addWidget(wid);
    mainLay->addStretch();
    setLayout(mainLay);
}
