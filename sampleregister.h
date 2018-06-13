#ifndef SAMPLEREGISTER_H
#define SAMPLEREGISTER_H
#include <QObject>

class MainWindow;
class SampleRegister:public QObject
{
public:
    SampleRegister(QObject *p);
    void SetSampleNo();
    void initsabutton();
    void setYesEnable(bool b);
    MainWindow *w;
};

#endif // SAMPLEREGISTER_H
