#include "comboitem.h"
#include "ui_comboitem.h"

ComBoItem::ComBoItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComBoItem)
{
    ui->setupUi(this);
}

ComBoItem::~ComBoItem()
{
    delete ui;
}
