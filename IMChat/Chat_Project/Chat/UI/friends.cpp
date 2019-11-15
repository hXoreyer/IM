#include "friends.h"

friends::friends(const QPixmap& headimg, const QString& nickname)
    :head_img(headimg),nick_name(nickname)
{


    QLabel *head = new QLabel;
    head->setPixmap(head_img.scaled(50,50));
    QLabel *nick = new QLabel(nick_name);
    nick->setFont(QFont("Consolas",11));

    QHBoxLayout *main = new QHBoxLayout(this);
    main->addWidget(head);
    main->addWidget(nick);
    main->addStretch();
    main->setSpacing(10);

    itemWidget = new QWidget;
    itemWidget->setLayout(main);
}
friends::~friends()
{

}
QWidget * friends::getWidget()
{
    return itemWidget;
}
