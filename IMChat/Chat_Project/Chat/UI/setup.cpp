#include "setup.h"

SetUp::SetUp(QWidget *parent) : QWidget(parent)
{
    setFixedSize(QSize(550,470));
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("QWidget{background-color:#f5f5f5}");



    mainLay = new QVBoxLayout;
    mainLay ->addLayout(toptoolBar());
    mainLay->addLayout(funUi_list());
    mainLay->setMargin(0);
    setLayout(mainLay);

    account_setting();
    general_setting();
    shortcutKey_setting();
    version_setting();
}
QLayout* SetUp::toptoolBar()
{
    minBtn = new QPushButton;
    cloBtn = new QPushButton;

    minBtn->setFixedSize(30,30);
    cloBtn->setFixedSize(30,30);

    minBtn->setToolTip("最小化");
    cloBtn->setToolTip("关闭");

    QPixmap min_ico(":/image/Min.svg");
    QPixmap close_ico(":/image/Close.svg");
    minBtn->setIcon(min_ico);
    minBtn->setFlat(true);
    cloBtn->setFlat(true);
    cloBtn->setIcon(close_ico);
    minBtn->setFixedSize(QSize(30,30));
    cloBtn->setFixedSize(QSize(30,30));
    minBtn->setStyleSheet("QPushButton:hover{background-color:#BEBEBE;border-style:none}");
    cloBtn->setStyleSheet("QPushButton:hover{background-color:red;border-style:none}");

    QHBoxLayout* tittle_lay = new QHBoxLayout;
    QLabel* tittle = new QLabel("   设置");
    tittle->setStyleSheet("QLabel{color:#CDC5BF}");
    tittle->setFont(QFont("Microsoft YaHei",11));
    tittle_lay->addWidget(tittle);
    tittle_lay->addStretch();
    tittle_lay->addWidget(minBtn);
    tittle_lay->addWidget(cloBtn);
    tittle_lay->setMargin(0);
    tittle_lay->setSpacing(0);

    connect(cloBtn,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(minBtn,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    return tittle_lay;

}
void SetUp::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == minBtn)
        {
            pWindow->showMinimized();
        }
        else if (pButton == cloBtn)
        {
            pWindow->close();
        }
    }
}
void SetUp::mousePressEvent(QMouseEvent *event)
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
QLayout * SetUp::funUi_list()
{
    QVBoxLayout * vlay_left = new QVBoxLayout;
    QVBoxLayout * vlay_right = new QVBoxLayout;
    stackWidget = new QStackedWidget;
    std::vector<QString> vec = {"账号设置","通用设置","快捷按键","关于我们"};
    unsigned i;
    for(i = 0; i< 4; ++i)
    {
        setBtn[i] = new QPushButton(vec[i]);
        setBtn[i]->setFlat(true);
        setBtn[i]->setFixedHeight(25);
        setBtn[i]->setStyleSheet("QPushButton{border-style:none}");
        setBtn[i]->setFont(QFont("Microsoft YaHei",10,QFont::Bold));
        vlay_left->addWidget(setBtn[i]);
        setWid[i] = new QWidget;
        stackWidget->addWidget(setWid[i]);
    }
    setBtn[0]->setStyleSheet("QPushButton{color:#00CD00}");
    connect(setBtn[0],&QPushButton::clicked,this,&SetUp::on_BtnClicked_first);
    connect(setBtn[1],&QPushButton::clicked,this,&SetUp::on_BtnClicked_second);
    connect(setBtn[2],&QPushButton::clicked,this,&SetUp::on_BtnClicked_thrid);
    connect(setBtn[3],&QPushButton::clicked,this,&SetUp::on_BtnClicked_four);
    vlay_left->setContentsMargins(15,50,0,0);
    vlay_left->addStretch();
    vlay_right->addWidget(stackWidget);
    QHBoxLayout *hlay = new QHBoxLayout;
    hlay->addLayout(vlay_left,1);
    hlay->addLayout(vlay_right,5);
    return hlay;
}
void SetUp::on_BtnClicked_first()
{
    setBtn[0]->setStyleSheet("QPushButton{color:#00CD00;border-style:none}");
    setBtn[1]->setStyleSheet("QPushButton{color:black;border-style:none}");
    setBtn[2]->setStyleSheet("QPushButton{color:black;border-style:none}");
    setBtn[3]->setStyleSheet("QPushButton{color:black;border-style:none}");
    stackWidget->setCurrentIndex(0);
}
void SetUp::on_BtnClicked_second()
{
    setBtn[1]->setStyleSheet("QPushButton{color:#00CD00;border-style:none}");
    setBtn[0]->setStyleSheet("QPushButton{color:black;border-style:none}");
    setBtn[2]->setStyleSheet("QPushButton{color:black;border-style:none}");
    setBtn[3]->setStyleSheet("QPushButton{color:black;border-style:none}");
    stackWidget->setCurrentIndex(1);
}
void SetUp::on_BtnClicked_thrid()
{
    setBtn[2]->setStyleSheet("QPushButton{color:#00CD00;border-style:none}");
    setBtn[0]->setStyleSheet("QPushButton{color:black;border-style:none}");
    setBtn[1]->setStyleSheet("QPushButton{color:black;border-style:none}");
    setBtn[3]->setStyleSheet("QPushButton{color:black;border-style:none}");
    stackWidget->setCurrentIndex(2);
}
void SetUp::on_BtnClicked_four()
{
    setBtn[3]->setStyleSheet("QPushButton{color:#00CD00;border-style:none}");
    setBtn[0]->setStyleSheet("QPushButton{color:black;border-style:none}");
    setBtn[1]->setStyleSheet("QPushButton{color:black;border-style:none}");
    setBtn[2]->setStyleSheet("QPushButton{color:black;border-style:none}");
    stackWidget->setCurrentIndex(3);
}
void SetUp::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor("#CDCDC1"));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(95,94,95,468);
}

