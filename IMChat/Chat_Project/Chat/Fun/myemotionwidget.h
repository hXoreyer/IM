#ifndef MYEMOTIONWIDGET_H
#define MYEMOTIONWIDGET_H
#include <QWidget>
#include <QStackedWidget>
#include <QTableWidgetItem>
#include <QMovie>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
class MyEmotionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyEmotionWidget(QWidget *parent = nullptr);
    void addFitstItem();
    void addSecondItem();
private:
    QTableWidget * m_tabFirstWidget = Q_NULLPTR;
    QTableWidget * m_tabSecondWidget = Q_NULLPTR;
    QStackedWidget * m_stackWidget = Q_NULLPTR;
    QPushButton * m_icon_1Btn;
    QPushButton * m_icon_2Btn;
    QVBoxLayout * main_vlay;
    std::map<std::pair<int,int>,int> m_firstMap;
    std::map<std::pair<int,int>,int> m_secondMap;
signals:
    void sendEmotionPath(const QString& path);
public slots:
};

#endif // MYEMOTIONWIDGET_H
