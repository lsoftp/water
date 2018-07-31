#include "itemframe.h"
#include "ui_itemframe.h"
#include "mainwindow.h"
#include<QLineEdit>

ItemFrame::ItemFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ItemFrame)
{
    ui->setupUi(this);
    //ui->radioButton->setChecked(true);
    //不可编辑
    ui->tableWidget1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget1->setSelectionMode(QAbstractItemView::SingleSelection);

    QHeaderView *header = ui->tableWidget1->verticalHeader();
    header->setHidden(true);// 隐藏行号
    initCombo();
    refreshtable();

}
int  ItemFrame::getfreeNo()
{
    QSqlQueryModel sqm;
    db.getItemNo(sqm);

    int j=-1,num=sqm.rowCount();
    if(num==0)
    {

        return 0;
    }
    for(int i=0;i<num;i++)
    {
        int k=sqm.record(i).value("TestID").toInt();
        int p=k-j;

        if(p>1)
        {

            return j+1;
        }
        j=k;
    }
    return j+1;
}

void ItemFrame::initCombo()
{
    QSqlQueryModel sqm;
    db.getReagent(sqm);

    for(int i=0;i<sqm.rowCount();i++)
    {
        int id=sqm.record(i).value(0).toInt();
        QString rn=sqm.record(i).value(1).toString();
        ui->comboBox_31->addItem(rn,id);
        ui->comboBox_32->addItem(rn,id);
        ui->comboBox_33->addItem(rn,id);
        ui->comboBox_34->addItem(rn,id);
        ui->comboBox_35->addItem(rn,id);
    }
}

ItemFrame::~ItemFrame()
{
    delete ui;
}

void ItemFrame::load(Item &it)
{
    it.name=ui->lineEdit_9->text();
    it.fullname=ui->lineEdit_11->text();
    if(ui->lineEdit_13->text().compare(""))
        it.tc.wavenum=1;
    else
        it.tc.wavenum=2;//to be modified according to the wl0,wl1
    it.tc.wl0=ui->lineEdit_12->text().toInt();
    it.tc.wl1=ui->lineEdit_13->text().toInt();

    it.digitnum=ui->comboBox_13->currentText();
    it.unit=ui->comboBox_14->currentText();

    it.limitlow=ui->lineEdit_14->text();
    it.limitlowjudge=ui->comboBox_15->currentText();

    it.limithigh=ui->lineEdit_15->text();
    it.limithighjudge=ui->comboBox_16->currentText();

    it.linearlow=ui->lineEdit_22->text();
    it.linearhigh=ui->lineEdit_23->text();

    it.correctA=ui->lineEdit_24->text();
    it.correctB=ui->lineEdit_25->text();

    it.xgdlimit=ui->checkBox->isChecked();
    it.xgdlimitvalue=ui->lineEdit_26->text();

    it.kbxgd=ui->checkBox_2->isChecked();
    it.kbxgd1=ui->lineEdit_28->text();
    it.kbxgd2=ui->lineEdit_27->text();
    it.xxd=ui->checkBox_4->isChecked();
    it.xxdvalue=ui->lineEdit_30->text();

    it.tc.isreplace=ui->checkBox_3->isChecked();
    it.tc.repalcereagentid=ui->comboBox_30->currentData().toInt();

    it.tc.reagent0=ui->comboBox_35->currentData().toInt();
    it.tc.v0=ui->lineEdit_32->text().toInt();
    it.tc.time0=ui->lineEdit_33->text().toInt();

    it.tc.reagent1=ui->comboBox_31->currentData().toInt();
    it.tc.v1=ui->lineEdit_35->text().toInt();
    it.tc.time1=ui->lineEdit_34->text().toInt();

    it.tc.reagent2=ui->comboBox_33->currentData().toInt();
    it.tc.v2=ui->lineEdit_37->text().toInt();
    it.tc.time2=ui->lineEdit_36->text().toInt();

    it.tc.reagent3=ui->comboBox_34->currentData().toInt();
    it.tc.v3=ui->lineEdit_39->text().toInt();
    it.tc.time3=ui->lineEdit_38->text().toInt();

    it.tc.reagent4=ui->comboBox_32->currentData().toInt();
    it.tc.v4=ui->lineEdit_42->text().toInt();
    it.tc.time4=ui->lineEdit_40->text().toInt();

    if(ui->radioButton->isChecked())
        it.tc.method=1;
    else if(ui->radioButton_2->isChecked())
        it.tc.method=2;
    else
        it.tc.method=3;

    it.tc.readstep=ui->comboBox_17->currentText().toInt();
    it.tc.readtimes=ui->lineEdit_17->text().toInt();
    it.tc.readinterval=ui->lineEdit_10->text().toInt();

    it.redodiluteid=ui->comboBox->currentData().toInt();

    it.redoxxfflow=ui->lineEdit->text();
    it.redoxxffhigh=ui->lineEdit_2->text();
    it.redoxxfftimes=ui->lineEdit_3->text();

    it.redodilute1low=ui->lineEdit_5->text();
    it.redodilute1high=ui->lineEdit_4->text();
    it.redodilute1times=ui->lineEdit_6->text();

    it.redodilute2low=ui->lineEdit_8->text();
    it.redodilute2high=ui->lineEdit_7->text();
    it.redodilute2times=ui->lineEdit_18->text();

    it.redootherlow=ui->lineEdit_20->text();
    it.redootherhigh=ui->lineEdit_19->text();
    it.redoothertimes=ui->lineEdit_21->text();
}

