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
    querymodel.setQuery("SELECT * FROM item order by name",m_db);




    qDebug()<<"&&&&&&&& threadid "<<QThread::currentThreadId()<<  endl;
}


void DBInterface::getPos(QSqlQueryModel &querymodel,const QString &index)//获取已占用位置
{
    querymodel.setQuery(QString("SELECT distinct Pos FROM raw_sr where testpageid='%1' order by pos").arg(index),m_db);
}
void DBInterface::getSampleNo(QSqlQueryModel &querymodel,const QString &index)//获取已用样本号
{
    QString sql=QString("SELECT id  FROM raw_sr where testpageid='%1' and Testtype=4  order by id").arg(index);
    querymodel.setQuery(sql,m_db);
}
void DBInterface::getCaNo(QSqlQueryModel &querymodel,const QString &index)//获取已用定标样本号
{
    QString sql=QString("SELECT id  FROM raw_sr where testpageid='%1' and Testtype<3  order by id").arg(index);
    querymodel.setQuery(sql,m_db);
}

void DBInterface::getQuNo(QSqlQueryModel &querymodel,const QString &index)//获取已用指控样本号
{
    QString sql=QString("SELECT id  FROM raw_sr where testpageid='%1' and Testtype=3  order by id").arg(index);
    querymodel.setQuery(sql,m_db);
}

void DBInterface::getItemNo(QSqlQueryModel &querymodel)//获取已用测试项目号
{
    QString sql=QString("SELECT TestID  FROM item  order by TestID");
    querymodel.setQuery(sql,m_db);
}

void DBInterface::getCaye(QSqlQueryModel &querymodel)
{
    QString sql=QString("SELECT *  FROM biaozhunye  order by name");
    querymodel.setQuery(sql,m_db);
}

void DBInterface::delCayebyName(QString name)
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2'  ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    query.prepare(QString("DELETE  from biaozhunye where name='%1'  ").arg(name));
    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::updateCayeByName(QString name, QString n1, QString no, QString valid)
{

    QSqlQuery query(m_db);

    query.prepare(QString("UPDATE `biaozhunye` SET `name`='%1' ,`no`='%2',`valid`='%3' WHERE  `name`='%4'").arg(n1).arg(no).arg(valid).arg(name));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }

}
//添加标准液
void DBInterface::insertCaye(CaDlg &cd)
{
    QSqlQuery query(m_db);
    //QString p;

    query.prepare("insert  into biaozhunye values(?,?,?)");


    query.bindValue(0,cd.name);
    query.bindValue(1,cd.no);
    query.bindValue(2,cd.valid);
    //query.bindValue(15,tr.combinetestname); //"" if just a common test

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

void DBInterface::insertzhikongye(QuDlg &cd)
{
    QSqlQuery query(m_db);
    //QString p;

    query.prepare("insert  into zhikongye values(?,?,?)");


    query.bindValue(0,cd.name);
    query.bindValue(1,cd.no);
    query.bindValue(2,cd.valid);
    //query.bindValue(15,tr.combinetestname); //"" if just a common test

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

void DBInterface::insertzhikongItem(QString name, QString testname, QString con, QString unit)
{
    QSqlQuery query(m_db);

    query.prepare("insert  into zhikongye1 values(?,NULL,?,?,?)");


    query.bindValue(0,name);
    query.bindValue(1,testname);
    query.bindValue(2,con);
    query.bindValue(3,unit);

    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();

        return;
    }


}

void DBInterface::getzhikongItem(QSqlQueryModel &querymodel, QString name)
{
    querymodel.setQuery(QString("SELECT *  FROM zhikongye1 where name='%1' order by TestName").arg(name),m_db);
}

void DBInterface::updatezhikongItemByName(QString name, QString n1, QString n2, QString con, QString unit)
{
    QSqlQuery query(m_db);

    query.prepare(QString("UPDATE `zhikongye1` SET `TestName`='%1' ,`con`='%2',`unit`='%3' WHERE  `name`='%4' AND `TestName`='%5'").arg(n2).arg(con).arg(unit).arg(name).arg(n1));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::delzhikongItem(QString name, QString n1)
{
    QSqlQuery query(m_db);
    query.prepare(QString("DELETE  from zhikongye1 where name='%1' and TestName='%2' ").arg(name).arg(n1));
    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }}

void DBInterface::getCacurveSetting(QSqlQueryModel &querymodel)
{
    querymodel.setQuery(QString("SELECT name  FROM cadetail   order by name"),m_db);
}

void DBInterface::insertCayeItem(QString name, QString testname, QString con, QString unit)
{
    QSqlQuery query(m_db);

    query.prepare("insert  into biaozhunye1 values(?,NULL,?,?,?)");


    query.bindValue(0,name);
    query.bindValue(1,testname);
    query.bindValue(2,con);
    query.bindValue(3,unit);

    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();

        return;
    }

}

