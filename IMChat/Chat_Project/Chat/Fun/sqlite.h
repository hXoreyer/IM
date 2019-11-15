#ifndef SQLITE_H
#define SQLITE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
using findVector =  QVector<std::pair<std::pair<QString,QString>,std::pair<QString,QString>>>;
class SQLite
{
public:
    SQLite();
    ~SQLite();
    void connect_sql();
    void create_table();
    bool insert_data(const QString &user, const std::pair<QString, QString> &fromUser, const QString& content,const QString &time);
    void close_sql();
    findVector search_data(const QString& user);
    bool IsTableExist(QSqlQuery &query,QString table);
private:
    QSqlDatabase database;
    QSqlQuery sql_query;
    QString insert_sql;
    bool closed;
};

#endif // SQLITE_H
