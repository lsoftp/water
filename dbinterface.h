#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <myprocess.h>
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
#include <QString>

struct  TestRegister{
    TestRow tr;
    int id;
    QString no;
    QString sampleid;
    int pre_dilute;
    int pre_d_times;
    QString qname;
    QString cname;
    //QString combinetestname;//组合项目名称
};

struct Item{
    TestConfig tc;
    QString name;
    QString fullname;
    QString digitnum;
    QString unit;
    QString checkmethod;
    QString limitlow;
    QString limitlowjudge;
    QString limithigh;
    QString limithighjudge;
    QString linearlow;
    QString linearhigh;
    QString correctA;
    QString correctB;
    int xgdlimit;
    QString xgdlimitvalue;
    int kbxgd;
    QString kbxgd1;
    QString kbxgd2;
    int  xxd;
    QString xxdvalue;

    int redodiluteid;
    QString redoxxfflow;
    QString redoxxffhigh;
    QString redoxxfftimes;
    QString redodilute1low;
    QString redodilute1high;
    QString redodilute1times;
    QString redodilute2low;
    QString redodilute2high;
    QString redodilute2times;
    QString redootherlow;
    QString redootherhigh;
    QString redoothertimes;
};




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
    void getSr(QSqlQueryModel &querymodel,const QString &index);//获取最后登记进去的样本号
    void insertSample(const TestRegister & tr );
    void insertItem(const Item &it);//添加项目
    void getalltest(QSqlQueryModel &querymodel,const QString &index);//获取所有登记的测试
    void gettestindex(QSqlQueryModel &querymodel);

    void getSrbyid(QSqlQueryModel &querymodel, const QString &index, QString &id);
    void delSrbyid( const QString &index, QString &id);
signals:

public slots:

};

extern DBInterface db;
extern DBInterface dbhandle;
#endif // DBINTERFACE_H
