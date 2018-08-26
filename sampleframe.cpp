#include "sampleframe.h"
#include "ui_sampleframe.h"
#include "printer.h"

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

void SampleFrame::on_printbtn_clicked()
{
    Printer p;
   // QPrintDialog pp(&p.p);
    //pp.exec();
    QPrintPreviewDialog pp(&p.p);
    connect(&pp, SIGNAL(paintRequested(QPrinter*)),
                &p, SLOT(printDocument(QPrinter*)));
    pp.exec();
}
