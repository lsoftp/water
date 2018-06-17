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

void ItemFrame::init()
{
    connect(ui->pushButton_5,SIGNAL(clicked()),g_w,SLOT(display_blank()));
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