void DBInterface::getCayeItem(QSqlQueryModel &querymodel,QString name)
{
    querymodel.setQuery(QString("SELECT *  FROM biaozhunye1 where name='%1' order by TestName").arg(name),m_db);
}

void DBInterface::updateCayeItemByName(QString name, QString n1, QString n2, QString con, QString unit)
{
    QSqlQuery query(m_db);

    query.prepare(QString("UPDATE `biaozhunye1` SET `TestName`='%1' ,`con`='%2',`unit`='%3' WHERE  `name`='%4' AND `TestName`='%5'").arg(n2).arg(con).arg(unit).arg(name).arg(n1));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::delCayeItem(QString name, QString n1)
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2'  ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    query.prepare(QString("DELETE  from biaozhunye1 where name='%1' and TestName='%2' ").arg(name).arg(n1));
    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::getzhikong(QSqlQueryModel &querymodel)
{
    QString sql=QString("SELECT *  FROM zhikongye  order by name");
    querymodel.setQuery(sql,m_db);
}

void DBInterface::delzhikongbyName(QString name)
{
    QSqlQuery query(m_db);
    query.prepare(QString("DELETE  from zhikongye where name='%1'  ").arg(name));
    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::updatezhikongByName(QString name, QString n1, QString no, QString valid)
{

    QSqlQuery query(m_db);

    query.prepare(QString("UPDATE `zhikongye` SET `name`='%1' ,`no`='%2',`valid`='%3' WHERE  `name`='%4'").arg(n1).arg(no).arg(valid).arg(name));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }

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
    querymodel.setQuery(QString("SELECT distinct id,Pos,Stage  FROM raw_sr where testpageid='%1' AND (Stage= 0 ) and Testtype=4 order by id").arg(index),m_db);
}


void DBInterface::getCa(QSqlQueryModel &querymodel,const QString &index)
{
    querymodel.setQuery(QString("SELECT distinct no, id,Pos,Caname,Stage  FROM raw_sr where testpageid='%1' AND (Stage= 0 ) and Testtype<3 order by id").arg(index),m_db);
}

void DBInterface::getQu(QSqlQueryModel &querymodel,const QString &index)
{
    querymodel.setQuery(QString("SELECT distinct no, id,Pos, Qualityname,Stage  FROM raw_sr where testpageid='%1' AND (Stage= 0 ) and Testtype=3 order by id").arg(index),m_db);
}
void DBInterface::getSrbyid(QSqlQueryModel &querymodel,const QString &index,QString &id)
{
    querymodel.setQuery(QString("SELECT * from raw_sr where id=%1 and Testtype=4 and testpageid='%2'  ").arg(id.toInt()).arg(index));
}
void DBInterface::getCabyid(QSqlQueryModel &querymodel,const QString &index,QString &id)
{
    querymodel.setQuery(QString("SELECT * from raw_sr where no='%1' and Testtype<3 and testpageid='%2'  ").arg(id).arg(index));
}

void DBInterface::getQubyid(QSqlQueryModel &querymodel,const QString &index,QString &id)
{
    querymodel.setQuery(QString("SELECT * from raw_sr where no='%1' and Testtype=3 and testpageid='%2'  ").arg(id).arg(index));
}
void DBInterface::delSrbyid(const QString &index, QString &id)
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2' and Testtype=4 ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("DELETE  from raw_sr where id=%1 and testpageid='%2'  and Testtype=4 ").arg(id.toInt()).arg(index));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::delCabyid(const QString &index, QString &id)
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2' and Testtype=4 ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("DELETE  from raw_sr where no='%1' and testpageid='%2'  and Testtype<3 ").arg(id).arg(index));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}
void DBInterface::delQubyid(const QString &index, QString &id)
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2' and Testtype=4 ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("DELETE  from raw_sr where no='%1' and testpageid='%2'  and Testtype=3 ").arg(id.toInt()).arg(index));



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

    query.prepare("insert  into raw_sr values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
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
    //query.bindValue(15,tr.combinetestname); //"" if just a common test

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

void DBInterface::insertItem(const Item &it)
{
    QSqlQuery query(m_db);
    QString p;

    query.prepare("insert  into item values("
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?"
                  ",?,?,?,?,?,?,?,?,?)");
    query.bindValue(0,it.tc.test_id);
    query.bindValue(1,it.name);
    query.bindValue(2,it.fullname);
    query.bindValue(3,it.tc.reagent0);
    query.bindValue(4,it.tc.time0);
    query.bindValue(5,it.tc.v0);
    query.bindValue(6,it.tc.reagent1);
    query.bindValue(7,it.tc.time1);
    query.bindValue(8,it.tc.v1);
    query.bindValue(9,it.tc.reagent2);
    query.bindValue(10,it.tc.time2);
    query.bindValue(11,it.tc.v2);
    query.bindValue(12,it.tc.reagent3);
    query.bindValue(13,it.tc.time3);

    query.bindValue(14,it.tc.v3);
    query.bindValue(15,it.tc.reagent4);
    query.bindValue(16,it.tc.time4);
    query.bindValue(17,it.tc.v4);

    query.bindValue(18,it.tc.priority);
    query.bindValue(19,it.tc.isreplace);
    query.bindValue(20,it.tc.repalcereagentid);
    query.bindValue(21,it.tc.method);
    query.bindValue(22,it.tc.readstep);
    query.bindValue(23,it.tc.readinterval);
    query.bindValue(24,it.tc.readtimes);
    query.bindValue(25,it.tc.wavenum);
    query.bindValue(26,it.tc.wl0);
    query.bindValue(27,it.tc.wl1);
    query.bindValue(28,it.digitnum);
    query.bindValue(29,it.unit);
    query.bindValue(30,it.checkmethod);
    query.bindValue(31,it.limitlow);
    query.bindValue(32,it.limitlowjudge);
    query.bindValue(33,it.limithigh);
    query.bindValue(34,it.limithighjudge);
    query.bindValue(35,it.linearlow);
    query.bindValue(36,it.linearhigh);
    query.bindValue(37,it.correctA);
    query.bindValue(38,it.correctB);
    query.bindValue(39,it.xgdlimit);
    query.bindValue(40,it.xgdlimitvalue);
    query.bindValue(41,it.kbxgd);
    query.bindValue(42,it.kbxgd1);
    query.bindValue(43,it.kbxgd2);
    query.bindValue(44,it.xxd);
    query.bindValue(45,it.xxdvalue);
    query.bindValue(46,it.redodiluteid);
    query.bindValue(47,it.redoxxfflow);
    query.bindValue(48,it.redoxxffhigh);
    query.bindValue(49,it.redoxxfftimes);
    query.bindValue(50,it.redodilute1low);
    query.bindValue(51,it.redodilute1high);
    query.bindValue(52,it.redodilute1times);
    query.bindValue(53,it.redodilute2low);
    query.bindValue(54,it.redodilute2high);
    query.bindValue(55,it.redodilute2times);
    query.bindValue(56,it.redootherlow);
    query.bindValue(57,it.redootherhigh);
    query.bindValue(58,it.redoothertimes);
    qDebug()<<query.lastQuery();
    bool success = query.exec();
    //qDebug() <<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<t;
    //  qDebug<<phone<<"  "<<msgid<<" "<<t<<" "<<s3;
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        //qDebug() << a1 << a2<< a3;
        qDebug()<<query.lastQuery();
        //qDebug << a1 << "  " << a2 << " " << t << " " << a3;

        return;
    }
}

void DBInterface::insertCadetail(const Cadetail &ca)
{
    QSqlQuery query(m_db);
    QString p;

    query.prepare("insert  into cadetail values("
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?,?,?,"
                  "?,?,?,?,?,?,?,?)");
    query.bindValue(0,ca.TestID);
    query.bindValue(1,ca.name);
    query.bindValue(2,ca.type);
    query.bindValue(3,ca.num);
    query.bindValue(4,ca.kvalue);
    query.bindValue(5,ca.testtimes);
    query.bindValue(6,ca.caname0);
    query.bindValue(7,ca.con0);
    query.bindValue(8,ca.dilute0);
    query.bindValue(9,ca.con01);
    query.bindValue(10,ca.caname1);
    query.bindValue(11,ca.con1);
    query.bindValue(12,ca.dilute1);
    query.bindValue(13,ca.con11);

    query.bindValue(14,ca.caname2);
    query.bindValue(15,ca.con2);
    query.bindValue(16,ca.dilute2);
    query.bindValue(17,ca.con21);

    query.bindValue(18,ca.caname3);
    query.bindValue(19,ca.con3);
    query.bindValue(20,ca.dilute3);
    query.bindValue(21,ca.con31);
    query.bindValue(22,ca.caname4);
    query.bindValue(23,ca.con4);
    query.bindValue(24,ca.dilute4);
    query.bindValue(25,ca.con41);
    query.bindValue(26,ca.caname5);
    query.bindValue(27,ca.con5);
    query.bindValue(28,ca.dilute5);
    query.bindValue(29,ca.con51);
    query.bindValue(30,ca.caname6);
    query.bindValue(31,ca.con6);
    query.bindValue(32,ca.dilute6);
    query.bindValue(33,ca.con61);
    query.bindValue(34,ca.caname7);
    query.bindValue(35,ca.con7);
    query.bindValue(36,ca.dilute7);
    query.bindValue(37,ca.con71);

    qDebug()<<query.lastQuery();
    bool success = query.exec();
    //qDebug() <<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<t;
    //  qDebug<<phone<<"  "<<msgid<<" "<<t<<" "<<s3;
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        //qDebug() << a1 << a2<< a3;
        qDebug()<<query.lastQuery();
        //qDebug << a1 << "  " << a2 << " " << t << " " << a3;

        return;
    }

}

