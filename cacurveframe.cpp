#include "cacurveframe.h"
#include "ui_cacurveframe.h"
#include "cadlg.h"
#include <QDebug>

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

void CaCurveFrame::refreshtable()
{

}

void CaCurveFrame::on_pushButton_clicked()
{
    CaDlg cd;
    cd.setWindowTitle("添加标准液");
    cd.setWindowFlags(cd.windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
    int i=cd.exec();
    if(i==QDialog::Accepted)
    {
        qDebug()<<cd.name<<cd.no<<cd.valid;
    }

}

void CaCurveFrame::on_pushButton_2_clicked()
{
    CaDlg cd("hahah","b","2018/8/8");
    cd.setWindowTitle("编辑标准液");
    //cd.name="sdf";
    int i=cd.exec();
    if(i==QDialog::Accepted)
    {
        qDebug()<<cd.name<<cd.no<<cd.valid;
    }
}
