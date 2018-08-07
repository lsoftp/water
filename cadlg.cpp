#include "cadlg.h"
#include "ui_cadlg.h"

CaDlg::CaDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaDlg)
{
    ui->setupUi(this);
    //setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
}

CaDlg::CaDlg(QString a, QString b, QString c):
    QDialog (0),
    ui(new Ui::CaDlg)
{
    ui->setupUi(this);
    ui->lineEdit_2->setText(a);
    ui->lineEdit->setText(b);
    ui->dateEdit->setDate(QDate::fromString(c,"yyyy/M/d"));
}

CaDlg::~CaDlg()
{
    delete ui;
}

void CaDlg::on_pushButton_clicked()
{
    name=ui->lineEdit_2->text();
    no=ui->lineEdit->text();
    valid=ui->dateEdit->text();
}

