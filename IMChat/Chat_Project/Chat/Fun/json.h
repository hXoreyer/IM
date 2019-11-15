#ifndef JSON_H
#define JSON_H
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QDir>
#include <QThread>
class JSON
{
public:
    JSON();
    ~JSON();
    bool openJson();
    void insertValue(const QString& user,const std::pair<QString,QString>& str,const QString& time);
    void getValue();
    void close();
private:
    QJsonArray m_jsonArray;
    QJsonDocument m_jsonDoc;
    bool closed;
    QFile m_file;
};

#endif // JSON_H
