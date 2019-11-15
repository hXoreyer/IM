#include "screenapi.h"

ScreenAPI::ScreenAPI(QSize size)
{
    maxWidth = size.width();
    maxHeight = size.height();

    //???
    startPos = QPoint(-1,-1);
    endPos = startPos;
    leftUpPos = startPos;
    rightDownPos = startPos;
    status = SELECT;
}

int ScreenAPI::width()
{
    return maxWidth;
}

int ScreenAPI::height()
{
    return maxHeight;
}

ScreenAPI::STATUS ScreenAPI::getStatus()
{
    return status;
}

void ScreenAPI::setStatus(STATUS st)
{
    status=st;
}

void ScreenAPI::setEnd(QPoint pos)
{
    endPos = pos;
    leftUpPos = startPos;
    rightDownPos = endPos;
    cmpPoint(leftUpPos,rightDownPos);
}

void ScreenAPI::setStart(QPoint pos)
{
    startPos=pos;
}

QPoint ScreenAPI::getEnd()
{
    return endPos;
}

QPoint ScreenAPI::getStart()
{
    return startPos;
}

QPoint ScreenAPI::getLeftUp()
{
    return leftUpPos;
}

QPoint ScreenAPI::getRightDown()
{
    return rightDownPos;
}


bool ScreenAPI::isInArea(QPoint pos)
{
    if( pos.x() > leftUpPos.x() && pos.x() < rightDownPos.x() &&\
        pos.y() > leftUpPos.y() && pos.y() < rightDownPos.y() )
        return true;
    return false;
}
void ScreenAPI::move(QPoint p)
{
    int lx = leftUpPos.x() + p.x();
    int ly = leftUpPos.y() + p.y();
    int rx = rightDownPos.x() + p.x();
    int ry = rightDownPos.y() + p.y();

    if( lx<0 ) { lx = 0; rx -= p.x(); }
    if( ly<0 ) { ly = 0; ry -= p.y(); }
    if( rx>maxWidth )  { rx = maxWidth; lx -= p.x(); }
    if( ry>maxHeight ) { ry = maxHeight; ly -= p.y(); }

    leftUpPos = QPoint(lx,ly);
    rightDownPos = QPoint(rx,ry);
    startPos = leftUpPos;
    endPos = rightDownPos;
}
void ScreenAPI::cmpPoint(QPoint& leftTop,QPoint& rightDown)
{
    QPoint l = leftTop;
    QPoint r = rightDown;

    if( l.x()<=r.x()  )
    {
        if( l.y()<=r.y() )
        {
            ;
        }
        else
        {
            leftTop.setY(r.y());
            rightDown.setY(l.y());
        }
    }
    else
    {
        if( l.y()<r.y() )
        {
            leftTop.setX(r.x());
            rightDown.setX(l.x());
        }
        else
        {
            QPoint tmp;
            tmp = leftTop;
            leftTop = rightDown;
            rightDown = tmp;
        }
    }
}

