#include "chatrecord.h"
ChatRecord::ChatRecord(const QString& m_name,QWidget *parent)
    :QWidget(parent),m_tittle(m_name)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setStyleSheet("background-color:#fafafa");
    setFixedSize(QSize(550,600));
    main_vlay = new QVBoxLayout(this);
    main_vlay->addLayout(addToolItem());
    main_vlay->addLayout(addWidget());
    main_vlay->addStretch();
    main_vlay->setMargin(0);
    setLayout(main_vlay);
}
QLayout* ChatRecord::addToolItem()
{
    m_tittleBtn = new QLabel;
    m_tittleBtn->setText("  "+m_tittle);
    m_tittleBtn->setFont(QFont("Microsoft YaHei",10));
    m_tittleBtn->setStyleSheet("QLabel{color:#8B8989}");

    m_cloBtn = new QPushButton;
    m_cloBtn->setIcon(QIcon(":/Chat/image/Close.svg"));
    m_cloBtn->setIconSize(QSize(16,16));
    m_cloBtn->setFixedSize(QSize(25,25));
    m_cloBtn->setFlat(true);
    m_cloBtn->setStyleSheet("QPushButton{border-style:none}"
                            "QPushButton:hover{border-style:none;background-color:red}");
    connect(m_cloBtn,&QPushButton::clicked,this,[&]()
    {
        this->close();
    });

    m_minBtn = new QPushButton;
    m_minBtn->setIcon(QIcon(":/Chat/image/Min.svg"));
    m_minBtn->setIconSize(QSize(16,16));
    m_minBtn->setFixedSize(QSize(25,25));
    m_minBtn->setFlat(true);
    m_minBtn->setStyleSheet("QPushButton{border-style:none}"
                            "QPushButton:hover{border-style:none;background-color:#BEBEBE}"
                            "QPushButton:visited{border-style:none}");
    connect(m_minBtn,&QPushButton::clicked,this,[&]()
    {
        this->showMinimized();
    });

    QHBoxLayout * hlay = new QHBoxLayout;
    QHBoxLayout * left_hlay = new QHBoxLayout;
    QHBoxLayout * right_hlay = new QHBoxLayout;
    left_hlay->addWidget(m_tittleBtn);
    right_hlay->addWidget(m_minBtn);
    right_hlay->addWidget(m_cloBtn);
    hlay->addLayout(left_hlay);
    hlay->addStretch();
    hlay->addLayout(right_hlay);
    hlay->setMargin(0);
    return hlay;
}

void ChatRecord::mousePressEvent(QMouseEvent *event)
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
QLayout* ChatRecord::addWidget()
{
    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("搜索");
    QAction* searAct = new QAction;
    searAct->setIcon(QIcon(":/Chat/image/Search.svg"));
    searchEdit->addAction(searAct,QLineEdit::LeadingPosition);
    searchEdit->setFixedHeight(25);
    searchEdit->setFont(QFont("Consolas",9));
    searchEdit->setStyleSheet("QLineEdit{border-style:none;background-color:rgba(190,190,190,0.5);border-radius:5px;}"
                              "QLineEdit:focus{background-color:white}");
    //connect(searchEdit,&QLineEdit::textChanged,this,&Chat_Ui::find_result);
    QHBoxLayout * ptr_toolhlay = new QHBoxLayout;
    std::vector<QString> m_vec = {"全部","文件","图片与视频","链接"};
    ptr_toolhlay->addStretch();
    for(unsigned i = 0;i < 4;++i)
    {
        ptr_toolBtn[i] = new QPushButton(m_vec[i]);
        ptr_toolBtn[i]->setFont(QFont("Microsoft YaHei",12));
        ptr_toolBtn[i]->setFlat(true);
        ptr_toolBtn[i]->setStyleSheet("QPushButton{border-style:none}");
        connect(ptr_toolBtn[i],&QPushButton::clicked,this,[&]()
        {
            //ptr_toolBtn[i]->setStyleSheet("QPushButton{border-style:none;color:green}");
        });
        ptr_toolBtn[i]->installEventFilter(this);
        ptr_toolhlay->addWidget(ptr_toolBtn[i]);
    }
    ptr_toolhlay->addStretch();
    ptr_toolhlay->setSpacing(38);

    QVBoxLayout * vlay = new QVBoxLayout;
    vlay->addWidget(searchEdit);
    vlay->addLayout(ptr_toolhlay);
    vlay->setMargin(50);
    vlay->setSpacing(20);
    return vlay;
}
bool ChatRecord::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ptr_toolBtn[0])
    {
        if(watched == ptr_toolBtn[0])
        {
            if(event->type() == QEvent::FocusIn)
            {
                ptr_toolBtn[0]->setStyleSheet("QPushButton{border-style:none;color:green}");
            }
            if(event->type() == QEvent::FocusOut)
            {
                ptr_toolBtn[0]->setStyleSheet("QPushButton{border-style:none;color:#000}");
            }
        }
        if(QEvent::HoverEnter == event->type())
        {
            ptr_toolBtn[0]->setCursor(QCursor(Qt::PointingHandCursor));
        }else if(QEvent::HoverLeave == event->type())
        {
            ptr_toolBtn[0]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }else if(watched == ptr_toolBtn[1])
    {
        if(event->type() == QEvent::FocusIn)
        {
            ptr_toolBtn[1]->setStyleSheet("QPushButton{border-style:none;color:green}");
        }
        if(event->type() == QEvent::FocusOut)
        {
            ptr_toolBtn[1]->setStyleSheet("QPushButton{border-style:none;color:#000}");
        }
        if(QEvent::HoverEnter == event->type())
        {
            ptr_toolBtn[1]->setCursor(QCursor(Qt::PointingHandCursor));
        }else if(QEvent::HoverLeave == event->type())
        {
            ptr_toolBtn[1]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }else if(watched == ptr_toolBtn[2])
    {
        if(event->type() == QEvent::FocusIn)
        {
            ptr_toolBtn[2]->setStyleSheet("QPushButton{border-style:none;color:green}");
        }
        if(event->type() == QEvent::FocusOut)
        {
            ptr_toolBtn[2]->setStyleSheet("QPushButton{border-style:none;color:#000}");
        }
        if(QEvent::HoverEnter == event->type())
        {
            ptr_toolBtn[2]->setCursor(QCursor(Qt::PointingHandCursor));
        }else if(QEvent::HoverLeave == event->type())
        {
            ptr_toolBtn[2]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }else if(watched == ptr_toolBtn[3])
    {
        if(event->type() == QEvent::FocusIn)
        {
            ptr_toolBtn[3]->setStyleSheet("QPushButton{border-style:none;color:green}");
        }
        if(event->type() == QEvent::FocusOut)
        {
            ptr_toolBtn[3]->setStyleSheet("QPushButton{border-style:none;color:#000}");
        }
        if(QEvent::HoverEnter == event->type())
        {
            ptr_toolBtn[3]->setCursor(QCursor(Qt::PointingHandCursor));
        }else if(QEvent::HoverLeave == event->type())
        {
            ptr_toolBtn[3]->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    return false;
}
void ChatRecord::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor("#F5F5F5"));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(0,163,550,163);
}
