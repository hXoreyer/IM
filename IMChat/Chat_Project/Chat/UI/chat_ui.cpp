#include "chat_ui.h"

Chat_Ui::Chat_Ui(const QString& self_email,const std::vector<net::MSG>& vec,QWidget *parent)
    : QWidget(parent),vec_friends(vec),m_self_email(self_email)
{
    send_LoginStatus();
    setMinimumSize(QSize(710,500));
    setWindowFlags(Qt::FramelessWindowHint);
    for(unsigned i = 0;i< 3;++i)
    {
        leftList[i] = new QListWidget;
        leftList[i]->setStyleSheet("QListWidget{background:#f0f0f0;border:0px}"
                                "QListWidget::item:hover{background:#E8E8E8}"
                                "QListWidget::item:selected{background:#D3D3D3}");
        leftList[i]->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {border: none;"
                                                     "background: #dfdfdf;"
                                                     "width: 12px;}"
                                                     "QScrollBar::handle:vertical {border: none;"
                                                     "border-radius: 5px;"
                                                     "background: #cfcfcf;}"                                             "QScrollBar::add-page:vertical {border: none;"                                             "background-color: #dfdfdf;}"                                             "QScrollBar::sub-page:vertical {border: none;"                                             "background-color: #dfdfdf;}");

        leftList[i]->setFocusPolicy(Qt::NoFocus);
        leftList[i]->installEventFilter(this);
        leftList[i]->setIconSize(QSize(50,50));
    }
    connect(leftList[0],&QListWidget::itemSelectionChanged,this,[&]()
    {
        request_friendAddr(vec_friends[vec_mess[leftList[0]->currentRow()]].friend_email);
        right_stackWidget->setCurrentIndex(0);
    });
    connect(leftList[2],&QListWidget::itemSelectionChanged,this,[&]()
    {
        int key = leftList[2]->currentRow();
        request_friendAddr(vec_friends[vec_findList[key]].friend_email);
        messItemClicked(vec_findList[key]);
    });
    main_layout = new QHBoxLayout(this);
    main_layout->addLayout(left_ui(),1);
    main_layout->addLayout(center_ui(),4);
    main_layout->addLayout(right_ui(),7);
    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    chatBtn->setFocus();
    setLayout(main_layout);
    m_thread.start();
    connect(&m_thread,&Controller::on_newMessage,this,&Chat_Ui::recv_newMessage);
    //m_sql.connect_sql();
}
Chat_Ui::~Chat_Ui()
{
    close_socket();
    serv_close();
    //m_sql.close_sql();
}
QLayout * Chat_Ui::left_ui()
{
    chatBtn = new QPushButton;
    chatBtn->setIcon(QIcon(":/Chat/image/Chat.svg"));
    chatBtn->setToolTip("聊天");
    chatBtn->setIconSize(QSize(34,34));
    chatBtn->setFixedSize(34,34);
    chatBtn->installEventFilter(this);
    chatBtn->setStyleSheet("QPushButton{border:0}");

    messBtn = new QPushButton;
    messBtn->setIcon(QIcon(":/Chat/image/ChatBook.svg"));
    messBtn->setIconSize(QSize(34,34));
    messBtn->setFixedSize(34,34);
    messBtn->setToolTip("通讯录");
    messBtn->setFlat(true);
    messBtn->installEventFilter(this);
    messBtn->setStyleSheet("QPushButton{border:0}");

    moreBtn = new QPushButton;
    moreBtn->setIcon(QIcon(":/Chat/image/More.svg"));
    moreBtn->setIconSize(QSize(34,34));
    moreBtn->setFixedSize(34,34);
    moreBtn->setToolTip("更多");
    moreBtn->setFlat(true);
    moreBtn->installEventFilter(this);
    moreBtn->setStyleSheet("QPushButton{border:0}");

    QMenu * m_file = new QMenu(this);
    QAction * fd_act = new QAction("意见反馈");
    QAction * set_act = new QAction("设置");
    connect(set_act,&QAction::triggered,this,[&]()
    {
        setObj.show();
    });
    connect(fd_act,&QAction::triggered,this,[&]()
    {
        fbObj.show();
    });
    QList<QAction *> m_list;
    m_list<<fd_act<<set_act;
    m_file->addActions(m_list);
    m_file->setStyleSheet("QMenu{background-color:#111922;color:#BEBEBE}"
                          "QMenu::item:selected{background-color:#363636}");
    moreBtn->setMenu(m_file);

    QVBoxLayout * widlay = new QVBoxLayout;
    widlay->addSpacing(10);
    headimg = getHeadImg(":/Chat/image/head.jpg");
    headimg->installEventFilter(this);

    widlay->addWidget(headimg);
    widlay->addWidget(chatBtn);
    widlay->addWidget(messBtn);
    widlay->addStretch();
    widlay->addWidget(moreBtn);
    widlay->setSpacing(17);

    QWidget * backWid = new QWidget;
    backWid->setStyleSheet("background-color:#111922");
    backWid->setLayout(widlay);
    QSizePolicy backPolicy = backWid->sizePolicy();
    backPolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    backWid->setSizePolicy(backPolicy);
    vblay_left = new QVBoxLayout;
    vblay_left->addWidget(backWid);
    return vblay_left;
}
QLayout *  Chat_Ui::center_ui()
{
    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("搜索");
    QAction* searAct = new QAction;
    searAct->setIcon(QIcon(":/Chat/image/Search.svg"));
    searchEdit->addAction(searAct,QLineEdit::LeadingPosition);
    searchEdit->setFixedHeight(30);
    searchEdit->setFont(QFont("Consolas",9));
    searchEdit->setStyleSheet("QLineEdit{border-style:none;background-color:rgba(190,190,190,0.5);border-radius:3px;}");
    searchEdit->installEventFilter(this);
    connect(searchEdit,&QLineEdit::textChanged,this,&Chat_Ui::find_result);

    addGroupChat = new QPushButton;
    addGroupChat->setIcon(QIcon(":/Chat/image/AddGroupChat.svg"));
    addGroupChat->setFixedSize(QSize(30,30));
    addGroupChat->setToolTip("发起群聊");
    addGroupChat->setStyleSheet("QPushButton{border-style:none;background-color:rgba(190,190,190,0.5);border-radius:3px;}"
                                "QPushButton:hover{background-color:rgba(122,128,144,0.5)}");


    QHBoxLayout * hlay_top = new QHBoxLayout;
    hlay_top->addWidget(searchEdit);
    hlay_top->addWidget(addGroupChat);
    hlay_top->setSpacing(10);
    hlay_top->setContentsMargins(10,21,10,0);

    left_stackWidget = new QStackedWidget;
    connect(leftList[0],&QListWidget::currentRowChanged,this,[&](int row)
    {
        ptrMessWid->setCurrentIndex(map[vec_mess[row]]);

    });
    friendsGroup_list();
    left_stackWidget->addWidget(leftList[0]);
    left_stackWidget->addWidget(leftList[1]);
    left_stackWidget->addWidget(leftList[2]);
    vblay_center = new QVBoxLayout;
    vblay_center->addLayout(hlay_top);
    vblay_center->addWidget(left_stackWidget);
    vblay_center->setSpacing(15);
    return vblay_center;
}
QLayout * Chat_Ui::right_ui()
{

    closeBtn = new QPushButton;
    closeBtn->setIcon(QIcon(":/Chat/image/Close.svg"));
    closeBtn->setToolTip("关闭");
    closeBtn->setFixedSize(QSize(25,25));
    closeBtn->setStyleSheet("QPushButton{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;color:#D6D6D6;}"
                               "QPushButton:hover{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;"
                               "background-color:red}"
                               "QPushButton:pressed{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;"
                               "background-color:red}");
    closeBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(closeBtn,&QPushButton::clicked,this,&Chat_Ui::on_titleBtn_clicked);

    maxBtn = new QPushButton;
    maxBtn->setIcon(QIcon(":/Chat/image/Max_Streth.svg"));
    maxBtn->setToolTip("最大化");
    maxBtn->setFixedSize(QSize(25,25));
    maxBtn->setStyleSheet("QPushButton{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;color:#D6D6D6}"
                             "QPushButton:hover{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;"
                             "background-color:qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0.368182 rgba(198,198,198,75))}"
                             "QPushButton:pressed{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;"
                             "background-color:qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0.368182 rgba(100,100,100,75))}");
    maxBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(maxBtn,&QPushButton::clicked,this,&Chat_Ui::on_titleBtn_clicked);

    minBtn = new QPushButton;
    minBtn->setIcon(QIcon(":/Chat/image/Min.svg"));
    minBtn->setToolTip("最小化");
    minBtn->setFixedSize(QSize(25,25));
    minBtn->setStyleSheet("QPushButton{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;color:#D6D6D6}"
                             "QPushButton:hover{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;"
                             "background-color:qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0.368182 rgba(198,198,198,75))}"
                             "QPushButton:pressed{border-left:0px;border-right:0px;border-top:0px;border-bottom:0px;width:35px;height:35px;"
                             "background-color:qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0.368182 rgba(100,100,100,75))}");
    minBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(minBtn,&QPushButton::clicked,this,&Chat_Ui::on_titleBtn_clicked);

    QHBoxLayout * head_hlay = new QHBoxLayout;
    head_hlay->addStretch();
    head_hlay->addWidget(minBtn);
    head_hlay->addWidget(maxBtn);
    head_hlay->addWidget(closeBtn);

    head_hlay->setSpacing(10);
    head_hlay->setMargin(0);
    QWidget *widHead = new QWidget;
    widHead ->setLayout(head_hlay);
    widHead->setStyleSheet("QWidget{background-color:#fafafa}");
    widHead->setFixedHeight(25);

    vblay_right = new QVBoxLayout;
    vblay_right->addWidget(widHead);
    vblay_right->setMargin(0);

    QPointer<QWidget> ptrCardWid(new QWidget);
    ptrMessWid = new QStackedWidget;
    ptrCardWid->setLayout(vlay_card);
    right_stackWidget = new QStackedWidget;
    right_stackWidget->addWidget(ptrMessWid);
    right_stackWidget->addWidget(ptrCardWid);
    vblay_right->addWidget(right_stackWidget);


    QWidget * widR = new QWidget;
    widR->setStyleSheet("QWidget{background-color:#fafafa}");
    widR->setLayout(vblay_right);
    QVBoxLayout * vblayRight = new QVBoxLayout;
    vblayRight->addWidget(widR);
    return vblayRight;
}
QPixmap Chat_Ui::pixmapToRound(QPixmap &src, int radius)
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
    painter.drawRoundedRect(0, 0, size.width(), size.height(),30, 30);

    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}
