#include "srtab.h"
#include "ui_srtab.h"
#include "mainwindow.h"

SrTab::SrTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SrTab)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(40);
    ui->tableWidget->setColumnWidth(0,60);
    initsabutton();
    setbutton();
    this->initstate();

}

SrTab::~SrTab()
{
    delete ui;
}

void SrTab::initsabutton()
{
    QWidget *qw=ui->frame_4;
    //qdeleteLater();

    for(int i=0;i<11;i++)
    {
        pb[i]= new ItemButton(qw);
        pb[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb[i]= new ItemButton(qw);
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb[i]= new ItemButton(qw);
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb[i]= new ItemButton(qw);
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }
    qw=ui->frame_10;
    //qdeleteLater();

    for(int i=0;i<11;i++)
    {
        pb[i+38]= new ItemButton(qw);
        pb[i+38]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb[i+38]= new ItemButton(qw);
        pb[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb[i+38]= new ItemButton(qw);
        pb[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb[i+38]= new ItemButton(qw);
        pb[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }

}


void SrTab::SetSampleNo()
{
    QSqlQueryModel sqm;
    db.getSampleNo(sqm, g_current_index);
    int j=0,num=sqm.rowCount();
    if(num==0)
    {
        ui->lineEdit_4->setText(QString::number(1));
        return;
    }
    for(int i=0;i<num;i++)
    {
        int k=sqm.record(i).value("id").toInt();
        int p=k-j;

        if(p>1)
        {
            ui->lineEdit_4->setText(QString::number(j+1));
            return;
        }
        j=k;
    }
    ui->lineEdit_4->setText(QString::number(j+1));
}

void SrTab::SetPos()
{
    ui->comboBox_2->clear();
    QSqlQueryModel sqm;
    db.getPos(sqm, g_current_index);
    for(int i=0;i<40;i++)
    {
        ui->comboBox_2->addItem(QString::number(i+1));
    }
    for(int j=0;j<sqm.rowCount();j++)
    {
        QString num=sqm.record(j).value("pos").toString();
        int index=ui->comboBox_2->findText(num);
        if(index!=-1)
        {
            ui->comboBox_2->removeItem(index);
        }
    }
    ui->comboBox_2->setCurrentIndex(0);
    //ui->comboBox_2->currentData()

}

void SrTab::setYesEnable(bool b)
{
    ui->sr_yes->setEnabled(b);
}

void SrTab::uncheckbt()
{
    for(int i=0;i<g_item_num;i++)
    {
        pb[i]->setChecked(false);
    }
}

void SrTab::setbutton()
{
    QSqlQueryModel sqm;
    db.getTestItem(sqm);
    g_item_num=sqm.rowCount();
    for(int i=0;i<sqm.rowCount();i++)

    {

        QString name=sqm.record(i).value("Name").toString();
        int   testid=sqm.record(i).value("TestId").toInt();

        pb[i]->setText(name);
        pb[i]->testid=testid;

        pb[i]->setEnabled(true);
        pb[i]->setCheckable(true);
        connect(pb[i],SIGNAL(toggled(bool)),this,SLOT(ontoggle(bool)));
    }



}
void SrTab::refreshtable()
{
    QSqlQueryModel sqm;
    db.getSr(sqm,::g_current_index);
    QTableWidget *tw=ui->tableWidget;
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

void SrTab::showpage(int i)
{
    if(!i) {
        ui->frame_4->show();
        ui->frame_10->hide();
    }
    else
    {
        ui->frame_4->hide();
        ui->frame_10->show();

    }
}

void SrTab::initstate()
{
    //page 1
    ui->comboBox_4->setCurrentIndex(0);

    showpage(0);
    setYesEnable(false);
    this->uncheckbt();
    this->SetSampleNo();
    SetPos();
    this->refreshtable();
}

void SrTab::reg()
{
   TestRegister t;
   QDateTime now=QDateTime::currentDateTime();

   t.id=ui->lineEdit_4->text().toInt();
   //t.tr.test_row_id=QDateTime::currentDateTime().toString()
   t.no=QString::number(t.id);
   t.sampleid=ui->lineEdit_6->text();
   t.pre_dilute=ui->checkBox->isChecked();
   t.pre_d_times=ui->lineEdit_5->text().toInt();
   t.tr.position=ui->comboBox_2->currentText().toInt();
   t.tr.sample_cup_type=ui->comboBox_3->currentIndex();
   t.tr.priority=!(ui->checkBox_2->isChecked());
   t.tr.test_type=4;
   t.qname="";
   t.cname="";
   t.tr.isdilute=0;
   t.tr.status=0;
   //初始化  g_current_index 在全局变量中
   //还有test_row_id ,isreplace, test_id
   int j=0;
   for(int i=0;i<g_item_num;i++)
   {
       if(pb[i]->isChecked())
       {
           //insert
           QString tempid =now.toString("yyyyMMddhhmmss")+QString("%1").arg(j,3,10,QChar('0'));
           //if test_id isreplace add two rows
           t.tr.test_row_id=tempid.toStdString();
           t.tr.isreplace=0;
           t.tr.test_id=pb[i]->testid;
           db.insertSample(t);
           j++;
           if(gi::isReplace(pb[i]->testid))
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

void SrTab::on_comboBox_4_currentIndexChanged(int index)
{
    showpage(index);
}

void SrTab::ontoggle(bool b)
{
    bool isOK=false;
    for (int i=0;i<g_item_num;i++)
    {
        if(pb[i]->isChecked())
        {
            isOK=true;
            break;
        }

    }
    if(isOK)
    {
        setYesEnable(true);
    }
    else
    {
        setYesEnable(false);
    }
}

void SrTab::on_sr_yes_clicked()
{
    reg();
    initstate();
}
