#ifndef WIDGET_H
#define WIDGET_H
#include "Chat/Fun/common.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QPixmap pixmapToRound(QPixmap &src, int radius);
    QLabel* getHeadImg(QString src);
    QLayout* toptoolBar();
    void login_connect_request();
    void saveInfo();
    bool check_local_network();
    void recv_message();

private:
    QLineEdit * user;   //user
    QLineEdit * psw;    //password
    QPushButton * sign; //login in
    QCheckBox * check_box[2]; //auto login in, remember password
    QPushButton * forget_psw;    //forget password
    QPushButton * rege; //account number register
    QAction * user_act_left;    //the icon of user;
    QAction * psw_act_left;     //the icon of password;
    QPushButton * minBtn;   //the button of minimize;
    QPushButton *cloBtn;    //the button of close
    QVBoxLayout * mlay;     //the main layout of ui;
    QVBoxLayout * mlay_log;
    QVBoxLayout * flay_login;
    QStackedWidget *stack_widget;
    QPushButton * cancelBtn;
    std::vector<net::MSG> vec_friends;

private:
    bool m_isRember;
    bool m_autoLog;

    Socket socket;
protected:
    void mousePressEvent(QMouseEvent *event);


signals:

private slots:
    bool eventFilter(QObject *,QEvent *);
    void sendMessage();

    void btnChange();
};
#endif // WIDGET_H