QPushButton* Chat_Ui::getHeadImg(QString src)
{
    QPixmap pixmap_userIcon;
    pixmap_userIcon.load(src);
    QPixmap fitpixmap_userIcon=pixmap_userIcon.scaled(45, 45, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPushButton *headimg = new QPushButton;
    headimg->setFixedSize(37,37);
    headimg->setIcon(fitpixmap_userIcon);
    headimg->setIconSize(QSize(37,37));
    headimg->setObjectName("headimg");
    headimg->setStyleSheet("QPushButton{border-width:1px; border-color:#ccc ;border-style:solid;}"
                           "QPushButton:hover{border-width:1px; border-color:#7EC0EE ;border-style:solid;}");
    return headimg;
}
void Chat_Ui::mousePressEvent(QMouseEvent *event)
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

void Chat_Ui::on_titleBtn_clicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == minBtn)
        {
            pWindow->showMinimized();
        }
        else if (pButton == maxBtn)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
            pWindow->isMaximized() ? maxBtn->setIcon(QIcon(":/Chat/image/Min_Streth.svg")) : maxBtn->setIcon(QIcon(":/Chat/image/Max_Streth.svg"));
            if(pWindow->isMaximized())
            {
                main_layout->setStretch(1,2);
                main_layout->setStretch(2,8);

            }else
            {
                main_layout->setStretch(0,1);
                main_layout->setStretch(1,4);
                main_layout->setStretch(2,7);
            }
        }
        else if (pButton == closeBtn)
        {
            pWindow->close();
        }

    }
}
bool Chat_Ui::eventFilter(QObject * watched,QEvent *event)
{
    if(watched == leftList[0])
    {
        if(event->type() == QEvent::HoverEnter)
        {
            leftList[0]->verticalScrollBar()->show();
        }
        if(event->type() == QEvent::HoverLeave)
        {
            leftList[0]->verticalScrollBar()->hide();
        }
    }
    if(watched == leftList[1])
    {
        if(event->type() == QEvent::HoverEnter)
        {
            leftList[1]->verticalScrollBar()->show();
        }
        if(event->type() == QEvent::HoverLeave)
        {
            leftList[1]->verticalScrollBar()->hide();
        }
    }
    if(watched == chatBtn)
    {
        if(QEvent::FocusIn == event->type())
        {
            chatBtn->setIcon(QIcon(":/Chat/image/ChatFocus.svg"));
            left_stackWidget->setCurrentIndex(0);
            right_stackWidget->setCurrentIndex(0);
            messBtn->setIcon(QIcon(":/Chat/image/ChatBook.svg"));
            moreBtn->setIcon(QIcon(":/Chat/image/More.svg"));
        }
        if(QEvent::HoverEnter == event->type())
        {
            chatBtn->setCursor(QCursor(Qt::PointingHandCursor));
        }else if(QEvent::HoverLeave == event->type())
        {
            chatBtn->setCursor(QCursor(Qt::ArrowCursor));
        }
    }else if (watched == messBtn)
    {
        if(QEvent::FocusIn == event->type())
        {
           messBtn->setIcon(QIcon(":/Chat/image/ChatBookFocus.svg"));
           left_stackWidget->setCurrentIndex(1);
           right_stackWidget->setCurrentIndex(1);
           moreBtn->setIcon(QIcon(":/Chat/image/More.svg"));
           chatBtn->setIcon(QIcon(":/Chat/image/Chat.svg"));
        }
        if(QEvent::HoverEnter == event->type())
        {
            messBtn->setCursor(QCursor(Qt::PointingHandCursor));
        }else if(QEvent::HoverLeave == event->type())
        {
            messBtn->setCursor(QCursor(Qt::ArrowCursor));
        }
    }else if (watched == moreBtn)
    {
        if(QEvent::FocusIn == event->type())
        {
            moreBtn->setIcon(QIcon(":/Chat/image/MoreFocus.svg"));
            messBtn->setIcon(QIcon(":/Chat/image/ChatBook.svg"));
            chatBtn->setIcon(QIcon(":/Chat/image/Chat.svg"));
        }
        if(QEvent::HoverEnter == event->type())
        {
            moreBtn->setCursor(QCursor(Qt::PointingHandCursor));
        }else if(QEvent::HoverLeave == event->type())
        {
            moreBtn->setCursor(QCursor(Qt::ArrowCursor));
        }
    }else if(watched == headimg)
    {
        if(QEvent::HoverEnter == event->type())
        {
            headimg->setCursor(QCursor(Qt::PointingHandCursor));
        }else if(QEvent::HoverLeave == event->type())
        {
            headimg->setCursor(QCursor(Qt::ArrowCursor));
        }
    }else if(watched == searchEdit)
    {
        if(QEvent::FocusIn == event->type())
        {
            searchEdit->setStyleSheet("QLineEdit{background-color:white;border-color:#cfcfcf;border-radius:3px;}");
            left_stackWidget->setCurrentIndex(2);
        }else if(QEvent::FocusOut == event->type())
        {
            searchEdit->setStyleSheet("QLineEdit{border-style:none;background-color:rgba(190,190,190,0.5);border-radius:3px;}");
        }
    }
    return false;

}
void Chat_Ui::messItemClicked(int row)
{
    request_friendAddr(vec_friends[row].friend_email);
    m_messRow = row;
    if(map_mess.count(row) == 0)
    {
        unsigned r = static_cast<unsigned>(row);
        QPointer<PerMsg> ptrPerMess(new PerMsg(m_self_email,vec_friends[r].friend_name,vec_friends[r].friend_email));
        //或消息发送成功，则判断列表中是否存在;
        connect(ptrPerMess,&PerMsg::on_sendMessSuss,this,[&](const QString& nick_name,const QString& mess)
        {
            left_stackWidget->setCurrentIndex(0);
            int tmp = find_perIsVisual(nick_name);
            QPixmap headimg(":/Chat/image/head.jpg");
            QDateTime time = QDateTime::currentDateTime();
            //若不存在;
            if(tmp < 0)
            {
                QListWidgetItem * item = new QListWidgetItem(leftList[0]);
                FriendsList * ptr_fri = new FriendsList(headimg,nick_name,mess,time.toString("hh:mm"));
                leftList[0]->addItem(item);
                item->setSizeHint(QSize(210,60));
                leftList[0]->setItemWidget(item,ptr_fri->getWidget());
                vec_mess.insert({m_mess_count_,m_messRow});
                m_mess_count_++;
            }else{
                QListWidgetItem * item = leftList[0]->item(tmp);
                FriendsList * ptr_fri = new FriendsList(headimg,nick_name,mess,time.toString("hh:mm"));
                leftList[0]->addItem(item);
                item->setSizeHint(QSize(210,60));
                leftList[0]->setItemWidget(item,ptr_fri->getWidget());
            }
             left_stackWidget->setCurrentIndex(0);
             chatBtn->setIcon(QIcon(":/Chat/image/ChatFocus.svg"));
             messBtn->setIcon(QIcon(":/Chat/image/ChatBook.svg"));
             searchEdit->clear();
        });
        ptrMessWid->addWidget(ptrPerMess);
        map_mess.insert({row,m_map_count});
        ptrMessWid->setCurrentIndex(m_map_count);
        map.insert({r,m_map_count});
        m_map_count++;
    }else{
        ptrMessWid->setCurrentIndex(map_mess[row]);
    }

    /*
    connect(ptrPerMess,&PerMsg::on_saveChatRecord,this,&Chat_Ui::save_chatRecord);
    connect(ptrPerMess,&PerMsg::on_getChatRecord,this,[&](const QString& user)
    {
        findVector vec = m_sql.search_data(user);
        for(auto it = vec.begin(); it != vec.end();++it)
        {
            qDebug()<<(*it).first.first<<(*it).first.second<<(*it).second.first<<(*it).second.second;
        }
    });
    */
}
void Chat_Ui::friendsGroup_list()
{
    auto size = vec_friends.size();
    if(size < 1)
        return;
    QListWidgetItem **item = new QListWidgetItem*[size];

    QPixmap headimg(":/Chat/image/head.jpg");
    for(unsigned i = 0;i < size;++i)
    {
        QPointer<friends> ptr_friend = new friends(headimg,vec_friends[i].friend_name);
        item[i] = new QListWidgetItem();
        item[i]->setSizeHint(QSize(210,60));

        leftList[1]->addItem(item[i]);
        leftList[1]->setItemWidget(item[i],ptr_friend->getWidget());
    }
    vlay_card = new QVBoxLayout;
    connect(leftList[1],&QListWidget::currentRowChanged,this,&Chat_Ui::listItemClicked);
}
void Chat_Ui::listItemClicked(int row)
{
    QLayoutItem * item;
    while((item = vlay_card->takeAt(0)) != nullptr)
    {
        if(item->widget())
        {
            delete item->widget();
        }
        delete item;
    }
    right_stackWidget->setCurrentIndex(1);
    QString key[] = {"friend_name","friend_remark","friend_email"};
    std::vector<QString> index;
    unsigned r = static_cast<unsigned>(row);

    index.push_back(vec_friends[r].friend_name);
    index.push_back(vec_friends[r].nick_name);
    index.push_back(vec_friends[r].friend_email);

    QPixmap headimg(":/Chat/image/head.jpg");
    std::map<QString,QString> map;
    unsigned i;
    for(i = 0;i < 3;++i)
    {
        map.insert(std::pair<QString,QString>(key[i],index[i]));
    }
    QPointer<PerCard> ptr_perCard(new PerCard(headimg,m_self_email,map));
    vlay_card->addWidget(ptr_perCard);
    connect(ptr_perCard,&PerCard::sendMess_onClicked,this,[&]()
    {
        right_stackWidget->setCurrentIndex(0);
        messItemClicked(leftList[1]->currentRow());
    });
}
void Chat_Ui::find_result(const QString& text)
{
    if(text.isEmpty() || vec_friends.empty())
        return;
    unsigned size = static_cast<unsigned>(vec_friends.size());
    leftList[2]->clear();
    if(!vec_findList.empty())
        vec_findList.clear();
    bool flag  = false;
    int n,count = 0;
    unsigned i = 0;
    while(i < size )
    {
        QString str = vec_friends[i].friend_name;
        n = str.indexOf(text);
        if(n != -1)
        {
            QPixmap headimg(":/Chat/image/head.jpg");
            QListWidgetItem *item = new QListWidgetItem;
            item->setSizeHint(QSize(210,60));
            item->setIcon(headimg);
            item->setText(str);
            item->setFont(QFont("Consolas",11));
            leftList[2]->addItem(item);
            flag = true;
            vec_findList.insert({count,i});
            count++;
        }
        i++;
   }
    if(flag == false)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setText("没有搜索到相关内容");
        item->setTextAlignment(Qt::AlignCenter);
        leftList[2]->addItem(item);
    }
}
void Chat_Ui::send_LoginStatus()
{
    UDP::MSG msg;
    memset(&msg,0,sizeof (msg));
    msg.type = UDP::LOGIN;
    strcpy(msg.send_user,m_self_email.toUtf8().data());
    char send_msg[sizeof(msg)] = {0};
    memcpy(send_msg,&msg,sizeof(msg));
    //Udp m_udp;
    if(common("47.106.14.185",5500) == false)
        return;
    bool status =  sento_message(send_msg,sizeof(send_msg));
    if(!status)
    {
        return;
    }
}

