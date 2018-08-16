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
    ui->graphicsView->setScene(&scene);
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

void CaCurveFrame::on_pushButton_4_clicked()
{
    // 标准曲线添加
    QList<QLineEdit *> ls = ui->tab_2->findChildren<QLineEdit *>();
    foreach(QLineEdit *le,ls)
    {
        le->clear();
    }
}

void CaCurveFrame::on_pushButton_6_clicked()
{
    //save curve
}

void CaCurveFrame::on_pushButton_5_clicked()
{
    //delete curve
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
       chart->setTitle("Simple line chart example");
       chart->setGeometry(0,0,500,300);

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
