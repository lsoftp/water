#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handlethread.h"

#include "interface.h"
#include "stopsampledia.h"
//按钮的宽度


//全局数据索引，默认为当前日期，如果选定了其他的日期，则切换到其他的日期

QString g_current_index=QDateTime::currentDateTime().toString("yyyy-MM-dd");
int g_item_num=0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setText("hahahah");
    ui->lineEdit->setReadOnly(true);

    initGUI();
    this->initFrames();
    display(G_HOME);
    //ui->frame_3->init();
}
//初始化界面
void MainWindow::initGUI()
{
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


    SampleButton *sb=new SampleButton(ui->frame);
    sb->setGeometry(0,0,50,60);

}
//assign frames index
void MainWindow::initFrames()
{
    pf[GUIFrame::G_BLANK]=ui->frame_13;
    pf[GUIFrame::G_HOME]=ui->frame;
    pf[GUIFrame::G_REGISTER]=ui->frame_2;
    pf[GUIFrame::G_ITEM]=ui->frame_3;
    pf[GUIFrame::G_START]=ui->frame_11;
}

void MainWindow::display(GUIFrame frame)
{
    for(int i=0;i<GUIFrame::G_NUM;i++)
    {
        if(i!=frame) pf[i]->hide();
        else pf[frame]->show();
    }

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::initsignal()
{
        ui->frame_3->init();
}




void MainWindow::on_toolButton_clicked()
{
    display(G_REGISTER);
    //ui->frame_2->tabWidget->hide();

}

void MainWindow::on_toolButton_5_clicked()
{
    display(GUIFrame::G_ITEM);
}

void MainWindow::on_toolButton_8_clicked()
{
    display(G_START);
    Interface::initTestrowArray();
    if(!g_handler.command)
    g_handler.command=1;
}

void MainWindow::on_pushButton_9_clicked()
{
    //register return button
    display(G_HOME);
}




void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index==0)
    {
        ui->tab->initstate();
    }
}

void MainWindow::on_toolButton_13_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_14_clicked()
{
    display(G_BLANK);
}

void MainWindow::on_pushButton_6_clicked()
{

}






void MainWindow::on_pushButton_6_toggled(bool checked)
{

}



void MainWindow::on_pushButton_15_clicked()
{
    display(G_BLANK);
}

void MainWindow::on_pushButton_16_clicked()
{
    display(G_BLANK);
}

void MainWindow::on_pushButton_13_clicked()
{
    display(G_BLANK);
}
//stop sample button
void MainWindow::on_toolButton_9_clicked()
{
    ::StopSDia  dl;
    int i=dl.exec();

    // QMessageBox::question(NULL, "question", QString::number(i), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void MainWindow::display_blank()
{
    display(G_BLANK);
}
