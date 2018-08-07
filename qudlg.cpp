#include "qudlg.h"
#include "ui_qudlg.h"

QuDlg::QuDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuDlg)
{
    ui->setupUi(this);
}

QuDlg::~QuDlg()
{
    delete ui;
}
