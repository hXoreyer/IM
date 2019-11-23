#ifndef SQL_H
#define SQL_H
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class SQL
{
private:
    MYSQL con;
public:
    SQL(){}
    SQL(SQL *src):con(src->con){}
    ~SQL()
    {
        mysql_close(&con);
    }

    bool init(string host, string user_name, string pass_word, string data_base); //初始化
    bool create_table(string table_name, map<string, string> param);//创建数据表
    bool delete_table(string table_name);//删除数据表

    /*************************
     *          数据操作类继承后实现
     * ***********************/
    bool insert_data(string table_name, map<string,string> param);//插入数据
    bool query_data(string sql,vector<map<string,string> > &ret); //查询语句

    inline void operator=(SQL *src)
    {
        con = src->con;
    }

};

#endif