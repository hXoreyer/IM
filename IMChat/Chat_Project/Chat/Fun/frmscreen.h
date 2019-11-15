#ifndef FRMSCREEN_H
#define FRMSCREEN_H
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
#include <QMenu>
#include <QAction>
#include <QWindow>
#include <QScreen>
#include <QDateTime>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPointer>
#include <QPen>
#include "qpainter.h"
#include "screenapi.h"
class frmScreen : public QWidget
{
    Q_OBJECT
public:
    explicit frmScreen(QWidget *parent = nullptr);
    void initForm();
private:
    QMenu * m_menu = Q_NULLPTR;
    ScreenAPI * m_screen = Q_NULLPTR;
    QPixmap * m_fullScreen = Q_NULLPTR;
    QPixmap * m_bgScreen = Q_NULLPTR;
    QPoint movPos;
    QPixmap m_screenImg;
    int m_screen_x;
    int m_screen_y;
    int m_screen_w;
    int m_screen_h;
protected:
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent* e);

signals:
    void sendScreenImgPath(const QString& path);
public slots:
};

#endif // FRMSCREEN_H
