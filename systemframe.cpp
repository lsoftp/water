#include "systemframe.h"
#include "ui_systemframe.h"

#include "comboitem.h"
#include "comboitem1.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
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
    ui->tableWidget_4 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget_4 ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_4 ->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setStyleSheet("QTableWidget{selection-background-color:blue;}");
    header = ui->tableWidget_4 ->verticalHeader();
    header->setHidden(true);// 隐藏行号
    ui->tableWidget_4->setColumnWidth(0,400);
    ui->tableWidget_4->setColumnWidth(1,416);

    ui->tableWidget_5 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget_5 ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_5 ->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setStyleSheet("QTableWidget{selection-background-color:blue;}");
    header = ui->tableWidget_5->verticalHeader();
    header->setHidden(true);// 隐藏行号
    ui->tableWidget_5->setColumnWidth(0,400);
    ui->tableWidget_5->setColumnWidth(1,416);
    refreshtable();
    refreshItemOrderTable();
    init_item_order();
    init_dict();
    ui->tabWidget->setStyleSheet(" QLineEdit{background-color:white} QComboBox{background-color:white}");
    init_serial_port_list();
    Calcu_init();
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
            QMessageBox box(QMessageBox::Information,"提示","请选择组合项目");
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

void SystemFrame::refreshItemOrderTable()
{
    QSqlQueryModel sqm;
    db.getItemOrderByPri(sqm);
    QTableWidget *tw=ui->tableWidget_4;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount());
    for(int i=0;i<sqm.rowCount();i++)
    {
        tw->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("name").toString()));

    }


}

void SystemFrame::init_item_order()
{
    QTableWidget *tw=ui->tableWidget_4;
    for(int i=0;i<tw->rowCount();i++)
    {
        int p=tw->item(i,0)->text().toInt();
        QString n=tw->item(i,1)->text();
        db.updateItemPri(n,p);
    }
}

void SystemFrame::on_tabWidget_currentChanged(int index)
{
    //    if(4==index)
    //    {
    //        item_order_init();
    //    }
}

int SystemFrame::ifSelectItemOrder(bool b)
{
    QList<QTableWidgetItem*> items=ui->tableWidget_4->selectedItems();
    if(items.size()==0)
    {
        if(!b)
        {
            QMessageBox box(QMessageBox::Information,"提示","请选择项目");
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.exec ();
        }
        return -1;
    }
    selOrdername=items.at(1)->text();
    return items.at(0)->row();
}
void SystemFrame::on_pushButton_4_clicked()
{
    int r=ifSelectItemOrder(0);
    if(r>0)
    {
        db.updateItemPri(selOrdername,r-1);
        db.updateItemPri(ui->tableWidget_4->item(r-1,1)->text(),r);
        refreshItemOrderTable();
        ui->tableWidget_4->selectRow(r-1);
    }
}

void SystemFrame::on_pushButton_5_clicked()
{
    QTableWidget *tw=ui->tableWidget_4;
    int r=ifSelectItemOrder(0);
    if(r>=0 and r<tw->rowCount()-1)
    {
        db.updateItemPri(selOrdername,r+1);
        db.updateItemPri(ui->tableWidget_4->item(r+1,1)->text(),r);
        refreshItemOrderTable();
        ui->tableWidget_4->selectRow(r+1);
    }

}

void SystemFrame::init_dict()
{
    ui->listWidget->setCurrentRow(0);
    QString tt= ui->listWidget->currentItem()->text();
    //QHeaderView *header = ui->tableWidget_5 ->horizontalHeader();
    ui->tableWidget_5->horizontalHeaderItem(1)->setText(tt);
    ui->label_6->setText(tt);
    ui->tableWidget_5->setColumnWidth(0,60);
    ui->tableWidget_5->setColumnWidth(1,200);
    ui->tableWidget_5->setColumnWidth(2,569);


}

void SystemFrame::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->tableWidget_5->horizontalHeaderItem(1)->setText(currentText);
    ui->label_6->setText(currentText);
}

void SystemFrame::on_singlebtn_toggled(bool checked)
{
    ui->doublebtn->setChecked(!checked);
}

void SystemFrame::on_doublebtn_toggled(bool checked)
{
    ui->singlebtn->setChecked(!checked);
}

void SystemFrame::on_return_btn_clicked()
{
    emit back();
}

void SystemFrame::on_careturnbtn_2_clicked()
{
    emit back();
}

void SystemFrame::on_careturnbtn_3_clicked()
{
    emit back();
}

void SystemFrame::on_careturnbtn_4_clicked()
{
    emit back();
}

void SystemFrame::on_return_btn_2_clicked()
{
    emit back();
}

void SystemFrame::init_serial_port_list()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString s = info.portName();
        ui->comboBox_4->addItem(s);
    }
    ui->comboBox_5->setCurrentIndex(5);
    ui->comboBox_7->setCurrentIndex(3);
}

