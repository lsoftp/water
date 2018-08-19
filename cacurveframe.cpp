#include "cacurveframe.h"
#include "ui_cacurveframe.h"
#include "cadlg.h"
#include "caqudlg.h"
#include <QDebug>
#include "dbinterface.h"
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

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

    ui->tableWidget_5 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget_5 ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_5 ->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setStyleSheet("QTableWidget{selection-background-color:blue;}");
    header = ui->tableWidget_5 ->verticalHeader();
    header->setHidden(true);// 隐藏行号

    ui->graphicsView->setScene(&scene);
    refreshtable();
    initTestList();
    initCayeList();
    refreshtable2();
    ui->tabWidget->setStyleSheet("QLineEdit { background-color: white }");
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

void CaCurveFrame::refreshtable2()
{
    QSqlQueryModel sqm;
    db.getCacurveSetting(sqm);
    QTableWidget *tw=ui->tableWidget_5;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount());
    for(int i=0;i<sqm.rowCount();i++)
    {
        tw->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("name").toString()));

    }
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

void CaCurveFrame::on_pushButton_4_clicked()
{
    // 标准曲线添加
    QList<QLineEdit *> ls = ui->tab_2->findChildren<QLineEdit *>();
    foreach(QLineEdit *le,ls)
    {
        le->clear();
    }
    ui->tableWidget_5->clearSelection();
}

void CaCurveFrame::on_pushButton_6_clicked()
{
    //save curve
    Cadetail cd;
    load(cd);
    QList<QTableWidgetItem*> items=ui->tableWidget_5->selectedItems();
    if(items.size()!=0)
    {
        //如果有当前的配置，就为update
        QString name=items.at(1)->text();
        db.delCadetailbyName(name);

    }
    db.insertCadetail(cd);

    refreshtable2();
}

void CaCurveFrame::on_pushButton_5_clicked()
{
    //delete curve
    QList<QTableWidgetItem*> items=ui->tableWidget_5->selectedItems();
    if(items.size()==0) return;
    QString name=items.at(1)->text();
    QMessageBox box(QMessageBox::Information,"提示","是否删除曲线设置?");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    //box.setStandardButtons ();
    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.setButtonText (QMessageBox::Cancel,QString("取 消"));

    if(QMessageBox::Ok==box.exec ())
    {
        db.delCadetailbyName(name);
        refreshtable2();
    }

}

void CaCurveFrame::on_pushButton_12_clicked()
{
    //print
    QLineSeries *series = new QLineSeries();
    QLineSeries series1 ;
       series->append(0, 6);
       series->append(2, 4);
       series->append(3, 8);
       series->append(7, 4);
       series->append(10, 5);
       series1 << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

       QChart *chart = new QChart();
       chart->legend()->hide();
       chart->addSeries(series);
       chart->addSeries(&series1);//not ok
       chart->createDefaultAxes();
       chart->axisY()->setTitleText("吸光度");
       chart->axisX()->setTitleText("浓度");
       chart->setTitle("Simple line chart example");
       chart->setGeometry(0,0,780,300);

       scene.addItem(chart);

}

void CaCurveFrame::load(Cadetail &cd)
{
    cd.name=ui->comboBox_12->currentText();
    cd.type=ui->comboBox->currentText();
    cd.num=ui->comboBox_2->currentText().toInt();
    cd.kvalue=ui->lineEdit_2->text();
    cd.testtimes=ui->comboBox_3->currentText();
    cd.caname0=ui->comboBox_4->currentText();
    cd.caname1=ui->comboBox_5->currentText();
    cd.caname2=ui->comboBox_6->currentText();
    cd.caname3=ui->comboBox_7->currentText();
    cd.caname4=ui->comboBox_8->currentText();
    cd.caname5=ui->comboBox_9->currentText();
    cd.caname6=ui->comboBox_10->currentText();
    cd.caname7=ui->comboBox_11->currentText();
    cd.con0=ui->lineEdit_3->text();
    cd.con1=ui->lineEdit_7->text();
    cd.con2=ui->lineEdit_10->text();
    cd.con3=ui->lineEdit_13->text();
    cd.con4=ui->lineEdit_16->text();
    cd.con5=ui->lineEdit_19->text();
    cd.con6=ui->lineEdit_22->text();
    cd.con7=ui->lineEdit_25->text();

    cd.dilute0=ui->lineEdit_5->text();
    cd.dilute1=ui->lineEdit_8->text();
    cd.dilute2=ui->lineEdit_11->text();
    cd.dilute3=ui->lineEdit_14->text();
    cd.dilute4=ui->lineEdit_17->text();
    cd.dilute5=ui->lineEdit_20->text();
    cd.dilute6=ui->lineEdit_23->text();
    cd.dilute7=ui->lineEdit_26->text();

    cd.con01=ui->lineEdit_4->text();
    cd.con11=ui->lineEdit_6->text();
    cd.con21=ui->lineEdit_9->text();
    cd.con31=ui->lineEdit_12->text();
    cd.con41=ui->lineEdit_15->text();
    cd.con51=ui->lineEdit_18->text();
    cd.con61=ui->lineEdit_21->text();
    cd.con71=ui->lineEdit_24->text();
}

void CaCurveFrame::initTestList()
{
    QSqlQueryModel sqm;
    db.getTestItem(sqm);
    for(int i=0; i<sqm.rowCount();i++)
    {
        ui->comboBox_12->addItem(sqm.record(i).value("name").toString(),sqm.record(i).value("TestID").toInt());
    }

}

