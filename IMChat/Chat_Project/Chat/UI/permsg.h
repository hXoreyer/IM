#ifndef PERMSG_H
#define PERMSG_H
#include "Chat/Fun/common.h"
#include "qnchatmessage.h"
#include "Chat/Fun/frmscreen.h"
#include "Chat/Fun/myemotionwidget.h"
#include "Chat/Fun/chatrecord.h"
#include "Chat/Fun/json.h"
#include "Chat/NetWork/udp.h"
#include <QTextEdit>
#include <QDateTime>
class PerMsg : public QWidget
{
    Q_OBJECT
public:
    PerMsg(const QString& self_name, const QString& nick_name,const QString& friend_email, QWidget* parent= nullptr);
    ~PerMsg();
    QLayout * perMsg_lable();
    QLayout * perMsg_list();
    QLayout * perMsg_send();
    void getWidget();
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item,const QPixmap& headimg, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(const QDateTime& time);
    inline QListWidget* get_listWidget()const{return m_listWidget;}
    void add_chatRecord();
private:
    QString m_self_email;
    QString m_nick_name;
    QString m_friend_email;
private:
    QHBoxLayout * perInfoLay;
    QVBoxLayout * chatInfoLay;
    QVBoxLayout * sendInfoLay;
    QVBoxLayout * mainLay;

private:
    QPushButton * perName;
    QScrollArea * perInfo;
    QTextEdit * textEdit;
    QPushButton * sendBtn;
    QPushButton ** toolBtn;
private:
    QNChatMessage * ptr_perMessageW;
    QString m_sendText;
    QString  m_sendTime;
    QNChatMessage::User_Type m_sendType;
    QString m_filePath;
    frmScreen  m_frmScreen;
    MyEmotionWidget m_emotionWidget;
    ChatRecord * m_ChatRecord;
    QListWidget * m_listWidget;
    QDateTime m_lastSendTime;
    JSON m_json;
    /*
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    */
signals:
    void on_saveChatRecord(const QString&,const std::pair<QString,QString>&,const QString&,const QString&);
    void on_getChatRecord(const QString&);
    void on_sendMessSuss(const QString& nick_name, const QString& mess);

public slots:
    bool eventFilter(QObject *,QEvent *);
    void onSendMessage_Clicked();
};

#endif // PERMSG_H