void SetUp::account_setting()
{
    QVBoxLayout * vblay_head = new QVBoxLayout;

     head =  new QPushButton;
     head->setIcon(QIcon(":/image/head.jpg"));
     head->setStyleSheet("QPushButton{border-style:none;border-radius:3px;}");
     head->setFixedSize(QSize(100,100));
     head->setIconSize(QSize(100,100));
     QHBoxLayout * hlay_head = new QHBoxLayout;
     hlay_head->addStretch();
     hlay_head->addWidget(head);
     hlay_head->addStretch();
     vblay_head->addLayout(hlay_head);


     petName = new QLabel;
     petName->setText("备注");
     petName->setFont(QFont("Microsoft YaHei",11));
     QHBoxLayout *hlay_Name = new QHBoxLayout;
     hlay_Name->addStretch();
     hlay_Name->addWidget(petName);
     hlay_Name->addStretch();
     vblay_head->addLayout(hlay_Name);


     accountLabel = new QLabel;
     accountLabel->setText("账号:");
     accountLabel->setFont(QFont("Microsoft YaHei",11));
     account = new QLabel;
     account->setText("1724236802@qq.com");
     account->setFont(QFont("Microsoft YaHei",11));
     QHBoxLayout *  hlay_account = new QHBoxLayout;
     hlay_account->addStretch();
     hlay_account->addWidget(accountLabel);
     hlay_account->addWidget(account);
     hlay_account->addStretch();
     hlay_account->setSpacing(10);
     vblay_head->addLayout(hlay_account);

     logOff = new QPushButton("退出登录");
     logOff->setFont(QFont("Microsoft YaHei",11));
     logOff->setFixedSize(QSize(120,30));
     logOff->setStyleSheet("QPushButton{background-color:#BEBEBE;border-style:none;border-radius:3px;}"
                           "QPushButton:hover{background-color:#D3D3D3}"
                           "QPushButton:pressed{background-color:#00CD00;color:white}");
     QHBoxLayout * hlay_logOff = new QHBoxLayout;
     hlay_logOff->addStretch();
     hlay_logOff->addWidget(logOff);
     hlay_logOff->addStretch();
     vblay_head->addStretch();
     vblay_head->addLayout(hlay_logOff);

     vblay_head->setContentsMargins(100,50,100,160);
     vblay_head->setSpacing(10);
     setWid[0]->setLayout(vblay_head);

}
void SetUp::general_setting()
{
    QVBoxLayout * vlay_left = new QVBoxLayout;
    QVBoxLayout * vlay_right = new QVBoxLayout;

    std::vector<QString> vec_left = {"文件管理","通用"};
    QLabel * labLeft[2];
    unsigned i;
    for(i = 0;i < 2;++i)
    {
        labLeft[i] = new QLabel(vec_left[i]);
        labLeft[i]->setFont(QFont("Microsoft YaHei",11));
        vlay_left->addWidget(labLeft[i]);
    }
    vlay_left->addStretch();
    vlay_left->setSpacing(117);

    filePath = new QLineEdit;
    filePath->setFixedSize(QSize(200,25));
    filePath -> setStyleSheet("QLineEdit{background-color:white;border-style:none}");
    filePath->setText("C:\\Program Files\\IM Files\\");
    filePath->setFont(QFont("Microsoft YaHei",11));
    std::vector<QString> vecBtn = {"更改","打开文件夹"};
    QHBoxLayout * hlay_file = new QHBoxLayout;
    for(i = 0;i < 2;++i)
    {
        fileBtn[i] = new QPushButton(vecBtn[i]);
        fileBtn[i]->setFont(QFont("Microsoft YaHei",11));
        fileBtn[i]->setFixedSize(QSize(105,25));
        fileBtn[i]->setStyleSheet("QPushButton{background-color:#BEBEBE;border-style:none;border-radius:3px;}"
                              "QPushButton:hover{background-color:#D3D3D3}"
                              "QPushButton:pressed{background-color:#00CD00;color:white}");
        hlay_file->addWidget(fileBtn[i]);
    }
    QLabel *labFile = new QLabel("文件的默认保存位置");
    labFile->setFont(QFont("Microsoft YaHei",10));
    QVBoxLayout * vlay_file = new QVBoxLayout;
    vlay_file->addWidget(filePath);
    vlay_file->addWidget(labFile);
    vlay_file->addLayout(hlay_file);
    vlay_file->setMargin(0);
    vlay_file->setSpacing(5);
    vlay_right->addLayout(vlay_file);

    QVBoxLayout * vlay_box = new QVBoxLayout;
    std::vector<QString> vecBox = {"开启新消息提醒声音","开启语音和视频通话提醒声音","有更新时自动升级版本","开机时自动启动"};
    for(i = 0;i < 4;++i)
    {
        generalCheck[i] = new QCheckBox(vecBox[i]);
        generalCheck[i]->setFont(QFont("Microsoft YaHei",11));
        vlay_box->addWidget(generalCheck[i]);

    }
    vlay_box->setSpacing(10);
    vlay_box->setContentsMargins(0,50,0,0);
    vlay_right->addLayout(vlay_box);
    vlay_right->addStretch();
    QHBoxLayout * mainLay_general = new QHBoxLayout;
    mainLay_general->addLayout(vlay_left);
    mainLay_general->addLayout(vlay_right);
    mainLay_general->setContentsMargins(70,53,80,50);
    setWid[1]->setLayout(mainLay_general);

}
void SetUp::shortcutKey_setting()
{
    QStringList strList_send;
    strList_send<<"Ctrl + Enter"<<"Enter";
    QStringList strList_shortCut;
    strList_shortCut<<"Alt + A"<<"Ctrl + Alt + A";


    QHBoxLayout * hblay_first = new QHBoxLayout;
    sendComboBox = new QComboBox;
    sendComboBox->addItems(strList_send);
    sendComboBox->setFont(QFont("Microsoft YaHei",11));
    sendComboBox->setStyleSheet("QComboBox{background-color:white;border-style:none;width:132px;height:25px}"
                                "QComboBox QAbstractItemView{background-color:white}");
    QLabel * sendLab = new QLabel("发送消息");
    sendLab->setFont(QFont("Microsoft YaHei",11));
    hblay_first->addWidget(sendLab);
    hblay_first->addWidget(sendComboBox);
    hblay_first->addStretch();
    hblay_first->setSpacing(30);

    QHBoxLayout * hblay_second = new QHBoxLayout;
    shortCutComboBox = new QComboBox;
    shortCutComboBox->addItems(strList_shortCut);
    shortCutComboBox->setFont(QFont("Microsoft YaHei",11));
    shortCutComboBox->setStyleSheet("QComboBox{background-color:white;border-style:none;width:132px;height:25px}"
                                "QComboBox QAbstractItemView{background-color:white}");
    QLabel * shortLab = new QLabel("截取屏幕");
    shortLab->setFont(QFont("Microsoft YaHei",11));
    hblay_second->addWidget(shortLab);
    hblay_second->addWidget(shortCutComboBox);
    hblay_second->addStretch();
    hblay_second->setSpacing(30);

    QVBoxLayout * vlay= new QVBoxLayout;
    vlay->addLayout(hblay_first);
    vlay->addLayout(hblay_second);
    vlay->addStretch();
    vlay->setSpacing(30);
    vlay->setContentsMargins(70,53,0,150);
    setWid[2]->setLayout(vlay);
}
void SetUp::version_setting()
{
    versionInfo = new QLabel;
    versionInfo->setFont(QFont("Microsoft YaHei",11));
    versionInfo->setText("IM 19.1.0");
    QLabel * verLab = new QLabel("版本信息");
    verLab->setFont(QFont("Microsoft YaHei",11));
    QHBoxLayout* hlay = new QHBoxLayout;
    hlay->addWidget(verLab);
    hlay->addWidget(versionInfo);
    hlay->setSpacing(30);
    hlay->addStretch();
    QVBoxLayout *vlay = new QVBoxLayout;
    vlay->addLayout(hlay);
    vlay->addStretch();
    vlay->setContentsMargins(70,53,0,200);
    setWid[3]->setLayout(vlay);
}