void SystemFrame::Calcu_init()
{
    QSqlQueryModel sqm;
    db.getItem(sqm);
    QTableWidget *tw=ui->tableWidget_7;
    ui->tableWidget_7 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    //ui->tableWidget_5 ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_7 ->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setStyleSheet("QTableWidget{selection-background-color:blue;}");
    QHeaderView *header = ui->tableWidget_7 ->verticalHeader();
    header->setHidden(true);// 隐藏行号
    header = ui->tableWidget_7 ->horizontalHeader();
    header->setHidden(true);// 隐藏行号

    ui->tableWidget  ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget  ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget  ->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setStyleSheet("QTableWidget{selection-background-color:blue;}");
     header = ui->tableWidget ->verticalHeader();
    header->setHidden(true);// 隐藏行号
    tw->clearContents();
    tw->setRowCount(sqm.rowCount()/5+1);
    for(int i=0;i<sqm.rowCount();i++)
    {
        //tw->setItem(i/5,i/%5,new QTableWidgetItem(QString::number(i+1)));
        tw->setItem(i/5,i%5,new QTableWidgetItem(sqm.record(i).value("name").toString()));

    }
    caluItem_refresh_table();
    this->cacuItem_selectrow(0);
}

void SystemFrame::on_tableWidget_7_cellDoubleClicked(int row, int column)
{
    QLineEdit *l=ui->lineEdit_3;
    QTableWidget *tw=ui->tableWidget_7;
    QString f=l->text();
    int len=f.size();
    QTableWidgetItem *si=tw->item(row,column);
    if(NULL==si) return;
    QString item=si->text();
    if(item!="")
    {
        int i=ui->lineEdit_3->cursorPosition();
        QString newf=f.left(i)+item+f.right(len-i);
        l->setText(newf);
        l->setCursorPosition(i+item.size());
    }
}

void SystemFrame::caluItem_refresh_table()
{
    QSqlQueryModel sqm;
    db.getCalcuItem(sqm);
    QTableWidget *tw=ui->tableWidget;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount());
    for(int i=0;i<sqm.rowCount();i++)
    {
        tw->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("name").toString()));

    }
}

void SystemFrame::caluItem_new()
{
    QList<QLineEdit *> ls = ui->tab->findChildren<QLineEdit *>();
    foreach(QLineEdit *le,ls)
    {
        le->clear();
    }
    ui->tableWidget->clearSelection();
}
void SystemFrame::caluItem_del()
{
    if(calcuItem_ifSelectCa())
    {
        db.delCalcuItembyName(selCaname);
        caluItem_refresh_table();
    }
}
void SystemFrame::caluItem_save()
{
    CalcuItem ci;
    calcuItem_load(ci);
    if(calcuItem_ifSelectCa())
    {
        db.delCalcuItembyName(selCaname);
    }
    db.insertCalcuItem(ci);
    caluItem_refresh_table();
}
void SystemFrame::cacuItem_selectrow(int row)
{
    ui->tableWidget->selectRow(row);
}

void SystemFrame::calcuItem_load(CalcuItem &ci)
{
    ci.name=ui->lineEdit->text();
    ci.fullname=ui->lineEdit_2->text();
    ci.digitnum=ui->comboBox->currentText();
    ci.unit=ui->comboBox_2->currentText();
    ci.formula=ui->lineEdit_3->text();

}

bool SystemFrame::calcuItem_ifSelectCa()
{
    QList<QTableWidgetItem*> items=ui->tableWidget->selectedItems();
    if(items.size()==0)
    {
        //        QMessageBox box(QMessageBox::Information,"提示","请选择计算项目");
        //        box.setStandardButtons (QMessageBox::Ok);
        //        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        //        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
        //        box.exec ();
        return false;
    }
    selCaname=items.at(1)->text();
    return true;
}
void SystemFrame::on_tableWidget_itemSelectionChanged()
{
    calcuItem_ifSelectCa();
    QSqlQueryModel sqm;
    db.getCalcuItembyname(sqm,selCaname);
    CalcuItem ci;
    int i=0;
#define ITEM_I(p,q) q=sqm.record(i).value(p).toInt()
#define ITEM_C(p,q) q=sqm.record(i).value(p).toString()
    ITEM_C(0,ci.name);
    ITEM_C(1,ci.fullname);
    ITEM_C(2,ci.digitnum);
    ITEM_C(3,ci.unit);
    ITEM_C(4,ci.formula);

    ui->lineEdit->setText(ci.name);
    ui->lineEdit_2->setText(ci.fullname);
    i=ui->comboBox->findText(ci.digitnum);
    ui->comboBox_2->setCurrentIndex(i);
    i=ui->comboBox_2->findText(ci.unit);
    ui->comboBox_2->setCurrentIndex(i);
    ui->lineEdit_3->setText(ci.formula);




}

void SystemFrame::on_pushButton_6_clicked()
{
    caluItem_new();
}

void SystemFrame::on_pushButton_11_clicked()
{
    this->caluItem_save();
}

void SystemFrame::on_pushButton_10_clicked()
{
    this->caluItem_del();
}
