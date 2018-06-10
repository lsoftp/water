#include "mainwindow.h"
#include "ui_mainwindow.h"
#define IB_LENGTH 50
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->pushButton_2->setStyleSheet("text-align: left;");
            //setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_7->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_8->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_9->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_10->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_11->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_12->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_13->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_14->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->frame_2->hide();
    ui->frame_3->hide();
    QWidget *qw=ui->frame_4;
    for(int i=0;i<11;i++)
    {
        pb[i]= new ItemButton(qw);
        pb[i]->setText("test");
        pb[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb[i]= new ItemButton(qw);
        pb[i]->setText("test");
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb[i]= new ItemButton(qw);
        pb[i]->setText("test");
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb[i]= new ItemButton(qw);
        pb[i]->setText("test");
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }
    initcabutton();
    initqubutton();
    ui->comboBox->setCurrentText("sdfsdfjkl");\
    SampleButton *sb=new SampleButton(ui->frame);
    sb->setGeometry(0,0,50,60);
     ui->tableWidget->setColumnWidth(0,60);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initqubutton()
{
    QWidget *qw=ui->frame_6;
    for(int i=0;i<11;i++)
    {
        pb2[i]= new ItemButton(qw);
        pb2[i]->setText("test");
        pb2[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb2[i]= new ItemButton(qw);
        pb2[i]->setText("test");
        pb2[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb2[i]= new ItemButton(qw);
        pb2[i]->setText("test");
        pb2[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb2[i]= new ItemButton(qw);
        pb2[i]->setText("test");
        pb2[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }

}
void MainWindow::initcabutton()
{
    QWidget *qw=ui->frame_5;
    for(int i=0;i<11;i++)
    {
        pb1[i]= new CaButton(qw);
        pb1[i]->setText("test");
        pb1[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb1[i]= new CaButton(qw);
        pb1[i]->setText("test");
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb1[i]= new CaButton(qw);
        pb1[i]->setText("test");
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb1[i]= new CaButton(qw);
        pb1[i]->setText("test");
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }

}

void MainWindow::on_toolButton_clicked()
{
    ui->frame->hide();
    ui->frame_2->show();
    ui->frame_3->hide();
    //ui->frame_2->tabWidget->hide();

}

void MainWindow::on_toolButton_5_clicked()
{
    ui->frame->hide();
    ui->frame_2->hide();
    ui->frame_3->show();
}
