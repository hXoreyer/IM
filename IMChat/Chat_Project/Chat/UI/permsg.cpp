#include "permsg.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QToolTip>
PerMsg::PerMsg(const QString& self_email, const QString& nick_name,const QString& friend_email, QWidget *parent)
    :QWidget(parent),m_self_email(self_email), m_nick_name(nick_name),m_friend_email(friend_email)
{
    m_lastSendTime =  QDateTime::currentDateTime();
    getWidget();
}
PerMsg::~PerMsg()
{
}
QLayout * PerMsg::perMsg_lable()
{
    perName = new QPushButton;
    perName->setText(QString(m_nick_name));
    perName->setFont(QFont("Microsoft YaHei",12,QFont::Normal));
    perName->setFlat(true);
    perName->setStyleSheet("QPushButton{border-style:none;}");
    perInfoLay = new QHBoxLayout;
    perInfoLay->addSpacing(20);
    perInfoLay->addWidget(perName);
    perInfoLay->addStretch();
    perInfoLay->setMargin(0);
    return perInfoLay;
}
QLayout * PerMsg::perMsg_list()
{

    QVBoxLayout * vlay = new QVBoxLayout;
    m_listWidget = new QListWidget;
    m_listWidget->setObjectName("listWidget");
    m_listWidget->setStyleSheet("QListWidget{background-color:#fafafa;border:0px}");
    m_listWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {border: none;"
                                                 "background: #dfdfdf;"
                                                 "width: 12px;}"
                                                 "QScrollBar::handle:vertical {border: none;"
                                                 "border-radius: 5px;"
                                                 "background: #cfcfcf;}");
    m_listWidget->horizontalScrollBar()->hide();
    vlay->addWidget(m_listWidget);
    return vlay;
}
QLayout * PerMsg::perMsg_send()
{
    toolBtn = new QPushButton*[6];
    QHBoxLayout * hlay = new QHBoxLayout;
    std::vector<QString> vec = {"表情","发送文件","截图","聊天记录","语音聊天","视频聊天"};
    std::vector<QString> vecImg = {"Face.svg","File.svg","Cut.svg","ChatRecord.svg","SoundChat.svg","VideoChat.svg"};
    for(unsigned i = 0;i < 6;++i)
    {
        toolBtn[i] = new QPushButton;
        toolBtn[i]->setToolTip(vec[i]);
        toolBtn[i]->setIcon(QIcon(":/Chat/image/"+vecImg[i]));
        toolBtn[i]->setFlat(true);
        toolBtn[i]->setFixedSize(QSize(20,20));
        toolBtn[i]->setIconSize(QSize(20,20));
        toolBtn[i]->setStyleSheet("QPushButton{border-style:none;}");
        toolBtn[i]->installEventFilter(this);
        if(i == 4)
            hlay->addStretch();
        hlay->addWidget(toolBtn[i]);
    }
    hlay->setSpacing(10);
    hlay->setMargin(10);
    connect(toolBtn[0],&QPushButton::clicked,this,[&]()
    {
        if(m_emotionWidget.isVisible())
        {
            m_emotionWidget.hide();
        }else
        {
            QCursor cursor;
            QPoint point = cursor.pos();
            m_emotionWidget.move(point.x()-10,point.y() - 330);
            m_emotionWidget.show();
        }
    });
    connect(&m_emotionWidget,&MyEmotionWidget::sendEmotionPath,this,[&](const QString& path)
    {
        textEdit->append(path);
    });
    connect(toolBtn[1],&QPushButton::clicked,this,[&]()
    {
        QString fileName = QFileDialog::getOpenFileName(this,tr("此电脑"),"C:","");
        textEdit->append(fileName);

    });
    toolBtn[2]->setShortcut(QKeySequence(QLatin1String("Alt+A")));
    connect(toolBtn[2],&QPushButton::clicked,this,[&]()
    {
        m_frmScreen.showFullScreen();
    });
    connect(&m_frmScreen,&frmScreen::sendScreenImgPath,this,[&](const QString& path)
    {
        textEdit->append(path);
    });
    m_ChatRecord = new ChatRecord(m_nick_name);
    connect(toolBtn[3],&QPushButton::clicked,this,[&]()
    {
        emit on_getChatRecord(m_friend_email);
        m_ChatRecord->show();
    });
     textEdit = new QTextEdit;
     textEdit->setStyleSheet("QTextEdit{border-style:none}");
     textEdit->setFont(QFont("Consolas",12,QFont::Normal));
     textEdit->setAcceptDrops(true);

     QHBoxLayout * hblay = new QHBoxLayout;
     sendBtn = new QPushButton("发送(S)");
     sendBtn->setFixedSize(QSize(65,30));
     sendBtn->setStyleSheet("QPushButton{border:0px; border-radius:4px;background-color:#f9f9f9}"
                            "QPushButton:hover{border:0px; border-radius:4px;background-color:#6495ED;"
                            "color:#F8F8FF;padding-left:-1px;padding-bottom:-1px}"
                            "#QPushButton:pressed{border:0px; border-radius:4px;background-color:#5CACEE;"
                            "color:white;padding-left:-1px;padding-bottom:-1px}");
     sendBtn->setFont(QFont("Consolas",10));
     connect(sendBtn,&QPushButton::clicked,this,&PerMsg::onSendMessage_Clicked);
     hblay->addStretch();
     hblay->addWidget(sendBtn);

     sendInfoLay = new QVBoxLayout;
     sendInfoLay->addLayout(hlay);
     sendInfoLay->addWidget(textEdit);
     sendInfoLay->addLayout(hblay);
     sendInfoLay->setContentsMargins(25,0,25,10);

     return sendInfoLay;

}
void PerMsg::getWidget()
{
    QVBoxLayout * vlay = new QVBoxLayout;
    vlay->addLayout(perMsg_lable(),1);
    vlay->addLayout(perMsg_list(),6);
    QWidget * backPer = new QWidget;
    backPer->setLayout(perMsg_send());
    backPer->setStyleSheet("QWidget{background-color:white}");
    vlay->addWidget(backPer,2);
    vlay->setMargin(0);
    vlay->setSpacing(11);
    setLayout(vlay);
    setStyleSheet("QWidget{background-color:#fafafa}");
}
bool PerMsg::eventFilter(QObject * watched,QEvent *event)
{
    if(watched == toolBtn[0])
    {
        if(QEvent::HoverEnter == event->type())
        {
            toolBtn[0]->setIcon(QIcon(":/Chat/image/FaceFocus.svg"));
            toolBtn[0]->setCursor(QCursor(Qt::PointingHandCursor));
        }
        if(QEvent::HoverLeave == event->type())
        {
            toolBtn[0]->setIcon(QIcon(":/Chat/image/Face.svg"));
            toolBtn[0]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    else if(watched == toolBtn[1])
    {
        if(QEvent::HoverEnter == event->type())
        {
            toolBtn[1]->setIcon(QIcon(":/Chat/image/FileFocus.svg"));
            toolBtn[1]->setCursor(QCursor(Qt::PointingHandCursor));
        }
        if(QEvent::HoverLeave == event->type())
        {
            toolBtn[1]->setIcon(QIcon(":/Chat/image/File.svg"));
            toolBtn[1]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    else if(watched == toolBtn[2])
    {
        if(QEvent::HoverEnter == event->type())
        {
            toolBtn[2]->setIcon(QIcon(":/Chat/image/CutFocus.svg"));
            toolBtn[2]->setCursor(QCursor(Qt::PointingHandCursor));

        }
        if(QEvent::HoverLeave == event->type())
        {
            toolBtn[2]->setIcon(QIcon(":/Chat/image/Cut.svg"));
            toolBtn[2]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    else if(watched == toolBtn[3])
    {
        if(QEvent::HoverEnter == event->type())
        {
            toolBtn[3]->setIcon(QIcon(":/Chat/image/ChatRecordFocus.svg"));
            toolBtn[3]->setCursor(QCursor(Qt::PointingHandCursor));
        }
        if(QEvent::HoverLeave == event->type())
        {
            toolBtn[3]->setIcon(QIcon(":/Chat/image/ChatRecord.svg"));
            toolBtn[3]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    else if(watched == toolBtn[4])
    {
        if(QEvent::HoverEnter == event->type())
        {
            toolBtn[4]->setIcon(QIcon(":/Chat/image/SoundChatFocus.svg"));
            toolBtn[4]->setCursor(QCursor(Qt::PointingHandCursor));
        }
        if(QEvent::HoverLeave == event->type())
        {
            toolBtn[4]->setIcon(QIcon(":/Chat/image/SoundChat.svg"));
            toolBtn[4]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    else if(watched == toolBtn[5])
    {
        if(QEvent::HoverEnter == event->type())
        {
            toolBtn[5]->setIcon(QIcon(":/Chat/image/VideoChatFocus.svg"));
            toolBtn[5]->setCursor(QCursor(Qt::PointingHandCursor));
        }
        if(QEvent::HoverLeave == event->type())
        {
            toolBtn[5]->setIcon(QIcon(":/Chat/image/VideoChat.svg"));
            toolBtn[5]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}
void PerMsg::dealMessage(QNChatMessage *messageW, QListWidgetItem *item,const QPixmap& headimg, QString text, QString time, QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(headimg,text, time, size, type);
    m_listWidget->setItemWidget(item, messageW);
    m_listWidget->scrollToBottom();
}
void PerMsg::onSendMessage_Clicked()
{
    QString msg = textEdit->toPlainText();
    if(msg.isEmpty())
    {
        QPoint xy = sendBtn->pos();
        xy.setX(xy.x()-10);
        xy.setY(xy.y()+250);
        QToolTip::showText(mapToGlobal(xy),"发送信息不能为空");
        return;
    }
    textEdit->clear();
    QDateTime time = QDateTime::currentDateTime();
    dealMessageTime(time);
    m_lastSendTime = time;

    QPixmap headimg(":Chat/image/head.jpg");

    QNChatMessage* messageW = new QNChatMessage(m_listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(m_listWidget);
    dealMessage(messageW, item,headimg, msg, time.toString("yy:MM:dd hh:mm:ss"), QNChatMessage::User_Me);
    //Udp m_udp;
    UDP::MSG m_msg;
    memset(&m_msg,0,sizeof (m_msg));
    m_msg.type = UDP::CHAR;
    strcpy(m_msg.send_char,msg.toUtf8().data());
    strcpy(m_msg.send_user,m_self_email.toUtf8().data());
    strcpy(m_msg.recv_user,m_friend_email.toUtf8().data());
    char send_msg[sizeof (m_msg)] = {0};
    memcpy(send_msg,&m_msg,sizeof (m_msg));

    bool result = sento_message(send_msg,sizeof(send_msg));
    if(!result)
    {
        messageW->setTextSuccess(false);
        return;
    }
    messageW->setTextSuccess(true);
    qDebug()<<"send sus";

    emit on_sendMessSuss(m_nick_name,msg);
    //emit on_saveChatRecord(m_self_email,{m_friend_email,m_nick_name},msg,time.toString("yy:MM:dd hh:mm:ss"));
}
void PerMsg::dealMessageTime(const QDateTime &time)
{
    auto resultTime = time.toTime_t() - m_lastSendTime.toTime_t();
    QString convert_time =  QDateTime::fromTime_t(resultTime).toString("mm:ss");
    if(resultTime < 120)
        return;
    QListWidgetItem * item = new QListWidgetItem(time.toString("yy-MM-dd hh:mm"));
    item->setTextAlignment(Qt::AlignCenter);
    m_listWidget->addItem(item);
}
void PerMsg::add_chatRecord()
{

}
