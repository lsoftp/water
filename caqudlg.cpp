#include "caqudlg.h"
#include "ui_caqudlg.h"

CaQuDlg::CaQuDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaQuDlg)
{
    ui->setupUi(this);
    initTestList();
}

CaQuDlg::CaQuDlg(QString a, QString b, QString c):
    QDialog(0),
    ui(new Ui::CaQuDlg)
{
    int i;
    ui->setupUi(this);
    initTestList();
    i=ui->comboBox->findText(a);
    ui->comboBox->setCurrentIndex(i);
    ui->lineEdit->setText(b);
    i=ui->comboBox_2->findText(c);
    ui->comboBox_2->setCurrentIndex(i);
}

CaQuDlg::~CaQuDlg()
{
    delete ui;
}

void CaQuDlg::on_pushButton_clicked()
{
    testname=ui->comboBox->currentText();
    con=ui->lineEdit->text();
    unit=ui->comboBox_2->currentText();

}

void CaQuDlg::initTestList()
{
    QSqlQueryModel sqm;
    db.getTestItem(sqm);
    for(int i=0; i<sqm.rowCount();i++)
    {
        ui->comboBox->addItem(sqm.record(i).value("name").toString(),sqm.record(i).value("TestID").toInt());
    }

}
