#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
//#include <datastruct.h>
#include <QTime>
#include <QTimer>



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

signals:

public slots:

};

extern DBInterface db;
extern DBInterface dbhandle;
#endif // DBINTERFACE_H
