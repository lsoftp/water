#include "sampleregister.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

SampleRegister::SampleRegister(QObject *p)
    :QObject(p)
    ,w(qobject_cast<MainWindow*>(p))
{

}
void SampleRegister::SetSampleNo()
{
   //w->ui->pushButton_8->setEnabled(false);
    //Ui::MainWindow *ppp=w->ui;
//ppp->pushButton_8->setEnabled(false);
}
void SampleRegister::setYesEnable(bool b)
{
    w->ui->pushButton_8->setEnabled(b);
}

void SampleRegister::initsabutton()
{
    QWidget *qw=w->ui->frame_4;
    //qw->deleteLater();
    QSqlQueryModel sqm;
    db.getTestItem(sqm);
    for (int i=0;i<38;i++)
    {
        if(w->pb[i]!=NULL) {delete w->pb[i];
        w->pb[i]=NULL;}
    }
    for(int i=0;i<11;i++)
    {
        w->pb[i]= new ItemButton(qw);
        w->setbutton(i,w->pb,sqm);
        w->pb[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        w->pb[i]= new ItemButton(qw);
        w->setbutton(i,w->pb,sqm);
        w->pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        w->pb[i]= new ItemButton(qw);
        w->setbutton(i,w->pb,sqm);
        w->pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        w->pb[i]= new ItemButton(qw);
        w->setbutton(i,w->pb,sqm);
        w->pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }

}
