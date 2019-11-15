#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <windows.h>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
class AddFriend : public QWidget
{
    Q_OBJECT
public:
    explicit AddFriend(QWidget *parent = nullptr);
    QLayout * toptoolBar();

private:
    QPushButton * minBtn;
    QPushButton * cloBtn;
    QVBoxLayout * mainLay;

protected:
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:
    void onClicked();
};

#endif // ADDFRIEND_H
