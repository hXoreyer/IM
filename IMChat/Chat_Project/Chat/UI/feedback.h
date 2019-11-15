#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QMouseEvent>
#include <windows.h>
class FeedBack : public QWidget
{
    Q_OBJECT
public:
    explicit FeedBack(QWidget *parent = nullptr);
private:
    QTextEdit * text;
    QPushButton * sendBtn;
    QPushButton * cancelBtn;
    QPushButton * closeBtn;
    QVBoxLayout * main_vlay;
protected:
    void mousePressEvent(QMouseEvent *event);

signals:

};

#endif // FEEDBACK_H
