#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handlethread.h"
#include "sampleregister.h"
//按钮的宽度


//全局数据索引，默认为当前日期，如果选定了其他的日期，则切换到其他的日期

QString g_current_index=QDateTime::currentDateTime().toString("yyyy-MM-dd");


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sr=new SampleRegister(this);
    memset(pb,NULL,sizeof(pb));
    memset(pb1,NULL,sizeof(pb1));
    memset(pb2,NULL,sizeof(pb2));
    initGUI();
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
    ui->frame_2->hide();
    ui->frame_3->hide();
    initsabutton();

    initcabutton();
    initqubutton();
    ui->comboBox->setCurrentText("sdfsdfjkl");\
    SampleButton *sb=new SampleButton(ui->frame);
    sb->setGeometry(0,0,50,60);
     ui->tableWidget->setColumnWidth(0,60);
     ui->radioButton->setChecked(true);
     //ui->frame_3->setEnabled(false);
     ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

void MainWindow::on_toolButton_8_clicked()
{
    if(!g_handler.command)
    g_handler.command=1;
}

void MainWindow::on_pushButton_9_clicked()
{    ui->frame->show();
     ui->frame_2->hide();
     ui->frame_3->hide();

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
    on_toolButton_clicked();
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
