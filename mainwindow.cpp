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


   // SampleButton *sb=new SampleButton(ui->frame);
    //sb->setGeometry(0,0,50,60);

}
//assign frames index
void MainWindow::initFrames()
{
    pf[GUIFrame::G_BLANK]=ui->frame_13;
    pf[GUIFrame::G_HOME]=ui->frame;
    pf[GUIFrame::G_REGISTER]=ui->frame_2;
    pf[GUIFrame::G_ITEM]=ui->frame_3;
    pf[GUIFrame::G_START]=ui->frame_11;
    pf[G_CACURVE]=ui->cacurve;
    pf[G_QUFRAME]=ui->quframe;
    pf[G_STATUS]=ui->frame_4;
    pf[G_WEIHU]=ui->g_weihu;
    pf[G_SYSTEM]=ui->g_system;
    pf[G_SAMPLE]=ui->g_sample;

    ptb[GUIFrame::G_BLANK]=NULL;
    ptb[GUIFrame::G_HOME]=NULL;
    ptb[GUIFrame::G_REGISTER]=ui->toolButton;
    ptb[GUIFrame::G_ITEM]=ui->toolButton_5;
    ptb[GUIFrame::G_START]=ui->toolButton_8;
    ptb[G_CACURVE]=ui->toolButton_3;
    ptb[G_QUFRAME]=ui->toolButton_4;
    ptb[G_STATUS]=ui->toolButton_11;
    ptb[G_WEIHU]=ui->toolButton_6;
    ptb[G_SYSTEM]=ui->toolButton_7;
    ptb[G_SAMPLE]=ui->toolButton_2;
    //ptb[GUIFrame::G_REGISTER]->setStyleSheet("background-color: rgb(214, 214, 214);");//setStyleSheet("background-color: rgb(85, 255, 255);");
}

void MainWindow::display(GUIFrame frame)
{
    for(int i=0;i<GUIFrame::G_NUM;i++)
    {
        if(i!=frame)
        {
            pf[i]->hide();
            //if(ptb[i]) ptb[i]->setStyleSheet("background-color: rgb(214, 214, 214);");
        }
        else
        {
            pf[i]->show();
            //if(ptb[i]) ptb[i]->setStyleSheet("background-color: rgb(85, 255, 255);");

        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::initsignal()
{
    ui->frame_3->init();
    ui->tab_2->init();
    ui->tab_3->init();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
//    g_handler.terminate();
//    g_handler.wait();
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
    if(!g_handler.command)
    {
        display(G_START);
        Interface::initTestrowArray();
        g_handler.command=1;
    }
    else
    {
        QMessageBox box(QMessageBox::Information,"提示","正在处理中，请稍候操作");
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
        box.exec ();
    }
}

void MainWindow::on_srreturnbtn_clicked()
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

     QMessageBox::information(NULL, "注意", QString("是否停止采样?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void MainWindow::display_blank()
{
    display(G_BLANK);
}

void MainWindow::on_toolButton_11_clicked()
{
    display(G_STATUS);
}

void MainWindow::on_MainWindow_destroyed()
{

}

void MainWindow::on_toolButton_3_clicked()
{
    display(G_CACURVE);
}

void MainWindow::on_toolButton_4_clicked()
{
    display(G_QUFRAME);
}

void MainWindow::on_toolButton_2_clicked()
{
    display(GUIFrame::G_SAMPLE);
}

void MainWindow::on_toolButton_6_clicked()
{
    display(G_WEIHU);
}

void MainWindow::on_toolButton_7_clicked()
{
    display(G_SYSTEM);
}
