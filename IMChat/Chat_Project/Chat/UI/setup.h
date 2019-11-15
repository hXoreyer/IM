#ifndef SETUP_H
#define SETUP_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <windows.h>
#include <QLayout>
#include <QMouseEvent>
#include <QStackedWidget>
#include <vector>
#include <QPaintEvent>
#include <QPainter>
#include <QEvent>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QStringList>
class SetUp : public QWidget
{
    Q_OBJECT
public:
    explicit SetUp(QWidget *parent = nullptr);
    QLayout * toptoolBar();
    QLayout * funUi_list();
    void account_setting();
    void general_setting();
    void shortcutKey_setting();
    void version_setting();

private:
    QPushButton * minBtn;
    QPushButton * cloBtn;
    QVBoxLayout * mainLay;
    QPushButton * setBtn[4];
    QWidget * setWid[4];
    QStackedWidget * stackWidget;


private:
    QPushButton * head;
    QLabel * petName;
    QLabel * account;
    QLabel * accountLabel;
    QPushButton * logOff;

    QLineEdit * filePath;
    QPushButton * fileBtn[2];
    QCheckBox * generalCheck[4];

    QComboBox * sendComboBox;
    QComboBox * shortCutComboBox;

    QLabel * versionInfo;




protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void onClicked();
    void on_BtnClicked_first();
    void on_BtnClicked_second();
    void on_BtnClicked_thrid();
    void on_BtnClicked_four();

};

#endif // SETUP_H
