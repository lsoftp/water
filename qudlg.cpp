#include "qudlg.h"
#include "ui_qudlg.h"

QuDlg::QuDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuDlg)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

QuDlg::~QuDlg()
{
    delete ui;
}

QuDlg::QuDlg(QString a, QString b, QString c):
    QDialog (0),
    ui(new Ui::QuDlg)
{
    ui->setupUi(this);
    ui->lineEdit_2->setText(a);
    ui->lineEdit->setText(b);
    ui->dateEdit->setDate(QDate::fromString(c,"yyyy/M/d"));
}




void QuDlg::on_pushButton_clicked()
{
    name=ui->lineEdit_2->text();
    no=ui->lineEdit->text();
    valid=ui->dateEdit->text();
}
