#include "qutab.h"
#include "ui_qutab.h"

QuTab::QuTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuTab)
{
    ui->setupUi(this);
    initcabutton();
    setbutton();
    showpage(0);
}

QuTab::~QuTab()
{
    delete ui;
}

void QuTab::initcabutton()
{
    QWidget *qw=ui->frame_5;
    //qdeleteLater();

    for(int i=0;i<11;i++)
    {
        pb1[i]= new ItemButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb1[i]= new ItemButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb1[i]= new ItemButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb1[i]= new ItemButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }
    qw=ui->frame_6;
    //qdeleteLater();

    for(int i=0;i<11;i++)
    {
        pb1[i+38]= new ItemButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb1[i+38]= new ItemButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb1[i+38]= new ItemButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb1[i+38]= new ItemButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }

}

void QuTab::setbutton()
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
        pb1[i]->setCheckable(true);
        //connect(pb[i],SIGNAL(toggled(bool)),this,SLOT(ontoggle(bool)));
    }

}

void QuTab::showpage(int i)
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



void QuTab::on_comboBox_7_currentIndexChanged(int index)
{
        showpage(index);
}
