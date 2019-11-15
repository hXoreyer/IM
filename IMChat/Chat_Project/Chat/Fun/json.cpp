#include "json.h"
#include <QDebug>
JSON::JSON()
{
}
JSON::~JSON()
{
    if(closed == false)
        m_file.close();
}
bool JSON::openJson()
{
    m_file.setFileName("1.json");
    if(!m_file.open(QIODevice::ReadWrite))
    {
        return false;
    }
    return true;
}
void JSON::insertValue(const QString& user,const std::pair<QString,QString>& str,const QString& time)
{

    QJsonObject jsonObject;
    qDebug()<<user<<str.first<<str.second<<time;
    jsonObject.insert("user",user);
    jsonObject.insert("fromUser",str.first);
    jsonObject.insert("content",str.second);
    jsonObject.insert("time",time);

    m_jsonArray.append(jsonObject);
    m_jsonDoc.setArray(m_jsonArray);

    m_file.write(m_jsonDoc.toJson());
}
void JSON::getValue()
{

}
void JSON::close()
{
    m_file.close();
    closed = true;
    if(m_file.isOpen())
        closed = false;
}
