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
#include "mainwindow.h"
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
    //m_db.setDatabaseName("water");
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

void DBInterface::getTestItem(QSqlQueryModel &querymodel)
{
    //QSqlQueryModel querymodel;
    querymodel.setQuery("SELECT * FROM item ",m_db);




 qDebug()<<"&&&&&&&& threadid "<<QThread::currentThreadId()<<  endl;
}


void DBInterface::getPos(QSqlQueryModel &querymodel,const QString &index)//获取已占用位置
{
    querymodel.setQuery(QString("SELECT distinct Pos FROM raw_sr where testpageid='%1' order by pos").arg(index),m_db);
}
void DBInterface::getSampleNo(QSqlQueryModel &querymodel,const QString &index)//获取已用样本号
{
    QString sql=QString("SELECT id  FROM raw_sr where testpageid='%1' order by id").arg(index);
    querymodel.setQuery(sql,m_db);
}
void DBInterface::getSampleId(QSqlQueryModel &querymodel,const QString &index)//获取已用样品Id
{
    querymodel.setQuery(QString("SELECT sampleid  FROM raw_sr where testpageid='%1' order by sampleid").arg(index),m_db);
}

void DBInterface::getalltest(QSqlQueryModel &querymodel,const QString &index)
{
    querymodel.setQuery(QString("SELECT *  FROM raw_sr where testpageid='%1' order by sampleid").arg(index),m_db);

}

void DBInterface::gettestindex(QSqlQueryModel &querymodel)
{
    querymodel.setQuery(QString("SELECT testpageid  FROM raw_sr where  order by testpageid desc limit 7"),m_db);

}

void DBInterface::getSr(QSqlQueryModel &querymodel,const QString &index)
{
    querymodel.setQuery(QString("SELECT distinct id,Pos,Stage  FROM raw_sr where testpageid='%1' AND (Stage!=1 ) order by id").arg(index),m_db);
}

void DBInterface::getSrbyid(QSqlQueryModel &querymodel,const QString &index,QString &id)
{
    querymodel.setQuery(QString("SELECT * from raw_sr where id=%1 and testpageid='%2'  ").arg(id.toInt()).arg(index));
}

void DBInterface::delSrbyid(const QString &index, QString &id)
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2'  ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("DELETE  from raw_sr where id=%1 and testpageid='%2'  ").arg(id.toInt()).arg(index));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::insertSample(const TestRegister & tr )
{
    QSqlQuery query(m_db);
    QString p;

    query.prepare("insert  into raw_sr values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    p=QString::fromStdString(tr.tr.test_row_id);

    query.bindValue(0,p);
    query.bindValue(1,g_current_index);
    query.bindValue(2,tr.no);
    query.bindValue(3,tr.id);
    query.bindValue(4,tr.sampleid);
    query.bindValue(5,tr.pre_dilute);
    query.bindValue(6,tr.pre_d_times);
    query.bindValue(7,tr.tr.position);
    query.bindValue(8,tr.tr.sample_cup_type);
    query.bindValue(9,tr.tr.priority);//是否加急
    query.bindValue(10,tr.tr.test_type);
    query.bindValue(11,tr.qname);
    query.bindValue(12,tr.cname);
    query.bindValue(13,tr.tr.test_id);//-1 if is a combo test
    query.bindValue(14,tr.tr.status);
    query.bindValue(15,tr.combinetestname); //"" if just a common test

    bool success = query.exec();
           //qDebug() <<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<t;
  //  qDebug<<phone<<"  "<<msgid<<" "<<t<<" "<<s3;
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        //qDebug() << a1 << a2<< a3;
        //qDebug << a1 << "  " << a2 << " " << t << " " << a3;

        return;
    }

}
