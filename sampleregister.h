#ifndef SAMPLEREGISTER_H
#define SAMPLEREGISTER_H
#include <QObject>
#include "itembutton.h"
#include "dbinterface.h"
class MainWindow;
class SampleRegister:public QObject
{
    Q_OBJECT

public:

    SampleRegister(QObject *p);
    void SetSampleNo();
    void SetPos();

    void setYesEnable(bool b);
    MainWindow *w;
    void setbutton();
    void showpage(int i);
    void initstate();
    void uncheckbt();
    void refreshtable();
    void reg();
};

#endif // SAMPLEREGISTER_H
