#include "sql.h"
bool SQL::init(string host, string user_name, string pass_word, string data_base)
{
    mysql_init(&con);
    if(mysql_real_connect(&con,host.c_str(),user_name.c_str(),pass_word.c_str(),data_base.c_str(),0,NULL,CLIENT_FOUND_ROWS))
    {
        return true;
    }
    return false;
}

bool SQL::create_table(string table_name, map<string, string> param)
{
    string sql;
    sql = "create table " + table_name + " (";
    for(map<string,string>::iterator i = param.begin(); i != param.end(); i++)
    {
        sql = sql + i->first + " " + i->second + ",";
    }
    sql.replace(sql.end() - 1,sql.end(), ")");
    cout<<sql<<"size:"<<sql.size()<<endl;
    if(mysql_query(&con,sql.c_str()))
    {
        return false;
    }
    return true;
}

bool SQL::delete_table(string table_name)
{
    string sql = "drop table " + table_name;
    if(mysql_query(&con,sql.c_str()))
    {
        return false;
    }
    return true;
}

bool SQL::insert_data(string table_name, map<string,string> param)
{
    string sql = "insert into " + table_name + " (";
    for(map<string,string>::iterator i = param.begin(); i != param.end(); i++)
    {
        sql = sql + i->first + ",";
    }
    sql.replace(sql.end() - 1, sql.end(), ")");
    sql = sql + "values(";
        for(map<string,string>::iterator i = param.begin(); i != param.end(); i++)
    {
        sql = sql + i->second + ",";
    }
    sql.replace(sql.end() - 1, sql.end(), ")");
    cout<<sql<<endl;
    if(mysql_query(&con,sql.c_str()))
    {
        return false;
    }
    return true;
}

bool SQL::query_data(string sql,vector<map<string,string> > &ret)
{
    //设置编码格式
    mysql_query(&con, "set names utf-8"); 

    /*int mysql_query(MYSQL *mysql, const char *stmt_str)
    Executes an SQL query specified as a null-terminated string
    Executes the SQL statement pointed to by the null-terminated string stmt_str. 
    Normally, the string must consist of a single SQL statement without 
    a terminating semicolon (;). If multiple-statement execution has been enabled,
    the string can contain several statements separated by semicolons.
    Return Values:Zero for success. Nonzero if an error occurred.*/
    if (mysql_query(&con, sql.c_str())){
        return false;
    }
    MYSQL_RES* res = mysql_store_result(&con);
    if (!res){
        return false;
    }
    
    // 获取列数
    int j = mysql_num_fields(res);

    //存储字段信息
    string str_field[32];  

    //获取字段名
    for (int i = 0; i < j; i++){ 
        str_field[i] = mysql_fetch_field(res)->name;
    }

    //打印查询结果
    //MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
    //Fetches the next row from the result set
    while (MYSQL_ROW column = mysql_fetch_row(res)){
        map<string,string> m;
        for(int i = 0; i < j; ++i)
        {
            m[str_field[i]] = column[i];
        }
        ret.push_back(m);
    }
    return true;
}