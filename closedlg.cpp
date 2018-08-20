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