void DBInterface::getItem(QSqlQueryModel &querymodel)
{
    querymodel.setQuery(QString("SELECT name  FROM item order by name"),m_db);
}

void DBInterface::getItembyname(QSqlQueryModel &querymodel, QString &name)
{
    querymodel.setQuery(QString("SELECT *  FROM item where name='%1'").arg(name),m_db);
}

void DBInterface::getCadetailbyname(QSqlQueryModel &querymodel, QString &name)
{
    querymodel.setQuery(QString("SELECT *  FROM cadetail where name='%1'").arg(name),m_db);
}

void DBInterface::delItembyName(const QString &name)
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2'  ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("DELETE  from item where name='%1'  ").arg(name));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::delCadetailbyName(const QString &name)
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2'  ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("DELETE  from cadetail where name='%1'  ").arg(name));



    bool success = query.exec();
    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return;
    }
}

void DBInterface::getReagent(QSqlQueryModel &querymodel)
{
    querymodel.setQuery(QString("SELECT *  FROM reagent where id>=-3 order by id"),m_db);
}

int  DBInterface::getSampleCount( const QString &index)//获取总样本数量
{
    //querymodel.setQuery(QString("DELLET  from raw_sr where id=%1 and testpageid='%2'  ").arg(id.toInt()).arg(index));
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("SELECT count( DISTINCT no) as i from raw_sr where testpageid='%1'and Stage=0 ").arg(index));



    bool success = query.exec();

    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return -1;
    }
    else
    {
        query.first();
        return query.value(0).toInt();
    }


}

