QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chat/Fun/chatrecord.cpp \
    Chat/Fun/controller.cpp \
    Chat/Fun/frmscreen.cpp \
    Chat/Fun/json.cpp \
    Chat/Fun/myemotionwidget.cpp \
    Chat/Fun/screenapi.cpp \
    Chat/Fun/serv_thread.cpp \
    Chat/Fun/sqlite.cpp \
    Chat/Fun/worker.cpp \
    Chat/NetWork/Socket.cpp \
    Chat/NetWork/server.cpp \
    Chat/NetWork/udp.cpp \
    Chat/UI/addfriend.cpp \
    Chat/UI/chat_ui.cpp \
    Chat/UI/feedback.cpp \
    Chat/UI/friends.cpp \
    Chat/UI/friendslist.cpp \
    Chat/UI/percard.cpp \
    Chat/UI/permsg.cpp \
    Chat/UI/qimageview.cpp \
    Chat/UI/qnchatmessage.cpp \
    Chat/UI/setup.cpp \
    Chat/UI/textedit.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Chat/Fun/chatrecord.h \
    Chat/Fun/common.h \
    Chat/Fun/controller.h \
    Chat/Fun/frmscreen.h \
    Chat/Fun/json.h \
    Chat/Fun/myemotionwidget.h \
    Chat/Fun/screenapi.h \
    Chat/Fun/serv_thread.h \
    Chat/Fun/sqlite.h \
    Chat/Fun/worker.h \
    Chat/NetWork/Socket.h \
    Chat/NetWork/server.h \
    Chat/NetWork/udp.h \
    Chat/UI/addfriend.h \
    Chat/UI/chat_ui.h \
    Chat/UI/feedback.h \
    Chat/UI/friends.h \
    Chat/UI/friendslist.h \
    Chat/UI/percard.h \
    Chat/UI/permsg.h \
    Chat/UI/qimageview.h \
    Chat/UI/qnchatmessage.h \
    Chat/UI/setup.h \
    Chat/UI/textedit.h \
    widget.h
