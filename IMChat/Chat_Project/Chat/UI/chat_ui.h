#ifndef CHAT_UI_H
#define CHAT_UI_H
#include "Chat/Fun/common.h"
#include <QScrollArea>
#include <QListWidget>
#include "setup.h"
#include "feedback.h"
#include "Chat/Fun/controller.h"
#include "Chat/Fun/sqlite.h"
static int m_mess_count_ = 0;
static int m_map_count = 0;
class Chat_Ui : public QWidget
{
    Q_OBJECT
public:
    Chat_Ui(const QString& self_email,const std::vector<net::MSG>& vec,QWidget *parent = nullptr);
    ~Chat_Ui();
private:
    QHBoxLayout * main_layout;
    QVBoxLayout * vblay_left;
    QVBoxLayout * vblay_center;
    QVBoxLayout * vblay_right;
    QVBoxLayout * vlay_find;

private:
    QPushButton*    closeBtn;
    QPushButton*    maxBtn;
    QPushButton*     minBtn;
    QPushButton*    chatBtn;
    QPushButton*    messBtn;
    QPushButton*    moreBtn;
    QStackedWidget*     left_stackWidget;
    QStackedWidget*     right_stackWidget;
    QWidget*    friendsList_Group;
    QPushButton*         headimg;
    QLineEdit*      searchEdit;
    QPushButton*   addGroupChat;
    QScrollArea*    searchResult;
    QListWidget* leftList[3];
    SetUp setObj;
    FeedBack fbObj;
    QVBoxLayout * vlay_card;
private:
    std::vector<net::MSG> vec_friends;
    std::map<int,int> vec_findList;
    std::map<int,int> vec_mess;
    std::map<int,int> map_mess;
    std::map<int,int> map;
    QString m_self_email;
    Controller m_thread;
    SQLite m_sql;
    QStackedWidget * ptrMessWid;
    int m_messRow ;

public:

    QLayout * left_ui();
    QLayout * center_ui();
    QLayout * right_ui();
    void friendsGroup_list();
    void send_LoginStatus();
    int find_PerIndex(const QString& email);
    int find_perIsVisual(const QString& nick_name);
    void request_friendAddr(const QString& friend_email);
signals:
    void disClicked();
public slots:
    void on_titleBtn_clicked();
    QPixmap pixmapToRound(QPixmap &src, int radius);
    QPushButton* getHeadImg(QString src);
    bool eventFilter(QObject *,QEvent *);
    void listItemClicked(int row);
    void messItemClicked(int row);
    void find_result(const QString& text);
    void save_chatRecord(const QString& self,const std::pair<QString,QString>& f_pair,const QString& str,const QString& time);
    void recv_newMessage(const UDP::MSG& msg);

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // CHAT_UI_H
