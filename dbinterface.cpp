#include "dbinterface.h"
//#include "dbhandle.h"
#include <qsqlquery.h>
#include <qsqlquerymodel.h>
#include <qsqlrecord.h>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QByteArray>
#include <QThread>
DBInterface::DBInterface(QObject *parent) :
    QObject(parent)
{
}
void DBInterface::open1()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL","handler");
    QString qs =m_db.lastError().text();
    qDebug(qs.toLatin1().data());
    m_db.setHostName("localhost");
    m_db.setDatabaseName("water");
    m_db.setUserName("root");
    m_db.setPassword("123456");
    m_db.setConnectOptions("MYSQL_OPT_RECONNECT=1");
    bool b =m_db.open();
    qDebug("&&&&&&&&&&&&&&&&&&&%d\n",b);
     qs =m_db.lastError().text();
    if(!b) qDebug(qs.toLatin1().data());
   // qtimer = new QTimer(this);
}
void DBInterface::open()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    QString qs =m_db.lastError().text();
    qDebug(qs.toLatin1().data());
    m_db.setHostName("localhost");
    m_db.setDatabaseName("water");
    m_db.setUserName("root");
    m_db.setPassword("123456");
    m_db.setConnectOptions("MYSQL_OPT_RECONNECT=1");
    bool b =m_db.open();
    qDebug("&&&&&&&&&&&&&&&&&&&%d\n",b);
     qs =m_db.lastError().text();
    if(!b) qDebug(qs.toLatin1().data());
   // qtimer = new QTimer(this);
}
