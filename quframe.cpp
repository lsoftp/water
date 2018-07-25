#include "quframe.h"
#include "ui_quframe.h"

QuFrame::QuFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QuFrame)
{
    ui->setupUi(this);
}

QuFrame::~QuFrame()
{
    delete ui;
}
