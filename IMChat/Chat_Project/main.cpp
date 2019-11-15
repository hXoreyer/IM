//#include "widget.h"
#include <QApplication>
//#include "Chat/UI/chat_ui.h"
//#include "Chat/UI/setup.h"
#include "Chat/UI/chat_ui.h"
//#include "Chat/Fun/myemotionwidget.h"
#include "Chat/Fun/chatrecord.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;

    std::vector<net::MSG> ptr_vec;
    std::vector<std::string> friend_name = {"Mariaes","Keing","Kyced","Mariae"};
    std::vector<std::string> nick_name = {"Mariaes","","","La Fe"};
    std::vector<std::string> friend_email = {"1724236802@qq.com","1067374087@qq.com","xiazeshuang@hotmail.com","1854158152@qq.com"};
    for(unsigned i = 0;i < 4;++i)
    {
        net::MSG perMsg;
        memset(&perMsg,0,sizeof (perMsg));
        strcpy(perMsg.nick_name,nick_name[i].c_str());
        strcpy(perMsg.friend_name,friend_name[i].c_str());
        strcpy(perMsg.friend_email,friend_email[i].c_str());
        ptr_vec.push_back(perMsg);
    }
    Chat_Ui w("1067374087@qq.com",ptr_vec);
    w.show();
    return a.exec();
}
