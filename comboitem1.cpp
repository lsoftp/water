#include "comboitem1.h"
#include "ui_comboitem1.h"
#include "dbinterface.h"

ComboItem1::ComboItem1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComboItem1)
{
    ui->setupUi(this);
    initTestList();
}

ComboItem1::~ComboItem1()
{
    delete ui;
}

void ComboItem1::initTestList()
{
    QSqlQueryModel sqm;
    db.getTestItem(sqm);
    for(int i=0; i<sqm.rowCount();i++)
    {
        ui->comboBox->addItem(sqm.record(i).value("name").toString(),sqm.record(i).value("TestID").toInt());
    }

}

ComboItem1::ComboItem1(QString name):
    QDialog(0),
    ui(new Ui::ComboItem1)
{
    int i;
    ui->setupUi(this);
    initTestList();
    i=ui->comboBox->findText(name);
    ui->comboBox->setCurrentIndex(i);

}
void ComboItem1::on_pushButton_clicked()
{
    item=ui->comboBox->currentText();
    testid=ui->comboBox->currentData().toInt();
}
