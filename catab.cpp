#include "catab.h"
#include "ui_catab.h"
#include "mainwindow.h"

CaTab::CaTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaTab)
{
    ui->setupUi(this);
    initcabutton();
    setbutton();
    showpage(0);
    QRegExp regx("^C[1-9][0-9]*$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit_7 );
    ui->lineEdit_7->setValidator(validator);
    updateCayelist();
}

CaTab::~CaTab()
{
    delete ui;
}

void CaTab::init()
{
    connect(ui->careturnbtn, SIGNAL(clicked()),g_w,SLOT(on_srreturnbtn_clicked()));
}

void CaTab::initcabutton()
{
    QWidget *qw=ui->frame_5;
    //qdeleteLater();

    for(int i=0;i<11;i++)
    {
        pb1[i]= new CaButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb1[i]= new CaButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb1[i]= new CaButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb1[i]= new CaButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }
    qw=ui->frame_6;
    //qdeleteLater();

    for(int i=0;i<11;i++)
    {
        pb1[i+38]= new CaButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb1[i+38]= new CaButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb1[i+38]= new CaButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb1[i+38]= new CaButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }

}

void CaTab::setbutton()
{
    QSqlQueryModel sqm;
    db.getTestItem(sqm);
    g_item_num=sqm.rowCount();
    for(int i=0;i<sqm.rowCount();i++)

    {

        QString name=sqm.record(i).value("Name").toString();
        int   testid=sqm.record(i).value("TestId").toInt();

        pb1[i]->setText(name);
        pb1[i]->testid=testid;

        pb1[i]->setEnabled(true);
        //pb1[i]->setCheckable(true);
        //connect(pb[i],SIGNAL(toggled(bool)),this,SLOT(ontoggle(bool)));
    }

}

void CaTab::showpage(int i)
{
    if(!i) {
        ui->frame_5->show();
        ui->frame_6->hide();
    }
    else
    {
        ui->frame_5->hide();
        ui->frame_6->show();

    }
}
void CaTab::on_comboBox_7_currentIndexChanged(int index)
{
    showpage(index);
}

void CaTab::updateCayelist()
{
    QSqlQueryModel sqm;
    db.getCaye(sqm);
    ui->comboBox_5->clear();
    for(int i=0; i<sqm.rowCount();i++)
    {

        ui->comboBox_5->addItem(sqm.record(i).value("name").toString());
    }
}

void CaTab::reg()
{
    if(!isValid())
    {
        QMessageBox::information(0,"错误","请输入正确的样本号！");
        return;
    }
    TestRegister t;
    QDateTime now=QDateTime::currentDateTime();

    //t.tr.test_row_id=QDateTime::currentDateTime().toString()
    t.no=ui->lineEdit_7->text();
    t.id=t.no.right(t.no.size()-1).toInt();
    //t.sampleid=ui->lineEdit_6->text();
    //t.pre_dilute=ui->checkBox->isChecked();
    //t.pre_d_times=ui->lineEdit_5->text().toInt();
    //t.tr.position=ui->comboBox_2->currentText().toInt();
    t.tr.sample_cup_type=ui->comboBox_6->currentIndex();
    //t.tr.priority=!(ui->checkBox_2->isChecked());
    t.tr.test_type=1; //to be determined
    t.qname="";
    t.cname=ui->comboBox_5->currentText();
    t.tr.isdilute=0;
    t.tr.status=0;
    //t.combinetestname="";
    //初始化  g_current_index 在全局变量中
    //还有test_row_id ,isreplace, test_id

    db.delSrbyid(g_current_index,t.no);
    int j=0;
    for(int i=0;i<g_item_num;i++)
    {
        if(this->pb1[i]->isChecked())
        {
            //insert
            QString tempid =now.toString("yyyyMMddhhmmss")+QString("%1").arg(j,3,10,QChar('0'));
            //if test_id isreplace add two rows
            t.tr.test_row_id=tempid.toStdString();
            t.tr.isreplace=0;
            t.tr.test_id=pb1[i]->testid;
            db.insertSample(t);
            j++;
            //            if(gi::isReplace(pb[i]->testid))
            //            {
            //                tempid =now.toString("yyyyMMddhhmmss")+QString("%1").arg(j,3,10,QChar('0'));
            //                t.tr.isreplace=1;
            //                db.insertSample(t);
            //                j++;
            //            }

            //
        }
    }

}

bool CaTab::isValid()
{
    const QValidator* v=ui->lineEdit_7->validator();
    int i;
    QString s=ui->lineEdit_7->text();
    if(QValidator::Acceptable==v->validate(s,i))
    {
        //v->validate(s,i);
        //QMessageBox::information(0,QString::number(i),QString::number(v->validate(s,i)));
        return true;
    }
    else
    {
        return false;
    }


}
