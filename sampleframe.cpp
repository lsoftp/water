#include "sampleframe.h"
#include "ui_sampleframe.h"

SampleFrame::SampleFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SampleFrame)
{
    ui->setupUi(this);
    ui->tabWidget->setStyleSheet("QLineEdit { background-color: white }QDateEdit { background-color: white }");
}

SampleFrame::~SampleFrame()
{
    delete ui;
}
