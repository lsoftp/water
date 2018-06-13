#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
//#include <datastruct.h>
#include <QTime>
#include <QTimer>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>
#include <qsqlrecord.h>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QByteArray>
#include <QThread>


class DBInterface : public QObject
{
    Q_OBJECT
public:
    QTimer qtimer;
    QString a1[100],a2[100],a3[100],tt[100];
    int num=0,size =0;
    explicit DBInterface(QObject *parent = 0);
    QSqlDatabase m_db;
    void open();
    void open1();
    void getTestItem(QSqlQueryModel &querymodel);// 获取项目列表
    void getPos(QSqlQueryModel &querymodel,const QString &index);//获取已占用位置
    void getSampleNo(QSqlQueryModel &querymodel,const QString &index);//获取已用样本号
    void getSampleId(QSqlQueryModel &querymodel,const QString &index);//获取已用样品Id


signals:

public slots:

};

extern DBInterface db;
extern DBInterface dbhandle;
#endif // DBINTERFACE_H
