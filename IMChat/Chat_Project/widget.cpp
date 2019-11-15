#include "widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
       /*interface size settings*/
       setFixedSize(440,330);
       setWindowFlag(Qt::FramelessWindowHint);
       QPalette pal(this->palette());
       pal.setColor(QPalette::Background,Qt::white);
       this->setPalette(pal);

       /*set the rounded corner window */

       QBitmap bmp(this->size());
       bmp.fill();

       /*
       QPainter p(&bmp);
       p.setRenderHint(QPainter::Antialiasing);
       p.setPen(Qt::NoPen);
       p.setBrush(Qt::black);
       p.drawRoundedRect(bmp.rect(),2,2);
       setMask(bmp);
       */



       /*move interface center*/
       QDesktopWidget * desk = QApplication::desktop();
       QPointer<QDesktopWidget> ptr_desk = desk;
       move((ptr_desk->width()-this->width())/2,(ptr_desk->height()-this->height())/2);

       /*font settings*/
       QFont font;
       font.setFamily("幼圆");
       font.setBold(false);
       font.setPointSize(12);

       /*user input lineEdit*/
       user = new QLineEdit;
       user->setAttribute(Qt::WA_DeleteOnClose);
       user->setFixedHeight(32);
       user->setFont(font);
       user->setPlaceholderText("邮箱");
       user->installEventFilter(this);

       /*user stylesheet*/
       user->setStyleSheet("QLineEdit{border-bottom:1px solid #ccc;border-style:outset;"
                            "border-top:0px;border-left:0px;border-right:0px; }"
                            "QLineEdit:focus{border-bottom:1px solid #87CEFA;border-style:outset}");

       /*user icon settings*/
       user_act_left = new QAction;
       user_act_left->setIcon(QIcon(":/image/User.svg"));
       user->addAction(user_act_left,QLineEdit::LeadingPosition);



       /*password input lineEdit*/
       psw = new QLineEdit;
       psw->setAttribute(Qt::WA_DeleteOnClose);
       psw->setFont(font);
       psw->setFixedHeight(32);
       psw->setEchoMode(psw->Password);
       psw->setPlaceholderText("密码");
       psw->installEventFilter(this);

       psw->setObjectName("psw");
       psw->setStyleSheet("#psw{border-bottom:1px solid #ccc;border-style:outset;"
                     "border-top:0px;border-left:0px;border-right:0px;}"
                     "#psw:focus{border-bottom:1px solid #87CEFA;border-style:outset;"
                     "border-top:0px;border-left:0px;border-right:0px}");

       /*the icon of password */
       psw_act_left = new QAction(psw);
       psw_act_left->setIcon(QIcon(":/image/Psw.svg"));
       psw->addAction(psw_act_left,QLineEdit::LeadingPosition);
       connect(psw,&QLineEdit::textChanged,this,[&](){
           psw->setFont(QFont("幼圆",8,QFont::Normal));
           if(psw->text().isEmpty())
               psw->setFont(QFont("幼圆",12,QFont::Normal));
       });



       /*
        * ---remember password
        * -- auto login in
        * --forget password
      */
       QPointer<QHBoxLayout> lay(new QHBoxLayout);
       std::vector<QString> str = {"记住密码","自动登录"};
       unsigned int i = 0;
       for( ;i < 2; ++i)
       {
           check_box[i] = new QCheckBox;
           check_box[i]->setText(str[i]);
           check_box[i]->setVisible(true);
           check_box[i]->setFont(QFont("Microsoft YaHei",8,QFont::Bold));
           check_box[i]->setStyleSheet("QCheckBox{color:#D3D3D3;}"
                                       "QCheckBox::indicator {width:16px; height:16px;}"
                                       "QCheckBox::indicator:unchecked {image: url("
                                       ":image/CheckBox.svg)}");
           lay->addWidget(check_box[i]);
       }
       connect(check_box[0],&QCheckBox::stateChanged,this,[&]()
       {
           QSettings *config = new QSettings("info.ini",QSettings::IniFormat);
           QString m_user = user->text();
           QString m_psw = psw->text();
           if(!m_user.isEmpty() && !m_psw.isEmpty())
           {
               config->setValue("Info/User",m_user);
               config->setValue("Info/Password",m_psw);
           }
           delete config;
       });
       connect(check_box[1],&QCheckBox::stateChanged,this,[&]()
       {
           QSettings *config = new QSettings("info.ini",QSettings::IniFormat);
           config->setValue("Log/AutoLog","Yes");
           delete config;
       });
       forget_psw = new QPushButton;
       forget_psw->setAttribute(Qt::WA_DeleteOnClose);
       forget_psw->setText("忘记密码");
       forget_psw->setFlat(true);
       forget_psw->setFont(QFont("Microsoft YaHei",8,QFont::Bold));
       forget_psw->setStyleSheet("QPushButton{color:#D3D3D3}"
                                 "QPushButton:hover{border:0px;color:#696969}"
                                 "QPushButton:pressed{border:0px;color:#696969;}");
       lay->addWidget(forget_psw);


       /*the style of sign button*/
       sign = new QPushButton;
       sign->setAttribute(Qt::WA_DeleteOnClose);
       sign->setText("登录");
       sign->setObjectName("sign");
       sign->setStyleSheet("#sign{border-style:none; border-radius:4px;background-color:#3A5FCD;"
                           "color:white}"
                           "#sign:hover{border-style:none; border-radius:4px;background-color:#6495ED;"
                                                   "color:white;padding-left:-1px;padding-bottom:-1px}"
                           "#sign:pressed{border-style:none; border-radius:4px;background-color:"

                           "#5CACEE;"
                           "color:white;padding-left:-1px;padding-bottom:-1px}");
       sign->setFont(QFont("Microsoft YaHei",12,QFont::Bold));
       sign->setFixedHeight(30);
       connect(sign,&QPushButton::clicked,this,&Widget::sendMessage);

       /*
        * --register number;
       */
       rege = new QPushButton;
       rege->setAttribute(Qt::WA_DeleteOnClose);
       rege->setText("注册账号");
       rege->setObjectName("rege");
       rege->setFixedHeight(30);
       rege->setFont(QFont("Microsoft YaHei",11,QFont::Bold));
       rege->setStyleSheet("#rege{border:2px;border-width:40px;color:#ccc}"
                           "#rege:hover{border:2px;border-width:40px;color:#8b8a8d}");
       connect(rege,&QPushButton::clicked,this,[&]()
       {
           QDesktopServices::openUrl(QUrl(QLatin1String("http://im.keing.top/register")));
       });

       saveInfo();
       QPointer<QVBoxLayout> vblay(new QVBoxLayout);
       QPointer<QVBoxLayout> hblayout(new QVBoxLayout);
       QPointer<QHBoxLayout> hblay(new QHBoxLayout);

       vblay->addWidget(user);
       vblay->addWidget(psw);

       hblayout->addWidget(sign);
       hblayout->addWidget(rege);

       /* the setting of heading */
       hblay->addWidget(getHeadImg(":/image/head.jpg"));

       mlay = new QVBoxLayout(this);
       mlay->addLayout(toptoolBar());
       QPointer<QVBoxLayout> flay(new QVBoxLayout);
       flay->addLayout(hblay);
       flay->addLayout(vblay);
       flay->addLayout(lay);
       flay->addLayout(hblayout);
       flay->setSpacing(10);
       flay->setMargin(0);
       flay->setContentsMargins(100,15,100,5);

       stack_widget = new QStackedWidget;
       stack_widget->setAttribute(Qt::WA_DeleteOnClose);
       QWidget *w_first = new QWidget;
       w_first->setAttribute(Qt::WA_DeleteOnClose);
       w_first->setLayout(flay);
       stack_widget->addWidget(w_first);
       connect(sign,&QPushButton::clicked,this,&Widget::btnChange);
       login_connect_request();
       QPointer<QVBoxLayout> mainlayout(new QVBoxLayout);
       mainlayout->addWidget(stack_widget);
       mlay->addLayout(mainlayout);
       mlay->setMargin(0);
       mlay->setSpacing(0);
       setLayout(mlay);
}

