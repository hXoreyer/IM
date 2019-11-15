#include "feedback.h"

FeedBack::FeedBack(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(QSize(360,224));
    closeBtn = new QPushButton;
    closeBtn->setIcon(QIcon(":/image/Close.svg"));
    closeBtn->setToolTip("关闭");
    closeBtn->setIconSize(QSize(15,15));
    closeBtn->setFixedSize(QSize(20,20));
    closeBtn->setFlat(true);
    closeBtn->setStyleSheet("QPushButton{border-style:none}"
                            "QPushButton:hover{background-color:red;border-style:none}");
    connect(closeBtn,&QPushButton::clicked,this,[&]()
    {
        this->close();
    });

    QHBoxLayout * hlay_head = new QHBoxLayout;
    hlay_head->addStretch();
    hlay_head->addWidget(closeBtn);

    text = new QTextEdit;
    text->setPlaceholderText("内容不得多于150个字...");
    text->setStyleSheet("QTextEdit{background-color:white;padding:10px;}");
    QVBoxLayout * vlay_text = new QVBoxLayout;
    vlay_text->addWidget(text);
    vlay_text->setMargin(10);

    sendBtn = new QPushButton("确定");
    sendBtn->setStyleSheet("QPushButton{border-radius:3px;background-color:#008B00;border-style:none;color:white}"
                           "QPushButton:hover{background-color:#00CD66;color:white}");
    sendBtn->setFixedSize(QSize(70,26));
    cancelBtn = new QPushButton("取消");
    cancelBtn->setStyleSheet("QPushButton{border-radius:3px;background-color:#8B8682;border-style:none;color:white}"
                           "QPushButton:hover{background-color:	#8B7D6B;color:white}");
    connect(cancelBtn,&QPushButton::clicked,this,[&]()
    {
        this->close();
    });
    cancelBtn->setFixedSize(QSize(70,26));
    QHBoxLayout * hlay_btn = new QHBoxLayout;
    hlay_btn->addStretch();
    hlay_btn->addWidget(sendBtn);
    hlay_btn->addWidget(cancelBtn);
    hlay_btn->setSpacing(10);
    hlay_btn->setContentsMargins(0,0,10,10);

    main_vlay = new QVBoxLayout(this);
    main_vlay->addLayout(hlay_head);
    main_vlay->addLayout(vlay_text);
    main_vlay->addLayout(hlay_btn);
    main_vlay->setMargin(0);
    setLayout(main_vlay);
}
void FeedBack::mousePressEvent(QMouseEvent *event)
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
