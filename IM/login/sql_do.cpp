#include "sql_do.h"

bool find_email(SQL *s, string user_email)
{
    vector<map<string,string> > m;
    string sql = "select * from users where user_email= \'" + user_email + "\'";
    if(s->query_data(sql,m))
    {
        if(m.size() == 0)
            return true;
        else
            return false;
    }
}

bool add_email(SQL *s,string user_name, string user_email, string user_pass)
{
    map<string,string> m;
    m["user_name"] = "\'" + user_name + "\'";
    m["user_pass"] = "\'" + user_pass + "\'";
    m["user_email"] = "\'" + user_email + "\'";
    if(s->insert_data("users",m))
    {
        return true;
    }else
    {
        return false;
    }
}

int login(SQL *s,string user_email, string user_pass)
{
    string sql = "select * from users where user_email = ";
    sql = sql + "\'" + user_email + "\'";
    vector<map<string,string> > res;
    if(s->query_data(sql,res))
    {
        if(res.size() == 0)
            return 0;
        else
        {
            
            if(!res[0]["user_pass"].compare(user_pass))
                return 1;
            else
                return 2;
            
        }
    }
}

bool firnds_list(SQL *s,string user_email,vector<map<string,string> > &ret)
{
    string sql = "select * from friends where user_email = ";
    sql = sql + "\'" + user_email + "\'";
    if(s->query_data(sql,ret))
    {
        if(ret.size() == 0)
            return false;
        else
        {
            return true;
        }
        

    }else
    {
        return false;
    }
    
}