void ItemFrame::add()
{
    QList<QLineEdit *> ls = ui->tabWidget_2->findChildren<QLineEdit *>();
    foreach(QLineEdit *le,ls)
    {
        le->clear();
    }





}

void ItemFrame::init()
{
    connect(ui->return_btn,SIGNAL(clicked()),g_w,SLOT(on_srreturnbtn_clicked()));
    //ui->com
}

void ItemFrame::setDbstatus(int s)
{

    dbstatus=s;
    switch(dbstatus){
    case 0:ui->pushButton_4->setEnabled(false);break;
    case 1:ui->pushButton_4->setEnabled(true);break; //new
    case 2:ui->pushButton_4->setEnabled(true);break; //modify
    }
}

void ItemFrame::on_radioButton_2_toggled(bool checked)
{
    if (!checked) return;
   ui->groupBox_9->show();
   ui->groupBox_10->hide();
}

void ItemFrame::on_radioButton_3_toggled(bool checked)
{
    if (!checked) return;
    ui->groupBox_9->hide();
    ui->groupBox_10->show();
}

void ItemFrame::on_radioButton_toggled(bool checked)
{
    if (!checked) return;
    ui->groupBox_9->hide();
    ui->groupBox_10->hide();
}
#include <QMessageBox>
void ItemFrame::display_blank()
{
    QMessageBox::question(NULL, "question", "QString::number(i)", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void ItemFrame::refreshtable()
{
    QSqlQueryModel sqm;
    db.getItem(sqm);
    QTableWidget *tw=ui->tableWidget1;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount());
    for(int i=0;i<sqm.rowCount();i++)
    {
        tw->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("name").toString()));

    }

}


void ItemFrame::on_pushButton_2_clicked()
{
    add();
}

