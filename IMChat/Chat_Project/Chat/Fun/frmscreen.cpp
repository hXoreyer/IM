#include "frmscreen.h"
#include <QDebug>
frmScreen::frmScreen(QWidget *parent) : QWidget(parent)
{
    this->initForm();
}
//初始化框架
void frmScreen::initForm()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);//隐藏标题栏，窗体出现在最顶层
    m_menu = new QMenu(this);
    QAction  * m_saveAction = new QAction("确定",this);
    //m_saveAction->setShortcut(tr("enter"));
    connect(m_saveAction,&QAction::triggered,this,[&]()
    {
        QPixmap pix;
        QWindow *window=windowHandle();
        QScreen *screen=window->screen();

        pix = screen->grabWindow(winId(),m_screen_x,m_screen_y,m_screen_w,m_screen_h);
        if(!pix.isNull())
        {
            QString fileName =  QDateTime::currentDateTime().toString("yyyy_MM_dd hh_mm");
            fileName += ".jpg";
            if(pix.save(fileName,"jpg"))
            {
                emit sendScreenImgPath(fileName);
                this->hide();
            }
        }
    });
    m_menu->addAction(m_saveAction);
    QAction * m_saveOtherAction = new QAction("另存为",this);
    connect(m_saveOtherAction,&QAction::triggered,this,[&]()
    {
        QString fileName = QFileDialog::getSaveFileName(this,tr("此电脑"),"C:",tr("图片文件(*jpg)"));
        QPixmap pix;
        QWindow *window=windowHandle();
        QScreen *screen=window->screen();

        pix = screen->grabWindow(winId(),m_screen_x,m_screen_y,m_screen_w,m_screen_h);
        if(!pix.isNull())
        {
            if(pix.save(fileName,"jpg"))
            {
                this->hide();
            }
        }

    });
    m_menu->addAction(m_saveOtherAction);
    m_menu->addAction("取消", this, SLOT(hide()));

    //取得屏幕大小
    m_screen = new ScreenAPI(QApplication::desktop()->size());
    //保存全屏图像
    m_fullScreen = new QPixmap();
}
void frmScreen::showEvent(QShowEvent *)
{
    QPoint point(-1, -1);
    m_screen->setStart(point);//设置开启坐标点
    m_screen->setEnd(point);//设置结束坐标点

    //全屏图像，抓取窗体
    QWindow *window=windowHandle();
    QScreen *screen=window->screen();

    *m_fullScreen = screen->grabWindow(0);
    //设置透明度实现模糊背景
    QPixmap pix(m_screen->width(), m_screen->height());
    pix.fill((QColor(0, 0, 0, 200)));//模糊颜色填充
    m_bgScreen = new QPixmap(*m_fullScreen);
    QPainter p(m_bgScreen);
    p.drawPixmap(0, 0, pix);
}
void frmScreen::paintEvent(QPaintEvent *)
{
    m_screen_x = m_screen->getLeftUp().x();
    m_screen_y = m_screen->getLeftUp().y();
    m_screen_w = m_screen->getRightDown().x() - m_screen_x;//宽度
    m_screen_h = m_screen->getRightDown().y() - m_screen_y;//高度

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidth(2);
    //pen.setStyle(Qt::DotLine);//虚线样式
    painter.setPen(pen);

    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(10);
    painter.setFont(font);

    //截屏思想：点击截屏工具的时候，截取全屏的像素，并且将全屏保存到一个全局的变量pixmap中。
    //然后，在点击鼠标移动，截取一个相应的矩形。将其绘制出来。
    painter.drawPixmap(0, 0, *m_bgScreen);//

    if (m_screen_w != 0 && m_screen_h != 0) {
        painter.drawPixmap(m_screen_x, m_screen_y, m_fullScreen->copy(m_screen_x, m_screen_y, m_screen_w, m_screen_h));//绘制选择截屏的区域
    }

    painter.drawRect(m_screen_x, m_screen_y, m_screen_w, m_screen_h);//绘制截图矩形
    //QString imgName = QDateTime::currentDateTime().toString("yyyy-MM-ddHH-mm-ss")  + ".jpg";//通过时间命名文件

    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawText(m_screen_x + 2, m_screen_y - 8, tr("截图范围：( %1 x %2 ) - ( %3 x %4 )  图片大小：( %5 x %6 )")
                     .arg(m_screen_x).arg(m_screen_y).arg(m_screen_x + m_screen_w).arg(m_screen_y + m_screen_h).arg(m_screen_w).arg(m_screen_h));
}
//鼠标按下事件
void frmScreen::mousePressEvent(QMouseEvent *e)
{
    int status = m_screen->getStatus();//获取状态

    if (status == ScreenAPI::SELECT) {
        m_screen->setStart(e->pos());
    } else if (status == ScreenAPI::MOV) {
        if (m_screen->isInArea(e->pos()) == false) {
            m_screen->setStart(e->pos());
            m_screen->setStatus(ScreenAPI::SELECT);
        } else {
            movPos = e->pos();
            this->setCursor(Qt::SizeAllCursor);
        }
    }

    update();
}
//鼠标移动事件
void frmScreen::mouseMoveEvent(QMouseEvent *e)
{
    if (m_screen->getStatus() == ScreenAPI::SELECT) {//选择区域
        m_screen->setEnd(e->pos());//得到结束点坐标
    } else if (m_screen->getStatus() == ScreenAPI::MOV) {//移动区域
        QPoint p(e->x() - movPos.x(), e->y() - movPos.y());
        m_screen->move(p);
        movPos = e->pos();
    }

    update();
}
//鼠标释放事件
void frmScreen::mouseReleaseEvent(QMouseEvent *)
{
    if (m_screen->getStatus() == ScreenAPI::SELECT) {
        m_screen->setStatus(ScreenAPI::MOV);
    } else if (m_screen->getStatus() == ScreenAPI::MOV) {
        this->setCursor(Qt::ArrowCursor);
    }
}
void frmScreen::contextMenuEvent(QContextMenuEvent* e)
{
    m_menu->exec(e->globalPos());
}