Widget::~Widget()
{
}
bool Widget::eventFilter(QObject * watched,QEvent *event)
{
    if(watched == user)
    {
        if(QEvent::FocusIn == event->type())
        {
            user_act_left->setIcon(QIcon(":/image/UserFocus.svg"));
            user->addAction(user_act_left,QLineEdit::LeadingPosition);
        }else if (QEvent::FocusOut == event->type()) {
            user_act_left->setIcon(QIcon(":/image/User.svg"));
            user->addAction(user_act_left,QLineEdit::LeadingPosition);
        }
    }else if (watched == psw)
    {
        if(QEvent::FocusIn == event->type())
        {
            psw_act_left->setIcon(QIcon(":/image/PswFocus.svg"));
            psw->addAction(psw_act_left,QLineEdit::LeadingPosition);
        }else if(QEvent::FocusOut == event->type())
        {
            psw_act_left->setIcon(QIcon(":/image/Psw.svg"));
            psw->addAction(psw_act_left,QLineEdit::LeadingPosition);
        }
    }
    return QWidget::eventFilter(watched,event);
}
QPixmap Widget::pixmapToRound(QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}
QLabel* Widget::getHeadImg(QString src)
{
    QPixmap pixmap_userIcon;
    pixmap_userIcon.load(src);
    QPixmap fitpixmap_userIcon=pixmap_userIcon.scaled(80, 80, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    fitpixmap_userIcon = this->pixmapToRound(fitpixmap_userIcon,100);
    QLabel *headimg = new QLabel;
    headimg->setAttribute(Qt::WA_DeleteOnClose);
    headimg->setScaledContents(true);
    headimg->setFixedSize(82,82);
    headimg->setPixmap(fitpixmap_userIcon);
    headimg->setObjectName("headimg");
    headimg->setStyleSheet("#headimg{border-width:2px; border-color:#ccc ;border-style:solid;"
                           "border-radius:40px;}"
                           "#headimg:hover{border-width:2px; border-color:#7EC0EE ;border-style:solid;"
                           "border-radius:40px;}");
    return headimg;
}
QLayout* Widget::toptoolBar()
{
    minBtn = new QPushButton;
    minBtn->setAttribute(Qt::WA_DeleteOnClose);
    cloBtn = new QPushButton;
    cloBtn->setAttribute(Qt::WA_DeleteOnClose);

    minBtn->setFixedSize(30,30);
    cloBtn->setFixedSize(30,30);

    minBtn->setToolTip("最小化");
    cloBtn->setToolTip("关闭");

    QPixmap min_ico(":/image/Min.svg");
    QPixmap close_ico(":/image/Close.svg");
    minBtn->setIcon(min_ico);
    cloBtn->setIcon(close_ico);

    minBtn->setStyleSheet("QPushButton{border-style:none;width:40px;height:40px;color:#D6D6D6}"
                          "QPushButton:visited{border-style:none}"
                          "QPushButton:hover{border-style:none;width:40px;height:40px;"
                          "background-color:qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0.368182 rgba(198,198,198,75))}"
                          "QPushButton:pressed{border-style:none;width:40px;height:40px;"
                          "background-color:qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0.368182 rgba(100,100,100,75))}");
    cloBtn->setStyleSheet("QPushButton{border-style:none;width:40px;height:40px;color:#D6D6D6;}"
                               "QPushButton:hover{border-style:none;width:40px;height:40px;background-color:red}"
                               "QPushButton:pressed{border-style:none;width:40px;height:40px;"
                               "background-color:red}");

    connect(cloBtn,&QPushButton::clicked,this,[&]()
    {
        this->close();
    });
    connect(minBtn,&QPushButton::clicked,this,[&]()
    {
        this->showMinimized();
    });

    QPointer<QHBoxLayout> tittle_lay(new QHBoxLayout);
    QLabel* tittle = new QLabel;
    tittle->setAttribute(Qt::WA_DeleteOnClose);
    tittle_lay->addWidget(tittle);
    tittle_lay->addWidget(minBtn);
    tittle_lay->addWidget(cloBtn);
    tittle_lay->setStretchFactor(tittle,10);
    tittle_lay->setStretchFactor(minBtn,1);
    tittle_lay->setStretchFactor(cloBtn,1);
    tittle_lay->setMargin(0);
    tittle_lay->setSpacing(0);

    return tittle_lay;

}
void Widget::mousePressEvent(QMouseEvent *event)
{

#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}
void Widget::sendMessage()
{

    QString m_user = user->text();
    QString m_psw = psw->text();
    if(m_user == nullptr || m_psw == nullptr)
    {
        if(m_user == nullptr)
        {
            QPoint xy = user->pos();
            xy.setX(xy.x()+24);
            xy.setY(xy.y()+40);
            QToolTip::showText(mapToGlobal(xy),"请输入账号后再登录");
        }else {
            QPoint xy = psw->pos();
            xy.setX(xy.x()+24);
            xy.setY(xy.y()+40);
            QToolTip::showText(mapToGlobal(xy),"请输入密码后再登录");
        }
        disconnect(sign,&QPushButton::clicked,this,&Widget::btnChange);
        connect(sign,&QPushButton::clicked,this,&Widget::btnChange);
        return;
    }
    if(check_local_network() == false)
    {
        disconnect(sign,&QPushButton::clicked,this,&Widget::btnChange);
        connect(sign,&QPushButton::clicked,this,&Widget::btnChange);
        QPoint xy  = rege->pos();
        xy.setX(xy.rx()-99);
        xy.setY(xy.ry() + 22);
        QToolTip::showText(mapToGlobal(xy),"请检查你的网络是否连接正确");
        return;
    }
    if(socket.request_server() == false)
    {
         qDebug()<<"request error";
         QPoint xy  = rege->pos();
         xy.setX(xy.rx() -99);
         xy.setY(xy.ry() + 22);
         QToolTip::showText(mapToGlobal(xy),"服务器请求超时");
         return;
    }
    net::MSG msg;
    memset(&msg,0,sizeof (msg));
    msg.user_type = 'a';
    strcpy(msg.user_email,m_user.toLatin1().data());
    strcpy(msg.user_pass,m_psw.toLatin1().data());
    char send_msg[sizeof (msg)] = {0};
    memcpy(send_msg,&msg,sizeof (msg));

    bool sendStatus = socket.send_message(send_msg,sizeof (msg));
    if(!sendStatus)
    {
        stack_widget->setCurrentIndex(0);
        QPoint xy  = rege->pos();
        xy.setX(xy.rx()-99);
        xy.setY(xy.ry() +22);
        QToolTip::showText(mapToGlobal(xy),"请检查你的网络是否连接正确");
        return;
    }
    recv_message();
    socket.close_socket();
}
void Widget::recv_message()
{
    net::MSG recvMsg;
    memset(&recvMsg,0,sizeof (recvMsg));
    char recv[sizeof (recvMsg)] = {0};
    bool flag = socket.recv_message(recv,sizeof (recvMsg));
    if(!flag)
    {
        return;
    }
    memcpy(&recvMsg,recv,sizeof (recvMsg));
    if(recvMsg.user_type == 'a')
    {
        if(recvMsg.login_result == 'a')
        {
            while(true)
            {
                net::MSG perMsg;
                memset(&perMsg,0,sizeof (perMsg));
                char m_recv[sizeof (perMsg)] = {0};
                bool status = socket.recv_message(m_recv,sizeof (perMsg));
                if(!status)
                    continue;
                memcpy(&perMsg,m_recv,sizeof (perMsg));
                if(perMsg.user_type == 'f')
                {
                    vec_friends.push_back(perMsg);
                }else if(perMsg.user_type == 'e')
                    break;
            }
            qDebug()<<"success";
            //Chat_Ui chat_w;
            this->hide();
            //chat_w.show();
            return;
        }else if(recvMsg.login_result == 'b' )
        {
            stack_widget->setCurrentIndex(0);
            QPoint xy = psw->pos();
            xy.setX(xy.rx()+24);
            xy.setY(xy.ry() + 40);
            QToolTip::showText(mapToGlobal(xy),"密码输入错误");
            return;
        }else if(recvMsg.login_result == 'c')
        {
            stack_widget->setCurrentIndex(0);
            QPoint xy = user->pos();
            xy.setX(xy.rx()+24);
            xy.setY(xy.ry() + 40);
            QToolTip::showText(mapToGlobal(xy),"账号未注册，请注册账号");
            return;

        }else
           return;
    }
}
void Widget::login_connect_request()
{
    QPointer<QHBoxLayout> ptr_hblay(new QHBoxLayout[3]);
    QLabel * request_lable = new QLabel("正在登录...");
    request_lable->setAttribute(Qt::WA_DeleteOnClose);
    request_lable->setFont(QFont("Microsoft YaHei",11,QFont::Bold));
    request_lable->setStyleSheet("color:#cfcfcf");
    QPointer<QVBoxLayout> flay_login(new QVBoxLayout);
    ptr_hblay[0].addWidget(getHeadImg(":/image/head.jpg"),Qt::AlignHCenter);
    ptr_hblay[1].addStretch();
    ptr_hblay[1].addWidget(request_lable);
    ptr_hblay[1].addStretch();
    cancelBtn = new QPushButton("取消登录");
    cancelBtn->setAttribute(Qt::WA_DeleteOnClose);
    cancelBtn->setFont(QFont("Microsoft YaHei",12,QFont::Bold));
    cancelBtn->setFixedHeight(32);
    cancelBtn->setStyleSheet("QPushButton{border-style:none; border-radius:4px;background-color:#3A5FCD;"
                        "color:white}"
                        "QPushButton:hover{border-style:none; border-radius:4px;background-color:#6495ED;"
                                                "color:white;padding-left:-1px;padding-bottom:-1px}"
                        "QPushButton:pressed{border-style:none; border-radius:4px;background-color:"

                        "#5CACEE;"
                        "color:white;padding-left:-1px;padding-bottom:-1px}");
    ptr_hblay[2].addWidget(cancelBtn,Qt::AlignHCenter);
    flay_login->addStretch(1);
    flay_login->addLayout(&ptr_hblay[0],3);
    flay_login->addLayout(&ptr_hblay[1],3);
    flay_login->addLayout(&ptr_hblay[2],3);
    flay_login->addStretch(1);
    flay_login->setContentsMargins(100,15,100,5);
    QWidget * w_second = new QWidget;
    w_second->setAttribute(Qt::WA_DeleteOnClose);
    w_second->setLayout(flay_login);
    stack_widget->addWidget(w_second);
    connect(cancelBtn,&QPushButton::clicked,this,&Widget::btnChange);
}
void Widget::btnChange()
{
    QPushButton* btn = static_cast<QPushButton*>(sender());
    if(btn == sign)
    {
        stack_widget->setCurrentIndex(1);
    }else if (btn == cancelBtn)
    {
        stack_widget->setCurrentIndex(0);
    }
}
bool Widget::check_local_network()
{
    QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
    if(info.addresses().isEmpty())
    {
        return false;
    }
    else
        return true;
}
void Widget::saveInfo()
{

    QSettings *config = new QSettings("info.ini", QSettings::IniFormat);
    QString m_user = config->value("Info/User").toString();
    QString m_psw = config->value("Info/Password").toString();
    if(!m_user.isEmpty() && !m_psw.isEmpty())
    {
        user->setText(m_user);
        psw->setText(m_psw);
    }
    delete config;
}





