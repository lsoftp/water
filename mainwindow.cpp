#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handlethread.h"
#include "sampleregister.h"
#include "interface.h"
#include "stopsampledia.h"
//按钮的宽度


//全局数据索引，默认为当前日期，如果选定了其他的日期，则切换到其他的日期

QString g_current_index=QDateTime::currentDateTime().toString("yyyy-MM-dd");


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sr=new SampleRegister(this);
    ui->lineEdit->setText("hahahah");
    ui->lineEdit->setReadOnly(true);
    memset(pb,NULL,sizeof(pb));
    memset(pb1,NULL,sizeof(pb1));
    memset(pb2,NULL,sizeof(pb2));
    initGUI();
    this->initFrames();
    display(G_HOME);
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
    initsabutton();
    ui->tableWidget->setRowCount(40);
    initcabutton();
    initqubutton();
    //
    ui->comboBox->setEditText("sdfsdfjkl");


    SampleButton *sb=new SampleButton(ui->frame);
    sb->setGeometry(0,0,50,60);
     ui->tableWidget->setColumnWidth(0,60);
     ui->radioButton->setChecked(true);
     //ui->frame_3->setEnabled(false);
     ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

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


void MainWindow::initsabutton()
{
    QWidget *qw=ui->frame_4;
    //qw->deleteLater();

    for(int i=0;i<11;i++)
    {
        pb[i]= new ItemButton(qw);
        pb[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb[i]= new ItemButton(qw);
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb[i]= new ItemButton(qw);
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb[i]= new ItemButton(qw);
        pb[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }
    qw=ui->frame_10;
    //qw->deleteLater();

    for(int i=0;i<11;i++)
    {
        pb[i+38]= new ItemButton(qw);
        pb[i+38]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb[i+38]= new ItemButton(qw);
        pb[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb[i+38]= new ItemButton(qw);
        pb[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb[i+38]= new ItemButton(qw);
        pb[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }

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

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (!checked) return;
   ui->groupBox_9->show();
   ui->groupBox_10->hide();
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if (!checked) return;
    ui->groupBox_9->hide();
    ui->groupBox_10->show();
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if (!checked) return;
    ui->groupBox_9->hide();
    ui->groupBox_10->hide();
}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index==0)
    {
        sr->initstate();
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

void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    sr->showpage(index);
}

void MainWindow::on_sr_del_clicked()
{
int j=ui->comboBox_4->findText("二");
qDebug("er is %d",j);
}

void MainWindow::ontoggle(bool b)
{
    bool isOK=false;
    for (int i=0;i<itemnum;i++)
    {
        if(pb[i]->isChecked())
        {
            isOK=true;
            break;
        }

    }
    if(isOK)
    {
        sr->setYesEnable(true);
    }
    else
    {
        sr->setYesEnable(false);
    }
}

void MainWindow::on_pushButton_6_toggled(bool checked)
{

}

void MainWindow::on_sr_yes_clicked()
{
    sr->reg();
    sr->initstate();
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
#include<QMessageBox>
void MainWindow::on_toolButton_9_clicked()
{
    ::StopSDia  dl;
    int i=dl.exec();

    QMessageBox::question(NULL, "question", QString::number(i), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
