#include "comboitem.h"
#include "ui_comboitem.h"

ComBoItem::ComBoItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComBoItem)
{
    ui->setupUi(this);
}

ComBoItem::ComBoItem(QString n) :
    QDialog (0),name(n),
    ui(new Ui::ComBoItem)
{
    ui->setupUi(this);
    ui->lineEdit->setText(name);
}

ComBoItem::~ComBoItem()
{
    delete ui;
}

void ComBoItem::on_pushButton_clicked()
{
    name=ui->lineEdit->text();
}
