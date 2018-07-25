#include "systemframe.h"
#include "ui_systemframe.h"

SystemFrame::SystemFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SystemFrame)
{
    ui->setupUi(this);
}

SystemFrame::~SystemFrame()
{
    delete ui;
}