LIBS += -lws2_32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Chat/Fun/emotions/1.jpg \
    Chat/Fun/emotions/10.jpg \
    Chat/Fun/emotions/11.jpg \
    Chat/Fun/emotions/12.jpg \
    Chat/Fun/emotions/13.jpg \
    Chat/Fun/emotions/14.jpg \
    Chat/Fun/emotions/15.jpg \
    Chat/Fun/emotions/16.jpg \
    Chat/Fun/emotions/17.jpg \
    Chat/Fun/emotions/18.jpg \
    Chat/Fun/emotions/19.jpg \
    Chat/Fun/emotions/2.jpg \
    Chat/Fun/emotions/20.jpg \
    Chat/Fun/emotions/21.jpg \
    Chat/Fun/emotions/22.jpg \
    Chat/Fun/emotions/23.jpg \
    Chat/Fun/emotions/24.jpg \
    Chat/Fun/emotions/25.jpg \
    Chat/Fun/emotions/3.jpg \
    Chat/Fun/emotions/4.jpg \
    Chat/Fun/emotions/5.jpg \
    Chat/Fun/emotions/6.jpg \
    Chat/Fun/emotions/7.jpg \
    Chat/Fun/emotions/8.jpg \
    Chat/Fun/emotions/9.jpg \
    Chat/Fun/face/1.gif \
    Chat/Fun/face/10.gif \
    Chat/Fun/face/11.gif \
    Chat/Fun/face/12.gif \
    Chat/Fun/face/13.gif \
    Chat/Fun/face/14.gif \
    Chat/Fun/face/15.gif \
    Chat/Fun/face/16.gif \
    Chat/Fun/face/17.gif \
    Chat/Fun/face/18.gif \
    Chat/Fun/face/19.gif \
    Chat/Fun/face/2.gif \
    Chat/Fun/face/20.gif \
    Chat/Fun/face/21.gif \
    Chat/Fun/face/22.gif \
    Chat/Fun/face/23.gif \
    Chat/Fun/face/24.gif \
    Chat/Fun/face/25.gif \
    Chat/Fun/face/26.gif \
    Chat/Fun/face/27.gif \
    Chat/Fun/face/28.gif \
    Chat/Fun/face/29.gif \
    Chat/Fun/face/3.gif \
    Chat/Fun/face/30.gif \
    Chat/Fun/face/31.gif \
    Chat/Fun/face/32.gif \
    Chat/Fun/face/33.gif \
    Chat/Fun/face/34.gif \
    Chat/Fun/face/35.gif \
    Chat/Fun/face/36.gif \
    Chat/Fun/face/37.gif \
    Chat/Fun/face/38.gif \
    Chat/Fun/face/39.gif \
    Chat/Fun/face/4.gif \
    Chat/Fun/face/40.gif \
    Chat/Fun/face/41.gif \
    Chat/Fun/face/42.gif \
    Chat/Fun/face/43.gif \
    Chat/Fun/face/44.gif \
    Chat/Fun/face/45.gif \
    Chat/Fun/face/46.gif \
    Chat/Fun/face/47.gif \
    Chat/Fun/face/48.gif \
    Chat/Fun/face/49.gif \
    Chat/Fun/face/5.gif \
    Chat/Fun/face/50.gif \
    Chat/Fun/face/51.gif \
    Chat/Fun/face/52.gif \
    Chat/Fun/face/53.gif \
    Chat/Fun/face/54.gif \
    Chat/Fun/face/55.gif \
    Chat/Fun/face/56.gif \
    Chat/Fun/face/57.gif \
    Chat/Fun/face/58.gif \
    Chat/Fun/face/59.gif \
    Chat/Fun/face/6.gif \
    Chat/Fun/face/60.gif \
    Chat/Fun/face/61.gif \
    Chat/Fun/face/62.gif \
    Chat/Fun/face/63.gif \
    Chat/Fun/face/64.gif \
    Chat/Fun/face/65.gif \
    Chat/Fun/face/66.gif \
    Chat/Fun/face/67.gif \
    Chat/Fun/face/68.gif \
    Chat/Fun/face/69.gif \
    Chat/Fun/face/7.gif \
    Chat/Fun/face/70.gif \
    Chat/Fun/face/71.gif \
    Chat/Fun/face/72.gif \
    Chat/Fun/face/73.gif \
    Chat/Fun/face/74.gif \
    Chat/Fun/face/75.gif \
    Chat/Fun/face/76.gif \
    Chat/Fun/face/77.gif \
    Chat/Fun/face/78.gif \
    Chat/Fun/face/79.gif \
    Chat/Fun/face/8.gif \
    Chat/Fun/face/80.gif \
    Chat/Fun/face/9.gif \
    Chat/Fun/icon/icon_1.svg \
    Chat/Fun/icon/icon_2.svg \
    Chat/image/AddGroupChat.svg \
    Chat/image/Chat.svg \
    Chat/image/ChatBook.svg \
    Chat/image/ChatBookFocus.svg \
    Chat/image/ChatFocus.svg \
    Chat/image/ChatRecord.svg \
    Chat/image/ChatRecordFocus.svg \
    Chat/image/Close.svg \
    Chat/image/Cut.svg \
    Chat/image/CutFocus.svg \
    Chat/image/Face.svg \
    Chat/image/FaceFocus.svg \
    Chat/image/File.svg \
    Chat/image/FileFocus.svg \
    Chat/image/Max_Streth.svg \
    Chat/image/Min.svg \
    Chat/image/Min_Streth.svg \
    Chat/image/More.svg \
    Chat/image/MoreFocus.svg \
    Chat/image/PerMore.svg \
    Chat/image/PerMoreFocus.svg \
    Chat/image/Search.svg \
    Chat/image/SoundChat.svg \
    Chat/image/SoundChatFocus.svg \
    Chat/image/VideoChat.svg \
    Chat/image/VideoChatFocus.svg \
    Chat/image/error.svg \
    Chat/image/head.jpg \
    Chat/image/loading4.gif \
    image/CheckBox.svg \
    image/Close.svg \
    image/Login.svg \
    image/LoginFocus.svg \
    image/Min.svg \
    image/Psw.svg \
    image/PswFocus.svg \
    image/User.svg \
    image/UserFocus.svg \
    image/bck.jpg \
    image/head.jpg

RESOURCES += \
    Resources.qrc
