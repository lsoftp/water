#include "cacurveframe.h"
#include "ui_cacurveframe.h"
#include "cadlg.h"
#include <QDebug>
#include "dbinterface.h"

CaCurveFrame::CaCurveFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CaCurveFrame)
{
    ui->setupUi(this);
    ui->tableWidget ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget ->setSelectionMode(QAbstractItemView::SingleSelection);

    QHeaderView *header = ui->tableWidget ->verticalHeader();
    header->setHidden(true);// 隐藏行号
    refreshtable();
}

CaCurveFrame::~CaCurveFrame()
{
    delete ui;
}



void CaCurveFrame::on_pushButton_clicked()
{
    CaDlg cd;
    cd.setWindowTitle("添加标准液");
    cd.setWindowFlags(cd.windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    int i=cd.exec();
    if(i==QDialog::Accepted)
    {
        qDebug()<<cd.name<<cd.no<<cd.valid;
        db.insertCaye(cd);
        refreshtable();
    }

}

void CaCurveFrame::on_pushButton_2_clicked()
{
    CaDlg cd("hahah","b","2018/8/8");
    cd.setWindowTitle("编辑标准液");
    //cd.name="sdf";
    int i=cd.exec();
    if(i==QDialog::Accepted)
    {
        qDebug()<<cd.name<<cd.no<<cd.valid;
    }
}


void CaCurveFrame::refreshtable()
{
    QSqlQueryModel sqm;
    db.getCaye(sqm);
    QTableWidget *tw=ui->tableWidget;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount());
    for(int i=0;i<sqm.rowCount();i++)
    {
        tw->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("name").toString()));
        tw->setItem(i,2,new QTableWidgetItem(sqm.record(i).value("no").toString()));
        tw->setItem(i,3,new QTableWidgetItem(sqm.record(i).value("valid").toString()));

    }

}
