#include "comboitem1.h"
#include "ui_comboitem1.h"

ComboItem1::ComboItem1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComboItem1)
{
    ui->setupUi(this);
}

ComboItem1::~ComboItem1()
{
    delete ui;
}
