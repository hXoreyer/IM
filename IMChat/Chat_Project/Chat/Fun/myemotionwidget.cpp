#include "myemotionwidget.h"

MyEmotionWidget::MyEmotionWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(QSize(452,304));
    m_stackWidget = new QStackedWidget(this);
    m_icon_1Btn = new QPushButton(this);
    m_icon_1Btn->setIcon(QIcon(":/Chat/Fun/icon/icon_1.svg"));
    m_icon_1Btn->setToolTip("经典表情");
    m_icon_1Btn->setFlat(true);
    m_icon_1Btn->setIconSize(QSize(25,25));
    connect(m_icon_1Btn,&QPushButton::clicked,this,[&]()
    {
        m_stackWidget->setCurrentIndex(0);
    });
    m_icon_2Btn = new QPushButton(this);
    m_icon_2Btn->setIcon(QIcon(":/Chat/Fun/icon/icon_2.svg"));
    m_icon_2Btn->setToolTip("表情包");
    m_icon_2Btn->setFlat(true);
    m_icon_2Btn->setIconSize(QSize(25,25));
    connect(m_icon_2Btn,&QPushButton::clicked,this,[&]()
    {
        m_stackWidget->setCurrentIndex(1);
    });
    QHBoxLayout * hlay = new QHBoxLayout;
    hlay->addWidget(m_icon_1Btn);
    hlay->addWidget(m_icon_2Btn);
    hlay->addStretch();
    main_vlay = new QVBoxLayout(this);
    main_vlay->addWidget(m_stackWidget);
    main_vlay->setMargin(0);
    main_vlay->addLayout(hlay);
    setLayout(main_vlay);
    addFitstItem();
    addSecondItem();
}
void MyEmotionWidget::addFitstItem()
{
    m_tabFirstWidget = new QTableWidget(7,13);
    int count = 1;
    int row, col;
    for(row = 0;row < 7;++row)
    {
        for(col = 0;col < 13;++col)
        {
            if(count > 80)
                break;
            QLabel * emotionIcon = new QLabel;
            emotionIcon->setMargin(5);
            QMovie * movie = new QMovie;
            movie->setScaledSize(QSize(24, 24));
            movie->setFileName(QString(":/Chat/Fun/face/%1.gif").arg(count));
            emotionIcon->setMovie(movie);
            movie->start();
            m_tabFirstWidget->setCellWidget(row,col,emotionIcon);
            m_tabFirstWidget->resizeRowToContents(row);
            m_tabFirstWidget->resizeColumnToContents(col);
            m_secondMap.insert({{row,col},count});
            count++;
        }
    }
    QHeaderView * m_verticalheader = m_tabFirstWidget->verticalHeader();
    m_verticalheader->setHidden(true);
    QHeaderView * m_horizontalheader = m_tabFirstWidget->horizontalHeader();
    m_horizontalheader->setHidden(true);
    m_stackWidget->addWidget(m_tabFirstWidget);
    connect(m_tabFirstWidget,&QTableWidget::cellClicked,this,[&](int row,int col)
    {
        emit sendEmotionPath(QString(":Chat/Fun/emotions/%1.gif").arg(m_secondMap[{row,col}]));
    });
}
void MyEmotionWidget::addSecondItem()
{
    m_tabSecondWidget = new QTableWidget(7,4);
    int count = 1;
    int row,col;
    for(row = 0;row < 7;++row)
    {
        for(col = 0;col < 4;++col)
        {
            if(count > 25)
                break;
            QLabel * emotionIcon = new QLabel;
            //emotionIcon->setMargin(3);
            QPixmap m_pixmap;
            m_pixmap.load(QString(":Chat/Fun/emotions/%1.jpg").arg(count));
            QPixmap m_resizePix = m_pixmap.scaled(67,67,Qt::KeepAspectRatioByExpanding);
            emotionIcon->setAlignment(Qt::AlignCenter);
            emotionIcon->setPixmap(m_resizePix);
            m_tabSecondWidget->setCellWidget(row,col,emotionIcon);
            m_tabSecondWidget->resizeRowToContents(row);
            m_tabSecondWidget->resizeColumnToContents(col);
            m_firstMap.insert({{row,col},count});
            count++;
        }
    }
    QHeaderView * m_verticalheader = m_tabSecondWidget->verticalHeader();
    m_verticalheader->setHidden(true);
    QHeaderView * m_horizontalheader = m_tabSecondWidget->horizontalHeader();
    m_horizontalheader->setHidden(true);
    connect(m_tabSecondWidget,&QTableWidget::cellClicked,this,[&](int row,int col)
    {
        emit sendEmotionPath(QString(":Chat/Fun/emotions/%1.jpg").arg(m_firstMap[{row,col}]));
    });
    m_stackWidget->addWidget(m_tabSecondWidget);
}
