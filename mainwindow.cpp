#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handlethread.h"

#include "interface.h"
#include "closedlg.h"
//按钮的宽度


//全局数据索引，默认为当前日期，如果选定了其他的日期，则切换到其他的日期

QString g_current_index=QDateTime::currentDateTime().toString("yyyy-MM-dd");
int g_item_num=0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->lineEdit->setText("hahahah");
    ui->lineEdit->setReadOnly(true);

    initGUI();
    this->initFrames();
    warnInittable();
    display(G_HOME);
    initsignal();
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
    pf[GUIFrame::G_WARN]=ui->frame_13;
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

    ptb[GUIFrame::G_WARN]=NULL;
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

void MainWindow::warnInittable()
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget ->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget ->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableWidget->setStyleSheet("QTableWidget{selection-background-color:blue;}");
    QHeaderView *header = ui->tableWidget ->verticalHeader();
    header->setHidden(true);// 隐藏行号
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,600);
    ui->tableWidget->setColumnWidth(2,149);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::initsignal()
{

    connect(ui->tab,SIGNAL(back()),this,SLOT(displayHome()));
    connect(ui->tab_2,SIGNAL(back()),this,SLOT(displayHome()));
    connect(ui->tab_3,SIGNAL(back()),this,SLOT(displayHome()));
    connect(ui->frame_3,SIGNAL(back()),this,SLOT(displayHome()));

    connect(pf[G_CACURVE],SIGNAL(back()),this,SLOT(displayHome()));
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
    //    if(!g_handler.command)
    //    {
    //        display(G_START);
    //        Interface::initTestrowArray();
    //        g_handler.command=1;
    //    }
    //    else
    //    {
    //        QMessageBox box(QMessageBox::Information,"提示","正在处理中，请稍候操作");
    //        box.setStandardButtons (QMessageBox::Ok);
    //        box.setButtonText (QMessageBox::Ok,QString("确 定"));
    //        //box.setButtonText (QMessageBox::Cancel,QString("取 消"));
    //        box.exec ();
    //    }
    display(G_START);
    ui->lineEdit_24->setText(QString::number(db.getSampleCount(g_current_index)));
    ui->lineEdit_25->setText(QString::number(db.getKBCount(g_current_index)));
    ui->lineEdit_26->setText(QString::number(db.getCaCount(g_current_index)));
    ui->lineEdit_27->setText(QString::number(db.getQuCount(g_current_index)));
    ui->lineEdit_28->setText(QString::number(db.getNormalCount(g_current_index)));


}

void MainWindow::on_srreturnbtn_clicked()
{
    //register return button
    //display(G_HOME);

}




void MainWindow::on_srtabWidget_currentChanged(int index)
{
    if(index==0)
    {
        ui->tab->initstate();
    }
    else if(1==index)
    {
        ui->tab_2->initstate();
    }
    else
        ui->tab_3->initstate();
}

void MainWindow::on_toolButton_13_clicked()
{
    ::CloseDlg  dl;
    int i=dl.exec();
    if(QDialog::Rejected==i)
    {
        this->close();
    }
    if(QDialog::Accepted==i)
    {
        //washing machine cup or other
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    display(G_WARN);
}

void MainWindow::on_pushButton_6_clicked()
{

}






void MainWindow::on_pushButton_6_toggled(bool checked)
{

}

/**************************************************
 * import test item from ram_sr to sr
 * push sr to g_test_array rearrange  start
 *
 *
 * ***************************************************/

void MainWindow::on_pushButton_15_clicked()
{
    //start test

}

void MainWindow::on_pushButton_16_clicked()
{
    display(G_WARN);
}

void MainWindow::on_pushButton_13_clicked()
{
    display(G_WARN);
}
//stop sample button
void MainWindow::on_toolButton_9_clicked()
{

    QMessageBox::StandardButton sb=QMessageBox::information(NULL, "注意", QString("是否停止采样?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(sb==QMessageBox::Yes)
    {
        g_handler.stop=1;
    }
}

void MainWindow::display_blank()
{
    display(G_WARN);
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


#include <QPixmap>

void MainWindow::on_toolButton_14_clicked()
{
    //QMessageBox::information(0,QString("关于"),"水质分析仪\n版本：1.0\nCopyright 2018-2020");
    QMessageBox box(QMessageBox::Information,"关于","水质分析仪\n\n\n版本：1.0\n\nCopyright 2018-2020 The Skysoft Company Ltd. All rights reserved.");
    box.setStandardButtons (QMessageBox::Ok);
    //box.setStandardButtons ();
    QPixmap g_pm(":/ico/app.ico");
    box.setIconPixmap(g_pm);
    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.exec();
}


/**********************************
 * convert rawsr to temp sr so
 * that to get ready for starting test
 * ***************************/
void MainWindow::fromRawtoSr()
{
    //getSr getCa getQu so that to compose sr
}

void MainWindow::displayHome()
{
    display(G_HOME);
}

void MainWindow::on_toolButton_10_clicked()
{
    //stop
    QMessageBox box(QMessageBox::Information,"提示","是否停止测试?");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    //box.setStandardButtons ();

    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.setButtonText (QMessageBox::Cancel,QString("取 消"));

    if(QMessageBox::Ok==box.exec ())
    {
        ::g_handler.command=0;
    }
}

void MainWindow::on_toolButton_12_clicked()
{
    //warning
    display_blank();
}

void MainWindow::on_warn_back_btn_clicked()
{
    displayHome();
}
