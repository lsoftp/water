#include "statusframe.h"
#include "ui_statusframe.h"

StatusFrame::StatusFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::StatusFrame)
{
    ui->setupUi(this);
}

StatusFrame::~StatusFrame()
{
    delete ui;
}
