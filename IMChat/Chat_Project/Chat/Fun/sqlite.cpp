#include "sqlite.h"
#include <QDebug>
SQLite::SQLite()
{
    connect_sql();
    insert_sql = "insert into chatRecord values (?,?,?,?,?)";
}
SQLite::~SQLite()
{
    if(closed == false)
        database.close();
}
void SQLite::connect_sql()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("root");
        database.setPassword("asd123456");
    }
    create_table();
}
void SQLite::create_table()
{
    if(!database.open())
        return ;
    sql_query = QSqlQuery(database);
    if(IsTableExist(sql_query,"chatRecord"))
    {
        sql_query.prepare("drop table chatRecord");
        if(!sql_query.exec())
            return;
    }
    QString sql = "create table chatRecord (selfname varchar(20) ,fromemail varchar(20),fromname varchar(20),content text, time varchar(20))";
    sql_query.prepare(sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
        return;
    }
}
bool SQLite:: IsTableExist(QSqlQuery &query,QString table)
{
   QString sql = QString("select * from sqlite_master where name='%1'").arg(table);
   query.exec(sql);
   return query.next();
}

bool SQLite::insert_data(const QString &user, const std::pair<QString, QString> &fromUser, const QString& content,const QString &time)
{
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(user);
    sql_query.addBindValue(fromUser.first);
    sql_query.addBindValue(fromUser.second);
    sql_query.addBindValue(content);
    sql_query.addBindValue(time);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
        return false;
    }
    qDebug()<<"insert sus";
    return true;
}
findVector SQLite::search_data(const QString& user)
{
    QString select_sql = QString("select fromemail,fromname,content,time from chatRecord where fromemail = '%1'").arg(user);

    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    findVector result;
    while(sql_query.next())
    {
        QString email = sql_query.value(0).toString();
        QString name = sql_query.value(1).toString();
        QString str = sql_query.value(2).toString();
        QString time = sql_query.value(3).toString();
        result.push_back({{email,name},{str,time}});
    }
    return result;
}
void SQLite::close_sql()
{
   database.close();
   closed = true;
}








