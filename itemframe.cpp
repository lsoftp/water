#include "itemframe.h"
#include "ui_itemframe.h"
#include "mainwindow.h"

ItemFrame::ItemFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ItemFrame)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(true);

}

ItemFrame::~ItemFrame()
{
    delete ui;
}

void ItemFrame::add()
{
    QObjectList list =ui->tab_4-> children();
        foreach (QObject *obj, list) {
            QString nnn=obj->metaObject()->className();
            if ( nnn== "QLineEdit"){
                QLineEdit *ql=qobject_cast<QLineEdit*>(obj);
                ql->setText("");

            }
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




void ItemFrame::on_pushButton_2_clicked()
{
    add();
}