void CaCurveFrame::initCayeList()
{
    QSqlQueryModel sqm;
    db.getCaye(sqm);
    for(int i=0; i<sqm.rowCount();i++)
    {
        ui->comboBox_4->addItem(sqm.record(i).value("name").toString());
        ui->comboBox_5->addItem(sqm.record(i).value("name").toString());
        ui->comboBox_6->addItem(sqm.record(i).value("name").toString());
        ui->comboBox_7->addItem(sqm.record(i).value("name").toString());
        ui->comboBox_8->addItem(sqm.record(i).value("name").toString());
        ui->comboBox_9->addItem(sqm.record(i).value("name").toString());
        ui->comboBox_10->addItem(sqm.record(i).value("name").toString());
        ui->comboBox_11->addItem(sqm.record(i).value("name").toString());
    }

}

void CaCurveFrame::on_tableWidget_5_itemSelectionChanged()
{
    QList<QTableWidgetItem*> items=ui->tableWidget_5->selectedItems();
    if(items.size()==0) return;
    QString name=items.at(1)->text();
    QSqlQueryModel sqm;
    db.getCadetailbyname(sqm,name);
    int i=0;
    Cadetail ca;
#define ITEM_I(p,q) q=sqm.record(i).value(p).toInt()
#define ITEM_C(p,q) q=sqm.record(i).value(p).toString()
    ITEM_I(0,ca.TestID);
    ITEM_C(1,ca.name);
    ITEM_C(2,ca.type);
    ITEM_I(3,ca.num);
    ITEM_C(4,ca.kvalue);
    ITEM_C(5,ca.testtimes);
    ITEM_C(6,ca.caname0);
    ITEM_C(7,ca.con0);
    ITEM_C(8,ca.dilute0);
    ITEM_C(9,ca.con01);
    ITEM_C(10,ca.caname1);
    ITEM_C(11,ca.con1);
    ITEM_C(12,ca.dilute1);
    ITEM_C(13,ca.con11);

    ITEM_C(14,ca.caname2);
    ITEM_C(15,ca.con2);
    ITEM_C(16,ca.dilute2);
    ITEM_C(17,ca.con21);

    ITEM_C(18,ca.caname3);
    ITEM_C(19,ca.con3);
    ITEM_C(20,ca.dilute3);
    ITEM_C(21,ca.con31);
    ITEM_C(22,ca.caname4);
    ITEM_C(23,ca.con4);
    ITEM_C(24,ca.dilute4);
    ITEM_C(25,ca.con41);
    ITEM_C(26,ca.caname5);
    ITEM_C(27,ca.con5);
    ITEM_C(28,ca.dilute5);
    ITEM_C(29,ca.con51);
    ITEM_C(30,ca.caname6);
    ITEM_C(31,ca.con6);
    ITEM_C(32,ca.dilute6);
    ITEM_C(33,ca.con61);
    ITEM_C(34,ca.caname7);
    ITEM_C(35,ca.con7);
    ITEM_C(36,ca.dilute7);
    ITEM_C(37,ca.con71);

    //cd.name=ui->comboBox_12->currentText();
    i=ui->comboBox_12->findText(ca.name);
    ui->comboBox_12->setCurrentIndex(i);

    i=ui->comboBox->findText(ca.type);
    ui->comboBox->setCurrentIndex(i);

    i=ui->comboBox_2->findText(QString::number(ca.num));
    ui->comboBox_2->setCurrentIndex(i);
    ui->lineEdit_2->setText(ca.kvalue);
    //cd.testtimes=ui->comboBox_3->currentText();
    i=ui->comboBox_3->findText(ca.testtimes);
    ui->comboBox_3->setCurrentIndex(i);

    //cd.caname0=ui->comboBox_4->currentText();
    i=ui->comboBox_4->findText(ca.caname0);
    ui->comboBox_4->setCurrentIndex(i);
    i=ui->comboBox_5->findText(ca.caname1);
    ui->comboBox_5->setCurrentIndex(i);
    i=ui->comboBox_6->findText(ca.caname2);
    ui->comboBox_6->setCurrentIndex(i);
    i=ui->comboBox_7->findText(ca.caname3);
    ui->comboBox_7->setCurrentIndex(i);
    i=ui->comboBox_8->findText(ca.caname4);
    ui->comboBox_8->setCurrentIndex(i);
    i=ui->comboBox_9->findText(ca.caname5);
    ui->comboBox_9->setCurrentIndex(i);
    i=ui->comboBox_10->findText(ca.caname6);
    ui->comboBox_10->setCurrentIndex(i);
    i=ui->comboBox_11->findText(ca.caname7);
    ui->comboBox_11->setCurrentIndex(i);

     ui->lineEdit_3->setText(ca.con0);
     ui->lineEdit_7->setText(ca.con1);
     ui->lineEdit_10->setText(ca.con2);
     ui->lineEdit_13->setText(ca.con3);
     ui->lineEdit_16->setText(ca.con4);
     ui->lineEdit_19->setText(ca.con5);
     ui->lineEdit_22->setText(ca.con6);
     ui->lineEdit_25->setText(ca.con7);

     ui->lineEdit_5->setText(ca.dilute0);
     ui->lineEdit_8->setText(ca.dilute1);
     ui->lineEdit_11->setText(ca.dilute2);
     ui->lineEdit_14->setText(ca.dilute3);
     ui->lineEdit_17->setText(ca.dilute4);
     ui->lineEdit_20->setText(ca.dilute5);
     ui->lineEdit_23->setText(ca.dilute6);
     ui->lineEdit_26->setText(ca.dilute7);

     ui->lineEdit_4->setText(ca.con01);
     ui->lineEdit_6->setText(ca.con11);
     ui->lineEdit_9->setText(ca.con21);
     ui->lineEdit_12->setText(ca.con31);
     ui->lineEdit_15->setText(ca.con41);
     ui->lineEdit_18->setText(ca.con51);
     ui->lineEdit_21->setText(ca.con61);
     ui->lineEdit_24->setText(ca.con71);




}
