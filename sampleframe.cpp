#include "sampleframe.h"
#include "ui_sampleframe.h"

SampleFrame::SampleFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SampleFrame)
{
    ui->setupUi(this);
}

SampleFrame::~SampleFrame()
{
    delete ui;
}
