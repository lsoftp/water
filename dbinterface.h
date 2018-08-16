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
#include "cadlg.h"
#include "qudlg.h"


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

struct Cadetail
{
    int TestID;
    QString name;
    QString type;
    int num;
    QString kvalue;
    QString testtimes;
    QString caname0;
    QString con0;
    QString dilute0;
    QString con01;
    QString caname1;
    QString con1;
    QString dilute1;
    QString con11;
    QString caname2;
    QString con2;
    QString dilute2;
    QString con21;
    QString caname3;
    QString con3;
    QString dilute3;
    QString con31;
    QString caname4;
    QString con4;
    QString dilute4;
    QString con41;
    QString caname5;
    QString con5;
    QString dilute5;
    QString con51;
    QString caname6;
    QString con6;
    QString dilute6;
    QString con61;
    QString caname7;
    QString con7;
    QString dilute7;
    QString con71;
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
    void insertCadetail(const Cadetail & ca);
    void getItem(QSqlQueryModel &querymodel);
    //void getItemInfo()
    void getItembyname(QSqlQueryModel &querymodel,QString &name);
    void getalltest(QSqlQueryModel &querymodel,const QString &index);//获取所有登记的测试
    void gettestindex(QSqlQueryModel &querymodel);

    void getSrbyid(QSqlQueryModel &querymodel, const QString &index, QString &id);
    void delSrbyid( const QString &index, QString &id);
    void delItembyName(const QString &name);
    void getReagent(QSqlQueryModel &querymodel);
    void getItemNo(QSqlQueryModel &querymodel);
    void getCaye(QSqlQueryModel &querymodel);
    void delCayebyName(QString name);
    void updateCayeByName(QString name ,QString n1,QString no,QString valid);

    void insertCaye(CaDlg & cd);//添加定标液
    //void insertzhikongye(QuDlg &cd);//添加质控液

    void insertCayeItem(QString name,QString testname,QString con, QString unit);
    void getCayeItem(QSqlQueryModel &querymodel,QString name);
    void updateCayeItemByName(QString name,QString n1,QString n2,QString con,QString unit);
    void delCayeItem(QString name, QString n1);

    void getzhikong(QSqlQueryModel &querymodel);
    void delzhikongbyName(QString name);
    void updatezhikongByName(QString name ,QString n1,QString no,QString valid);


    void insertzhikongye(QuDlg &cd);//添加质控液

    void insertzhikongItem(QString name,QString testname,QString con, QString unit);
    void getzhikongItem(QSqlQueryModel &querymodel,QString name);
    void updatezhikongItemByName(QString name,QString n1,QString n2,QString con,QString unit);
    void delzhikongItem(QString name, QString n1);
signals:

public slots:

};

extern DBInterface db;
extern DBInterface dbhandle;
#endif // DBINTERFACE_H
