#include "stopsampledia.h"
#include "ui_stopsampledlg.h"

StopSDia::StopSDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

StopSDia::~StopSDia()
{
    delete ui;
}