#include "cacurveframe.h"
#include "ui_cacurveframe.h"
#include "cadlg.h"
#include "caqudlg.h"
#include <QDebug>
#include "dbinterface.h"
#include <QMessageBox>

CaCurveFrame::CaCurveFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CaCurveFrame)
{
    ui->setupUi(this);
    ui->tableWidget ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget ->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setStyleSheet("QTableWidget{selection-background-color:blue;}");
    QHeaderView *header = ui->tableWidget ->verticalHeader();
    header->setHidden(true);// 隐藏行号
    ui->tableWidget_2 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget_2 ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2 ->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setStyleSheet("QTableWidget{selection-background-color:blue;}");
    header = ui->tableWidget_2 ->verticalHeader();
    header->setHidden(true);// 隐藏行号

    refreshtable();
}

CaCurveFrame::~CaCurveFrame()
{
    delete ui;
}

bool CaCurveFrame::ifSelectCa()
{
    QList<QTableWidgetItem*> items=ui->tableWidget->selectedItems();
    if(items.size()==0)
    {
        QMessageBox box(QMessageBox::Information,"提示","请选择标准液");
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
        box.exec ();
        return false;
    }
    selCaname=items.at(1)->text();
    return true;
}

bool CaCurveFrame::ifSelectCa1()
{
    QList<QTableWidgetItem*> items=ui->tableWidget->selectedItems();
    if(items.size()==0)
    {
        return false;
    }
    selCaname=items.at(1)->text();
    return true;
}

bool CaCurveFrame::ifSelectTest()
{
    QList<QTableWidgetItem*> items=ui->tableWidget_2->selectedItems();
    if(items.size()==0)
    {
        QMessageBox box(QMessageBox::Information,"提示","请选择测试");
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
        box.exec ();
        return false;
    }
    selTestname=items.at(0)->text();
    return true;
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
        for(int k=0;k<ui->tableWidget->rowCount();k++)
        {
            if(!ui->tableWidget->item(k,1)->text().compare(cd.name))
            {
                ui->tableWidget->selectRow(k);
                break;
            }
        }
    }

}

void CaCurveFrame::on_pushButton_2_clicked()
{
    QList<QTableWidgetItem*> items=ui->tableWidget->selectedItems();
    if(items.size()==0)
    {
        QMessageBox box(QMessageBox::Information,"提示","请选择标准液");
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
        box.exec ();
        return;
    }
    CaDlg cd(items.at(1)->text(),items.at(2)->text(),items.at(3)->text());
    cd.setWindowTitle("编辑标准液");
    //cd.name="sdf";
    int i=cd.exec();
    if(i==QDialog::Accepted)
    {
        qDebug()<<cd.name<<cd.no<<cd.valid;
        db.updateCayeByName(items.at(1)->text(),cd.name,cd.no,cd.valid);
        refreshtable();
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
    tw->selectRow(0);
}

void CaCurveFrame::refreshtable1(QString sel)
{
    QSqlQueryModel sqm;
    db.getCayeItem(sqm,sel);
    QTableWidget *tw=ui->tableWidget_2;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount());
    for(int i=0;i<sqm.rowCount();i++)
    {
        //tw->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        tw->setItem(i,0,new QTableWidgetItem(sqm.record(i).value("TestName").toString()));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("con").toString()));
        tw->setItem(i,2,new QTableWidgetItem(sqm.record(i).value("unit").toString()));

    }
    tw->selectRow(0);

}

void CaCurveFrame::on_pushButton_3_clicked()
{
    QList<QTableWidgetItem*> items=ui->tableWidget->selectedItems();
    if(items.size()==0)
    {
        QMessageBox box(QMessageBox::Information,"提示","请选择标准液");
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
        box.exec ();
        return;
    }
    QMessageBox box(QMessageBox::Information,"提示","是否删除?");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    //box.setStandardButtons ();
    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.setButtonText (QMessageBox::Cancel,QString("取 消"));

    if(QMessageBox::Ok==box.exec ())
    {
        db.delCayebyName(items.at(1)->text());
        refreshtable();
    }
}

void CaCurveFrame::on_pushButton_8_clicked()
{
    //add test
    if(ifSelectCa())
    {
        CaQuDlg cqd;
        cqd.setWindowTitle("添加测试");
        if(QDialog::Accepted==cqd.exec())
        {
            db.insertCayeItem(selCaname,cqd.testname,cqd.con,cqd.unit);
            refreshtable1(selCaname);
        }
    }
}

void CaCurveFrame::on_pushButton_7_clicked()
{
    //edit test
    if(ifSelectCa() && ifSelectTest())
    {
        QList<QTableWidgetItem*> items=ui->tableWidget_2->selectedItems();
        CaQuDlg cqd(items.at(0)->text(),items.at(1)->text(),items.at(2)->text());
        cqd.setWindowTitle("编辑测试");
        if(QDialog::Accepted==cqd.exec())
        {
            db.updateCayeItemByName(selCaname,selTestname,cqd.testname,cqd.con,cqd.unit);
            refreshtable1(selCaname);
        }
    }
}

void CaCurveFrame::on_pushButton_9_clicked()
{
    //delete test
    if(ifSelectCa() && ifSelectTest())
    {
        QMessageBox box(QMessageBox::Information,"提示","是否删除测试?");
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
        //box.setStandardButtons ();
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        box.setButtonText (QMessageBox::Cancel,QString("取 消"));

        if(QMessageBox::Ok==box.exec ())
        {
            db.delCayeItem(selCaname,selTestname);
            refreshtable1(selCaname);
        }
    }
}

void CaCurveFrame::on_tableWidget_itemSelectionChanged()
{
    if(ifSelectCa1())
    {
        refreshtable1(selCaname);
    }
}
