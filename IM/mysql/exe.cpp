#include <iostream>
#include "sql.h"
using namespace std;

// exe find email [add user_name user_pass user_email]
int main(int argc,const char* argv[])
{
    if(argc <= 1)
        return -1;
    
    SQL* s = new SQL();
    if(s->init("localhost","root","199836Keing..","IM"))
    {
        string constrol = argv[1];
        if(!constrol.compare("find"))
        {
            vector<map<string,string> > m;
            string user_email = argv[2];
            string sql = "select * from users where user_email= \'" + user_email + "\'";
            if(s->query_data(sql,m))
            {
                if(m.size() == 0)
                    cout<<"可以注册!"<<endl;
                else
                    cout<<"已存在!"<<endl;
            }
        }else if(!constrol.compare("add"))
        {
            map<string,string> m;
            string user_name = argv[2];
            string user_pass = argv[3];
            string user_email = argv[4];
            m["user_name"] = "\'" + user_name + "\'";
            m["user_pass"] = "\'" + user_pass + "\'";
            m["user_email"] = "\'" + user_email + "\'";
            if(s->insert_data("users",m))
            {
                cout<<"注册成功!"<<endl;
            }else
            {
                cout<<"注册失败!"<<endl;
            }
            
        }
        delete s;    
    }
    else
    {
        cout<<"init failed"<<endl;
        return -1;
    }
    
    return 0;
}
