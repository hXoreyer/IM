#ifndef SCREENAPI_H
#define SCREENAPI_H
#include <QPoint>
#include <QSize>

class ScreenAPI
{
public:
    enum STATUS {SELECT, MOV, SET_W_H};
    ScreenAPI() {}
    ScreenAPI(QSize size);

    void setStart(QPoint pos);//设置开启坐标
    void setEnd(QPoint pos);//设置结束坐标
    QPoint getStart();
    QPoint getEnd();

    QPoint getLeftUp();
    QPoint getRightDown();

    STATUS getStatus();
    void setStatus(STATUS status);

    int width();
    int height();
    bool isInArea(QPoint pos);          // 检测pos是否在截图区域内
    void move(QPoint p);                // 按 p 移动截图区域

private:
    QPoint leftUpPos, rightDownPos;     //记录 截图区域 左上角、右下角
    QPoint startPos, endPos;            //记录 鼠标开始位置、结束位置
    int maxWidth, maxHeight;            //记录屏幕大小
    STATUS status;                      //三个状态: 选择区域、移动区域、设置width height

    void cmpPoint(QPoint &s, QPoint &e);//比较两位置，判断左上角、右下角
};

#endif // SCREENAPI_H
