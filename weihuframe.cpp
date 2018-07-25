#include "weihuframe.h"
#include "ui_weihuframe.h"

WeihuFrame::WeihuFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WeihuFrame)
{
    ui->setupUi(this);
}

WeihuFrame::~WeihuFrame()
{
    delete ui;
}