int  DBInterface::getKBCount( const QString &index)//获取空白数量
{
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("SELECT count( DISTINCT no,TestID) as i from raw_sr where testpageid='%1' and Testtype<3 and Stage=0").arg(index));



    bool success = query.exec();

    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return -1;
    }
    else
    {
        query.first();
        return query.value(0).toInt();
    }

}

int  DBInterface::getCaCount(const QString &index)//获取定标数量
{
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("SELECT count( DISTINCT no,TestID) as i from raw_sr where testpageid='%1' and Testtype=2 and Stage=0").arg(index));



    bool success = query.exec();

    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return -1;
    }
    else
    {
        query.first();
        return query.value(0).toInt();
    }

}
int DBInterface::getQuCount(const QString &index)
{
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("SELECT count( DISTINCT no,TestID) as i from raw_sr where testpageid='%1' and Testtype=3 and Stage=0").arg(index));



    bool success = query.exec();

    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return -1;
    }
    else
    {
        query.first();
        return query.value(0).toInt();
    }
}


int  DBInterface::getNormalCount( const QString &index)//获取常规数量
{
    QSqlQuery query(m_db);
    // 插入数据user
    query.prepare(QString("SELECT count( DISTINCT no,TestID) as i from raw_sr where testpageid='%1' and Testtype=4 and Stage=0").arg(index));



    bool success = query.exec();

    if(!success){
        QSqlError lastError = query.lastError();
        qDebug() << "插入失败：" << lastError.driverText() << lastError.databaseText();
        return -1;
    }
    else
    {
        query.first();
        return query.value(0).toInt();
    }

}
