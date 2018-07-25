#include "cacurveframe.h"
#include "ui_cacurveframe.h"

CaCurveFrame::CaCurveFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CaCurveFrame)
{
    ui->setupUi(this);
}

CaCurveFrame::~CaCurveFrame()
{
    delete ui;
}
