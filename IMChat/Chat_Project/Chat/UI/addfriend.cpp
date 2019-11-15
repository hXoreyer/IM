#include "addfriend.h"

AddFriend::AddFriend(QWidget *parent) : QWidget(parent)
{

}
QLayout* AddFriend::toptoolBar()
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
    minBtn->setStyleSheet("QPushButton:hover{background-color:rgba(198,198,198,75)}");
    cloBtn->setStyleSheet("QPushButton:hover{background-color:red}");

    QHBoxLayout* tittle_lay = new QHBoxLayout;
    tittle_lay->addWidget(minBtn);
    tittle_lay->addWidget(cloBtn);
    tittle_lay->setMargin(0);
    tittle_lay->setSpacing(0);

    connect(cloBtn,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(minBtn,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    return tittle_lay;

}
void AddFriend::onClicked()
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
void AddFriend::mousePressEvent(QMouseEvent *event)
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
