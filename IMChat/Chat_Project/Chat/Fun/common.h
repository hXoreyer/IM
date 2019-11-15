#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#define MAX_LINE 1024
namespace UDP{

#pragma pack(4)
enum TYPE
{
    LOGIN,
    //NEWCHAR,
    //REQUEST,
    CHAR,
    FILE,
    IMG,
    CHAT,
    //ONLINE,
    //NOT_ONLINE
};
struct MSG
{
    TYPE type;
    //TYPE status;
    char send_char[MAX_LINE];
    char recv_user[20];
    char send_user[20];
    //char site_ip[20];
    sockaddr_in addr;
};
#pragma pack()
}
#ifdef CHATRECORD_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <windows.h>
#include <QMouseEvent>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QAction>
#endif

#ifdef FRMSCREEN_H
#include <QWidget>
#include "screenapi.h"
#include <QAction>
#include <QPixmap>
#include <QMenu>
#include <QApplication>
#include <QDesktopWidget>
#include <QShowEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QContextMenuEvent>
#include <QPainter>
#include <QDateTime>
#include <QScreen>
#include <QWindow>
#include <QFileDialog>
#endif


#ifdef CHAT_UI_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QIcon>
#include <QSizePolicy>
#include <QLabel>
#include <QMouseEvent>
#include <windows.h>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QDebug>
#include <QStackedWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QAction>
#include <QScrollBar>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDockWidget>
#include <QList>
#include <QMenu>
#include <QPointer>
#include <set>
#include "Chat/UI/permsg.h"
#include "Chat/UI/friendslist.h"
#include "Chat/UI/percard.h"
#include "Chat/UI/friends.h"
#include "Chat/NetWork/Socket.h"
#include "Chat/NetWork/udp.h"
#endif

#ifdef PERMSG_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <vector>
#include <list>
#include <QEvent>
#include <QListWidgetItem>
#include <QDebug>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QImageReader>
#include <QTextDocumentFragment>
#endif

#ifdef WIDGET_H
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QActionGroup>
#include <QLayout>
#include <QLabel>
#include <QSettings>
#include <QStackedWidget>
#include <QPointer>
#include "Chat/NetWork/Socket.h"
#include "Chat/UI/chat_ui.h"
#include <QFont>
#include <QAction>
#include <QDesktopWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBitmap>
#include <QPainter>
#include <vector>
#include <windows.h>
#include <QMouseEvent>
#include <QPixmap>
#include <QDebug>
#include <string.h>
#include <QToolTip>
#include <QDesktopServices>
#include <QHostInfo>
#endif

#endif // COMMON_H
