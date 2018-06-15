#include "sampleregister.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myprocess.h"

SampleRegister::SampleRegister(QObject *p)
    :QObject(p)
    ,w(qobject_cast<MainWindow*>(p))
{

}
void SampleRegister::SetSampleNo()
{
    QSqlQueryModel sqm;
    db.getSampleNo(sqm, g_current_index);
    int j=0,num=sqm.rowCount();
    if(num==0)
    {
        w->ui->lineEdit_4->setText(QString::number(1));
        return;
    }
    for(int i=0;i<num;i++)
    {
        int k=sqm.record(i).value("id").toInt();
        int p=k-j;

        if(p>1)
        {
            w->ui->lineEdit_4->setText(QString::number(j+1));
            return;
        }
        j=k;
    }
    w->ui->lineEdit_4->setText(QString::number(j+1));
}

void SampleRegister::SetPos()
{
    w->ui->comboBox_2->clear();
    QSqlQueryModel sqm;
    db.getPos(sqm, g_current_index);
    for(int i=0;i<40;i++)
    {
        w->ui->comboBox_2->addItem(QString::number(i+1));
    }
    for(int j=0;j<sqm.rowCount();j++)
    {
        QString num=sqm.record(j).value("pos").toString();
        int index=w->ui->comboBox_2->findText(num);
        if(index!=-1)
        {
            w->ui->comboBox_2->removeItem(index);
        }
    }
    w->ui->comboBox_2->setCurrentIndex(0);
    //w->ui->comboBox_2->currentData()

}

void SampleRegister::setYesEnable(bool b)
{
    w->ui->sr_yes->setEnabled(b);
}

void SampleRegister::uncheckbt()
{
    for(int i=0;i<w->itemnum;i++)
    {
        w->pb[i]->setChecked(false);
    }
}

void SampleRegister::setbutton()
{
    QSqlQueryModel sqm;
    db.getTestItem(sqm);
    w->itemnum=sqm.rowCount();
    for(int i=0;i<sqm.rowCount();i++)

    {

        QString name=sqm.record(i).value("Name").toString();
        int   testid=sqm.record(i).value("TestId").toInt();

        w->pb[i]->setText(name);
        w->pb[i]->testid=testid;

        w->pb[i]->setEnabled(true);
        w->pb[i]->setCheckable(true);
        connect(w->pb[i],SIGNAL(toggled(bool)),g_w,SLOT(ontoggle(bool)));
    }



}
void SampleRegister::refreshtable()
{
    QSqlQueryModel sqm;
    db.getSr(sqm,::g_current_index);
    QTableWidget *tw=w->ui->tableWidget;
    tw->clearContents();
    for(int i=0;i<sqm.rowCount();i++)
    {
      tw->setItem(i,0,new QTableWidgetItem(sqm.record(i).value("id").toString()));
      tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("Pos").toString()));
      int k = sqm.record(i).value("Stage").toInt();
      QString status= k==0?"已登记":"其他";
      tw->setItem(i,2,new QTableWidgetItem(status));

    }

}

void SampleRegister::showpage(int i)
{
    if(!i) {
        w->ui->frame_4->show();
        w->ui->frame_10->hide();
    }
    else
    {
        w->ui->frame_4->hide();
        w->ui->frame_10->show();

    }
}

void SampleRegister::initstate()
{
    //page 1
    w->ui->comboBox_4->setCurrentIndex(0);

    showpage(0);
    setYesEnable(false);
    this->uncheckbt();
    this->SetSampleNo();
    SetPos();
    this->refreshtable();
}

void SampleRegister::reg()
{
   TestRegister t;
   QDateTime now=QDateTime::currentDateTime();

   t.id=w->ui->lineEdit_4->text().toInt();
   //t.tr.test_row_id=QDateTime::currentDateTime().toString()
   t.no=QString::number(t.id);
   t.sampleid=w->ui->lineEdit_6->text();
   t.pre_dilute=w->ui->checkBox->isChecked();
   t.pre_d_times=w->ui->lineEdit_5->text().toInt();
   t.tr.position=w->ui->comboBox_2->currentText().toInt();
   t.tr.sample_cup_type=w->ui->comboBox_3->currentIndex();
   t.tr.priority=!(w->ui->checkBox_2->isChecked());
   t.tr.test_type=4;
   t.qname="";
   t.cname="";
   t.tr.isdilute=0;
   t.tr.status=0;
   //初始化  g_current_index 在全局变量中
   //还有test_row_id ,isreplace, test_id
   int j=0;
   for(int i=0;i<w->itemnum;i++)
   {
       if(w->pb[i]->isChecked())
       {
           //insert
           QString tempid =now.toString("yyyyMMddhhmmss")+QString("%1").arg(j,3,10,QChar('0'));
           //if test_id isreplace add two rows
           t.tr.test_row_id=tempid.toStdString();
           t.tr.isreplace=0;
           t.tr.test_id=w->pb[i]->testid;
           db.insertSample(t);
           j++;
           if(gi::isReplace(w->pb[i]->testid))
           {
               tempid =now.toString("yyyyMMddhhmmss")+QString("%1").arg(j,3,10,QChar('0'));
               t.tr.isreplace=1;
               db.insertSample(t);
               j++;
           }

           //
       }
   }

}
