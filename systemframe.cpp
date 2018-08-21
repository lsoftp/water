#include "systemframe.h"
#include "ui_systemframe.h"
#include "dbinterface.h"
#include "comboitem.h"
#include "comboitem1.h"
SystemFrame::SystemFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SystemFrame)
{
    ui->setupUi(this);
    ui->tableWidget_3 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget_3 ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_3 ->setSelectionMode(QAbstractItemView::SingleSelection);
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

SystemFrame::~SystemFrame()
{
    delete ui;
}

bool SystemFrame::ifSelectCa(bool b)
{
    QList<QTableWidgetItem*> items=ui->tableWidget_2->selectedItems();
    if(items.size()==0)
    {
        if(!b)
        {
            QMessageBox box(QMessageBox::Information,"提示","请选择质控液");
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.exec ();
        }
        return false;
    }
    selCaname=items.at(1)->text();
    return true;
}



bool SystemFrame::ifSelectTest()
{
    QList<QTableWidgetItem*> items=ui->tableWidget_3->selectedItems();
    if(items.size()==0)
    {
        QMessageBox box(QMessageBox::Information,"提示","请选择测试");
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
        box.exec ();
        return false;
    }
    selTestname=items.at(1)->text();
    return true;
}





void SystemFrame::refreshtable()
{
    QSqlQueryModel sqm;
    db.getComboItem(sqm);
    QTableWidget *tw=ui->tableWidget_2;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount());
    for(int i=0;i<sqm.rowCount();i++)
    {
        tw->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("name").toString()));


    }
    tw->selectRow(0);
}

void SystemFrame::refreshtable1(QString sel)
{
    QSqlQueryModel sqm;
    db.getComboItem1(sqm,sel);
    QTableWidget *tw=ui->tableWidget_3;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount());
    for(int i=0;i<sqm.rowCount();i++)
    {
        tw->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        //tw->setItem(i,0,new QTableWidgetItem(sqm.record(i).value("TestName").toString()));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("Item").toString()));
        //tw->setItem(i,2,new QTableWidgetItem(sqm.record(i).value("unit").toString()));

    }
    tw->selectRow(0);

}








void SystemFrame::on_pushButton_clicked()
{
    // add qu
    ComBoItem cd;
    cd.setWindowTitle("添加组合测试");
    cd.setWindowFlags(cd.windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    int i=cd.exec();
    if(i==QDialog::Accepted)
    {
        //qDebug()<<cd.name<<cd.no<<cd.valid;
        db.insertComboItem(cd.name);
        refreshtable();
        for(int k=0;k<ui->tableWidget_2->rowCount();k++)
        {
            if(!ui->tableWidget_2->item(k,1)->text().compare(cd.name))
            {
                ui->tableWidget_2->selectRow(k);
                break;
            }
        }
    }
}

void SystemFrame::on_pushButton_2_clicked()
{
    //edit qu
    QList<QTableWidgetItem*> items=ui->tableWidget_2->selectedItems();
    if(items.size()==0)
    {
        QMessageBox box(QMessageBox::Information,"提示","请选择组合项目");
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
        box.exec ();
        return;
    }
    ComBoItem cd(items.at(1)->text());
    cd.setWindowTitle("编辑组合项目");
    //cd.name="sdf";
    int i=cd.exec();
    if(i==QDialog::Accepted)
    {
        //qDebug()<<cd.name<<cd.no<<cd.valid;
        db.updateComboItemByName(items.at(1)->text(),cd.name);
        refreshtable();
    }
}

void SystemFrame::on_pushButton_3_clicked()
{
    //delete qu
    QList<QTableWidgetItem*> items=ui->tableWidget->selectedItems();
    if(items.size()==0)
    {
        QMessageBox box(QMessageBox::Information,"提示","请选择组合项目");
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
        db.delComboItembyName(items.at(1)->text());
        refreshtable();
    }
}

void SystemFrame::on_pushButton_8_clicked()
{
    //add item
    if(ifSelectCa())
    {
        ComboItem1 cqd;
        cqd.setWindowTitle("添加项目");
        if(QDialog::Accepted==cqd.exec())
        {
            db.insertComboItem1(selCaname,cqd.item,cqd.testid);
            refreshtable1(selCaname);
        }
    }
}

void SystemFrame::on_pushButton_7_clicked()
{
    //edit item
    if(ifSelectCa() && ifSelectTest())
    {
        QList<QTableWidgetItem*> items=ui->tableWidget_3->selectedItems();
        ComboItem1 cqd(items.at(1)->text());
        cqd.setWindowTitle("编辑项目");
        if(QDialog::Accepted==cqd.exec())
        {
            db.updateComboItem1ByName(selCaname,selTestname,cqd.item,cqd.testid);
            refreshtable1(selCaname);
        }
    }
}

void SystemFrame::on_pushButton_9_clicked()
{
    //del item
    if(ifSelectCa() && ifSelectTest())
    {
        QMessageBox box(QMessageBox::Information,"提示","是否删除项目?");
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
        //box.setStandardButtons ();
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        box.setButtonText (QMessageBox::Cancel,QString("取 消"));

        if(QMessageBox::Ok==box.exec ())
        {
            db.delComboItem1(selCaname,selTestname);
            refreshtable1(selCaname);
        }
    }
}

void SystemFrame::on_tableWidget_2_itemSelectionChanged()
{
    if(ifSelectCa(1))
    {
        refreshtable1(selCaname);
    }
}

void SystemFrame::on_careturnbtn_clicked()
{
    emit back();
}
