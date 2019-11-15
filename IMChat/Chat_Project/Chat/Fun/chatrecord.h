#ifndef CHATRECORD_H
#define CHATRECORD_H
#include "common.h"
class ChatRecord : public QWidget
{
    Q_OBJECT
public:
    explicit ChatRecord(const QString& m_name,QWidget *parent = nullptr);
    QLayout* addWidget();
    QLayout* addToolItem();
private:

    QPushButton * m_cloBtn = Q_NULLPTR;
    QPushButton * m_minBtn = Q_NULLPTR;
    QLabel * m_tittleBtn = Q_NULLPTR;
    QString m_tittle;
    QVBoxLayout * main_vlay = Q_NULLPTR;
    QLineEdit * searchEdit = Q_NULLPTR;
    QPushButton * ptr_toolBtn[4];

protected:
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject * watched,QEvent *event);
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // CHATRECORD_H
