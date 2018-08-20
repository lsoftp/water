#include "closedlg.h"
#include "ui_closedlg.h"

CloseDlg::CloseDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

CloseDlg::~CloseDlg()
{
    delete ui;
}

void CloseDlg::on_pushButton_3_clicked()
{
    this->close();
}

void CloseDlg::on_pushButton_2_clicked()
{
    i=1;
}

void CloseDlg::on_pushButton_clicked()
{
    i=0;
}