void ItemFrame::on_tableWidget1_itemSelectionChanged()
{
    QList<QTableWidgetItem*> items=ui->tableWidget1->selectedItems();
    if(items.size()==0) return;
    QString name=items.at(1)->text();
    QSqlQueryModel sqm;
    db.getItembyname(sqm,name);
    int i=0;
    Item it;
#define ITEM_I(p,q) q=sqm.record(i).value(p).toInt()
#define ITEM_C(p,q) q=sqm.record(i).value(p).toString()
    //it.tc.test_id=sqm.record(i).value()
    ITEM_I(0,it.tc.test_id);
    ITEM_C(1,it.name);
    ITEM_C(2,it.fullname);
    ITEM_I(3,it.tc.reagent0);
    ITEM_I(4,it.tc.time0);
    ITEM_I(5,it.tc.v0);
    ITEM_I(6,it.tc.reagent1);
    ITEM_I(7,it.tc.time1);
    ITEM_I(8,it.tc.v1);
    ITEM_I(9,it.tc.reagent2);
    ITEM_I(10,it.tc.time2);
    ITEM_I(11,it.tc.v2);
    ITEM_I(12,it.tc.reagent3);
    ITEM_I(13,it.tc.time3);

    ITEM_I(14,it.tc.v3);
    ITEM_I(15,it.tc.reagent4);
    ITEM_I(16,it.tc.time4);
    ITEM_I(17,it.tc.v4);

    ITEM_I(18,it.tc.priority);
    ITEM_I(19,it.tc.isreplace);
    ITEM_I(20,it.tc.repalcereagentid);
    ITEM_I(21,it.tc.method);
    ITEM_I(22,it.tc.readstep);
    ITEM_I(23,it.tc.readinterval);
    ITEM_I(24,it.tc.readtimes);
    ITEM_I(25,it.tc.wavenum);
    ITEM_I(26,it.tc.wl0);
    ITEM_I(27,it.tc.wl1);
    ITEM_C(28,it.digitnum);
    ITEM_C(29,it.unit);
    ITEM_C(30,it.checkmethod);
    ITEM_C(31,it.limitlow);
    ITEM_C(32,it.limitlowjudge);
    ITEM_C(33,it.limithigh);
    ITEM_C(34,it.limithighjudge);
    ITEM_C(35,it.linearlow);
    ITEM_C(36,it.linearhigh);
    ITEM_C(37,it.correctA);
    ITEM_C(38,it.correctB);
    ITEM_I(39,it.xgdlimit);
    ITEM_C(40,it.xgdlimitvalue);
    ITEM_I(41,it.kbxgd);
    ITEM_C(42,it.kbxgd1);
    ITEM_C(43,it.kbxgd2);
    ITEM_I(44,it.xxd);
    ITEM_C(45,it.xxdvalue);
    ITEM_I(46,it.redodiluteid);
    ITEM_C(47,it.redoxxfflow);
    ITEM_C(48,it.redoxxffhigh);
    ITEM_C(49,it.redoxxfftimes);
    ITEM_C(50,it.redodilute1low);
    ITEM_C(51,it.redodilute1high);
    ITEM_C(52,it.redodilute1times);
    ITEM_C(53,it.redodilute2low);
    ITEM_C(54,it.redodilute2high);
    ITEM_C(55,it.redodilute2times);
    ITEM_C(56,it.redootherlow);
    ITEM_C(57,it.redootherhigh);
    ITEM_C(58,it.redoothertimes);

    ui->lineEdit_9->setText(it.name);
    ui->lineEdit_11->setText(it.fullname);
//    if(ui->lineEdit_13->text().compare(""))
//        it.tc.wavenum=1;
//    else
//        it.tc.wavenum=2;//to be modified according to the wl0,wl1
    ui->lineEdit_12->setText(QString::number(it.tc.wl0));
    ui->lineEdit_13->setText(QString::number(it.tc.wl1));

    //it.digitnum=ui->comboBox_13->currentText();
    i=ui->comboBox_13->findText(it.digitnum);
    ui->comboBox_13->setCurrentIndex(i);
    i=ui->comboBox_14->findText(it.unit);
    ui->comboBox_14->setCurrentIndex(i);
    //it.unit=ui->comboBox_14->currentText();

    ui->lineEdit_14->setText(it.limitlow);
    i=ui->comboBox_15->findText(it.limitlowjudge);
    ui->comboBox_15->setCurrentIndex(i);
    //=ui->comboBox_15->currentText();

    ui->lineEdit_15->setText(it.limithigh);
    //it.limithighjudge=ui->comboBox_16->currentText();
    i=ui->comboBox_16->findText(it.limithighjudge);
    ui->comboBox_16->setCurrentIndex(i);


    ui->lineEdit_22->setText(it.linearlow);
    ui->lineEdit_23->setText(it.linearhigh);

    ui->lineEdit_24->setText(it.correctA);
    ui->lineEdit_25->setText(it.correctB);

    ui->checkBox->setChecked(it.xgdlimit);
    ui->lineEdit_26->setText(it.xgdlimitvalue);

    ui->checkBox_2->setChecked(it.kbxgd);
    ui->lineEdit_28->setText(it.kbxgd1);
    ui->lineEdit_27->setText(it.kbxgd2);
    ui->checkBox_4->setChecked(it.xxd);
    ui->lineEdit_30->setText(it.xxdvalue);

    ui->checkBox_3->setChecked(it.tc.isreplace);

    i=ui->comboBox_30->findData(it.tc.repalcereagentid);
    ui->comboBox_30->setCurrentIndex(i);
// to be updated
    i=ui->comboBox_35->findData(it.tc.reagent0);
    ui->comboBox_35->setCurrentIndex(i);
    //it.tc.reagent0=ui->comboBox_35->currentData().toInt();
    ui->lineEdit_32->setText(QString::number(it.tc.v0));
    ui->lineEdit_33->setText(QString::number(it.tc.time0));

    i=ui->comboBox_31->findData(it.tc.reagent1);
    ui->comboBox_31->setCurrentIndex(i);
//    it.tc.reagent1=ui->comboBox_31->currentData().toInt();
    ui->lineEdit_35->setText(QString::number(it.tc.v1));
    ui->lineEdit_34->setText(QString::number(it.tc.time1));

    i=ui->comboBox_33->findData(it.tc.reagent2);
    ui->comboBox_33->setCurrentIndex(i);
    //it.tc.reagent2=ui->comboBox_33->currentData().toInt();
    ui->lineEdit_37->setText(QString::number(it.tc.v2));
    ui->lineEdit_36->setText(QString::number(it.tc.time2));

    i=ui->comboBox_34->findData(it.tc.reagent3);
    ui->comboBox_34->setCurrentIndex(i);

//    it.tc.reagent3=ui->comboBox_34->currentData().toInt();
    ui->lineEdit_39->setText(QString::number(it.tc.v3));
    ui->lineEdit_38->setText(QString::number(it.tc.time3));

    i=ui->comboBox_32->findData(it.tc.reagent4);
    ui->comboBox_32->setCurrentIndex(i);
    //it.tc.reagent4=ui->comboBox_32->currentData().toInt();
    ui->lineEdit_42->setText(QString::number(it.tc.v4));
    ui->lineEdit_40->setText(QString::number(it.tc.time4));

    if(it.tc.method==1)
        ui->radioButton->setChecked(true);
    else if(it.tc.method==2)
        ui->radioButton_2->setChecked(true);
    else
        ui->radioButton_3->setChecked(true);

    i=ui->comboBox_17->findText(QString::number(it.tc.readstep));
    ui->comboBox_17->setCurrentIndex(i);
     ui->lineEdit_17->setText(QString::number(it.tc.readtimes));
     ui->lineEdit_10->setText(QString::number(it.tc.readinterval));

     ui->comboBox->findData(it.redodiluteid);
     ui->comboBox->setCurrentIndex(i);
    //it.redodiluteid=ui->comboBox->currentData().toInt();

    ui->lineEdit->setText(it.redoxxfflow);
    ui->lineEdit_2->setText(it.redoxxffhigh);
    ui->lineEdit_3->setText(it.redoxxfftimes);

    ui->lineEdit_5->setText(it.redodilute1low);
    ui->lineEdit_4->setText(it.redodilute1high);
    ui->lineEdit_6->setText(it.redodilute1times);

    ui->lineEdit_8->setText(it.redodilute2low);
    ui->lineEdit_7->setText(it.redodilute2high);
    ui->lineEdit_18->setText(it.redodilute2times);

    ui->lineEdit_20->setText(it.redootherlow);
    ui->lineEdit_19->setText(it.redootherhigh);
    ui->lineEdit_21->setText(it.redoothertimes);

}

void ItemFrame::on_pushButton_4_clicked()
{
    Item it;
    //save
    db.delItembyName(ui->lineEdit_9->text());
    load(it);
    it.tc.test_id=getfreeNo();
    it.tc.priority=it.tc.test_id;
    db.insertItem(it);
    refreshtable();
}