void Chat_Ui::save_chatRecord(const QString& self,const std::pair<QString,QString>& f_pair,const QString& str,const QString& time)
{
    m_sql.insert_data(self,f_pair,str,time);
}
void Chat_Ui::recv_newMessage(const UDP::MSG& msg)
{
    if(msg.type == UDP::CHAT)
    {
        if(m_self_email.compare(msg.recv_user) == 0)
        {
            qDebug()<<"msg to myself";
            common("127.0.0.1",5501);
        }
        else
        {
            qDebug()<<"msg to others";
            char * ip = inet_ntoa(msg.addr.sin_addr);
            common("192.168.1.100",5501);
        }
        //common(ip,5501);
        return;
        /*
        if(msg.status == UDP::ONLINE)
        {

         servAddr.sin_addr.S_un.S_addr = inet_addr(msg.site_ip);
         servAddr.sin_port = htons(5501);
        }else if(msg.status == UDP::NOT_ONLINE){
            servAddr.sin_addr.S_un.S_addr = inet_addr("47.106.14.185");
            servAddr.sin_port = htons(5500);
        }
        return;
        */
    }
    int flag = find_PerIndex(QString(msg.send_user));
    if(flag < 0)
        return;
    //查找好友在聊天列表中是否存在，
    int tmp = find_perIsVisual(QString(vec_friends[flag].friend_name));
    QPixmap headimg(":/Chat/image/head.jpg");
    QDateTime time = QDateTime::currentDateTime();
    if(tmp < 0)
    {
        QListWidgetItem * item = new QListWidgetItem(leftList[0]);
        FriendsList * ptr_fri = new FriendsList(headimg,QString(vec_friends[static_cast<size_t>(flag)].friend_name),QString(msg.send_char),time.toString("hh:mm"));
        leftList[0]->addItem(item);
        item->setSizeHint(QSize(210,60));
        leftList[0]->setItemWidget(item,ptr_fri->getWidget());
        vec_mess.insert({m_mess_count_,flag});

        /* 修改部分*/
        PerMsg * ptr_perMsg = new PerMsg(m_self_email,vec_friends[flag].friend_name,msg.send_user);
        connect(ptr_perMsg,&PerMsg::on_sendMessSuss,this,[&](const QString& nick_name,const QString& mess)
        {
            int f = find_perIsVisual(nick_name);
            QPixmap headimg(":/Chat/image/head.jpg");
            QDateTime m_t = QDateTime::currentDateTime();
            QListWidgetItem * item = leftList[0]->item(f);
            FriendsList * ptr_fri = new FriendsList(headimg,nick_name,mess,m_t.toString("hh:mm"));
            leftList[0]->addItem(item);
            item->setSizeHint(QSize(210,60));
            leftList[0]->setItemWidget(item,ptr_fri->getWidget());
            left_stackWidget->setCurrentIndex(0);
        });
        QNChatMessage* messageW = new QNChatMessage(ptr_perMsg->get_listWidget()->parentWidget());
        QListWidgetItem* item_mess = new QListWidgetItem(ptr_perMsg->get_listWidget());
        ptr_perMsg->dealMessage(messageW,item_mess,headimg,msg.send_char,time.toString("yy:MM:dd hh:mm:ss"),QNChatMessage::User_Other);
        ptrMessWid->addWidget(ptr_perMsg);
        map_mess.insert({m_mess_count_,m_map_count});
        map.insert({flag,m_map_count});
        m_map_count++;
        /* 修改部分*/

        m_mess_count_++;
    }else{
        QListWidgetItem * item = leftList[0]->item(tmp);
        FriendsList * ptr_fri = new FriendsList(headimg,QString(vec_friends[static_cast<size_t>(flag)].friend_name),QString(msg.send_char),time.toString("hh:mm"));
        leftList[0]->addItem(item);
        item->setSizeHint(QSize(210,60));
        leftList[0]->setItemWidget(item,ptr_fri->getWidget());

        /*修改部分*/
        int r = map[vec_mess[tmp]];
        QWidget * ptrWid = ptrMessWid->widget(r);

        QList<QListWidget *> list = ptrWid->findChildren<QListWidget *>("listWidget");
        foreach(QListWidget * it,list)
        {

            QNChatMessage* messageW = new QNChatMessage(it->parentWidget());
            QListWidgetItem* item_mess = new QListWidgetItem(it);
            messageW->setFixedWidth(it->width());
            QSize size = messageW->fontRect(msg.send_char);
            item_mess->setSizeHint(size);
            messageW->setText(headimg,msg.send_char, time.toString("yy:MM:dd hh:mm:ss"), size, QNChatMessage::User_Other);
            it->setItemWidget(item_mess, messageW);
            it->scrollToBottom();
        }

       /*修改部分 */
    }
}
int Chat_Ui::find_PerIndex(const QString &email)
{
    auto size = vec_friends.size();
    unsigned i ;
    for( i = 0;i < size; ++i)
    {
        if(QString(vec_friends[i].friend_email) == email)
        {
            return static_cast<int>(i);
        }
    }
    return  -1;
}
int Chat_Ui::find_perIsVisual(const QString& nick_name)
{
    int count = leftList[0]->count();
    int i = 0;
    while(i < count)
    {
        QListWidgetItem * item = leftList[0]->item(i);
        QWidget * ptr_wid = leftList[0]->itemWidget(item);

        QList<QLabel *> list = ptr_wid -> findChildren<QLabel *>("nick_name");
        foreach(QLabel * it,list)
        {
            if(it ->text() == nick_name)
                return i;
        }
        i++;
    }
    return  -1;
}
void Chat_Ui::request_friendAddr(const QString& friend_email)
{
    qDebug()<<"request to"<<friend_email;
    if(servAddr.sin_port != htons(5500))
    {
        common("47.106.14.185",5500);
        qDebug()<<"common to server";
    }
    UDP::MSG pack;
    memset(&pack,0,sizeof (pack));
    pack.type = UDP::CHAT;
    strcpy(pack.send_user,m_self_email.toUtf8().data());
    strcpy(pack.recv_user,friend_email.toUtf8().data());
    char send[sizeof (pack)] = {0};
    memcpy(send,&pack,sizeof (pack));
    bool flag =  sento_message(send,sizeof (pack));
    if(!flag)
    {
        qDebug()<<"request send failed";
    }
}



