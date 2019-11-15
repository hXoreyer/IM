#ifndef FRIENDS_H
#define FRIENDS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QHBoxLayout>
#include <QDebug>
#include <QMouseEvent>
class friends : public QWidget
{
    Q_OBJECT
public:
    //explicit friends(QWidget *parent = nullptr);
    friends(const QPixmap& headimg,const QString& nickname);
    ~friends();
    QWidget * getWidget();
private:
    QPixmap head_img;
    QString nick_name;
    QWidget * itemWidget;
};

#endif // FRIENDS_H
