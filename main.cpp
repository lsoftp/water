#include "mainwindow.h"
#include <QApplication>
#include "dbinterface.h"


DBInterface db;
DBInterface dbhandle;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    db.open();
    dbhandle.open1();
    return a.exec();
}
