#include "catab.h"
#include "ui_catab.h"
#include "mainwindow.h"

CaTab::CaTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaTab)
{
    ui->setupUi(this);
    initcabutton();
    setbutton();
    showpage(0);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //一次选择一行
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);

    QHeaderView *header = ui->tableWidget_2->verticalHeader();
    header->setHidden(true);// 隐藏行号
    ui->tableWidget_2->setColumnWidth(0,60);
    ui->tableWidget_2->setColumnWidth(1,30);
    QRegExp regx("^C[1-9][0-9]*$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit_7 );
    ui->lineEdit_7->setValidator(validator);
    updateCayelist();
    initstate();
}

CaTab::~CaTab()
{
    delete ui;
}

void CaTab::init()
{
    connect(ui->careturnbtn, SIGNAL(clicked()),g_w,SLOT(on_srreturnbtn_clicked()));
}

void CaTab::initcabutton()
{
    QWidget *qw=ui->frame_5;
    //qdeleteLater();

    for(int i=0;i<11;i++)
    {
        pb1[i]= new CaButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb1[i]= new CaButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb1[i]= new CaButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb1[i]= new CaButton(qw);
        pb1[i]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }
    qw=ui->frame_6;
    //qdeleteLater();

    for(int i=0;i<11;i++)
    {
        pb1[i+38]= new CaButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*i,0,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<10;j++)
    {
        int i=j+11;
        pb1[i+38]= new CaButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH/2,IB_LENGTH,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<9;j++)
    {
        int i=j+21;
        pb1[i+38]= new CaButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH,IB_LENGTH*2,IB_LENGTH,IB_LENGTH);
    }
    for(int j=0;j<8;j++)
    {
        int i=j+30;
        pb1[i+38]= new CaButton(qw);
        pb1[i+38]->setGeometry(IB_LENGTH*j+IB_LENGTH*3/2,IB_LENGTH*3,IB_LENGTH,IB_LENGTH);
    }

}

void CaTab::setbutton()
{
    QSqlQueryModel sqm;
    db.getTestItem(sqm);
    g_item_num=sqm.rowCount();
    for(int i=0;i<sqm.rowCount();i++)

    {

        QString name=sqm.record(i).value("Name").toString();
        int   testid=sqm.record(i).value("TestId").toInt();

        pb1[i]->setText(name);
        pb1[i]->testid=testid;

        pb1[i]->setEnabled(true);
        //pb1[i]->setCheckable(true);
        connect(pb1[i],SIGNAL(clicked()),this,SLOT(ontoggle()));
    }

}

void CaTab::showpage(int i)
{
    if(!i) {
        ui->frame_5->show();
        ui->frame_6->hide();
    }
    else
    {
        ui->frame_5->hide();
        ui->frame_6->show();

    }
}
void CaTab::on_comboBox_7_currentIndexChanged(int index)
{
    showpage(index);
}

void CaTab::updateCayelist()
{
    QSqlQueryModel sqm;
    db.getCaye(sqm);
    ui->comboBox_5->clear();
    for(int i=0; i<sqm.rowCount();i++)
    {

        ui->comboBox_5->addItem(sqm.record(i).value("name").toString());
    }
}

void CaTab::reg()
{
    if(!isValid())
    {
        QMessageBox::information(0,"错误","请输入正确的样本号！");
        return;
    }
    TestRegister t;
    QDateTime now=QDateTime::currentDateTime();

    //t.tr.test_row_id=QDateTime::currentDateTime().toString()
    t.no=ui->lineEdit_7->text();
    t.id=t.no.right(t.no.size()-1).toInt();
    t.sampleid="";
    //t.pre_dilute=ui->checkBox->isChecked();
    //t.pre_d_times=ui->lineEdit_5->text().toInt();
    t.tr.position=ui->comboBox_11->currentText().toInt();
    t.tr.sample_cup_type=ui->comboBox_6->currentIndex();
    //t.tr.priority=!(ui->checkBox_2->isChecked());
    t.tr.test_type=1; //to be determined
    t.qname="";
    t.cname=ui->comboBox_5->currentText();
    t.tr.isdilute=0;
    t.tr.status=0;
    //t.combinetestname="";
    //初始化  g_current_index 在全局变量中
    //还有test_row_id ,isreplace, test_id

    db.delCabyid(g_current_index,t.no);
    int j=0;
    for(int i=0;i<g_item_num;i++)
    {
        if(this->pb1[i]->state!=0)
        {
            //insert
            QString tempid =now.toString("yyyyMMddhhmmsszzz")+QString("%1").arg(j,3,10,QChar('0'));
            //if test_id isreplace add two rows
            t.tr.test_type=pb1[i]->state;
            t.tr.test_row_id=tempid.toStdString();
            t.tr.isreplace=0;
            t.tr.test_id=pb1[i]->testid;
            db.insertSample(t);
            j++;
            //            if(gi::isReplace(pb[i]->testid))
            //            {
            //                tempid =now.toString("yyyyMMddhhmmss")+QString("%1").arg(j,3,10,QChar('0'));
            //                t.tr.isreplace=1;
            //                db.insertSample(t);
            //                j++;
            //            }

            //
        }
    }

}

bool CaTab::isValid()
{
    const QValidator* v=ui->lineEdit_7->validator();
    int i;
    QString s=ui->lineEdit_7->text();
    if(QValidator::Acceptable==v->validate(s,i))
    {
        //v->validate(s,i);
        //QMessageBox::information(0,QString::number(i),QString::number(v->validate(s,i)));
        return true;
    }
    else
    {
        return false;
    }


}

int  CaTab::getfreeNo()
{
    QSqlQueryModel sqm;
    db.getCaNo(sqm, g_current_index);

    int j=0,num=sqm.rowCount();
    if(num==0)
    {

        return 1;
    }
    for(int i=0;i<num;i++)
    {
        int k=sqm.record(i).value("id").toInt();
        int p=k-j;

        if(p>1)
        {

            return j+1;
        }
        j=k;
    }
    return j+1;
}

void CaTab::SetPos()
{
    ui->comboBox_11->clear();
    QSqlQueryModel sqm;
    db.getPos(sqm, g_current_index);
    for(int i=0;i<40;i++)
    {
        ui->comboBox_11->addItem(QString::number(i+1));
    }
    for(int j=0;j<sqm.rowCount();j++)
    {
        QString num=sqm.record(j).value("pos").toString();
        int index=ui->comboBox_11->findText(num);
        if(index!=-1)
        {
            ui->comboBox_11->removeItem(index);
        }
    }
    ui->comboBox_11->setCurrentIndex(0);
    //ui->comboBox_2->currentData()

}

void CaTab::clearBtn()
{
    for(int i=0;i<g_item_num;i++)
    {
        pb1[i]->setState(0);
    }
}

void CaTab::refreshtable()
{
    QSqlQueryModel sqm;
    db.getCa(sqm,::g_current_index);
    QTableWidget *tw=ui->tableWidget_2;
    tw->clearContents();
    tw->setRowCount(sqm.rowCount()+1);
    for(int i=0;i<sqm.rowCount();i++)
    {
        QString ts=sqm.record(i).value("id").toString();
        tw->setItem(i,0,new QTableWidgetItem(QString("C%1").arg(ts)));
        tw->setItem(i,1,new QTableWidgetItem(sqm.record(i).value("Pos").toString()));
        tw->setItem(i,2,new QTableWidgetItem(sqm.record(i).value("Caname").toString()));
        int k = sqm.record(i).value("Stage").toInt();
        QString status= k==0?"已登记":"其他";
        tw->setItem(i,3,new QTableWidgetItem(status));

    }
    int c=sqm.rowCount();
    tw->setItem(c,0,new QTableWidgetItem(QString("*C%1").arg(getfreeNo())));
    tw->setItem(c,3,new QTableWidgetItem("新"));
    tw->selectRow(c);

}

void CaTab::readytoaddnew()
{
    //page 1
    ui->comboBox_7->setCurrentIndex(0);


    showpage(0);

    this->clearBtn();
    //this->SetSampleNo();

    SetPos();
    //this->refreshtable();
    //ui->checkBox->setChecked(false);
    //ui->lineEdit_5->setText("");
    //ui->lineEdit_6->setText("");
    //ui->checkBox_2->setChecked(false);
    ui->comboBox_6->setCurrentIndex(0);
    //ui->lineEdit_6->setText("");
    ui->sr_yes->setEnabled(false);

}
void CaTab::on_tableWidget_2_itemSelectionChanged()
{

    QList<QTableWidgetItem*> items=ui->tableWidget_2->selectedItems();
    if(items.size()==0) return;
    QString no=items.at(0)->text();
    if(no.startsWith("*"))
    {
        //no="123456";
        no=no.right(no.size()-1);

    }
    ui->lineEdit_7->setText(no);
    QSqlQueryModel sqm;
    db.getCabyid(sqm,::g_current_index,no);
    //    SetPos();
    //    ui->comboBox_2->insertItem(0,no);
    //    ui->comboBox_2->setCurrentIndex(0);
    clearBtn();
    int num=sqm.rowCount();
    if (num==0)
    {
        readytoaddnew();
    }
    else
    {
        for(int i=0;i<sqm.rowCount();i++)
        {
            int position=sqm.record(i).value("Pos").toInt();
            int isP=sqm.record(i).value("isPredilute").toInt();
            int pdt=sqm.record(i).value("Predilutetimes").toInt();
            QString sid=sqm.record(i).value("sampleid").toString();
            int isu=sqm.record(i).value("Isurgent").toInt();
            int sct=sqm.record(i).value("samplecuptype").toInt();
            int tid=sqm.record(i).value("TestID").toInt();
            int tt=sqm.record(i).value("Testtype").toInt();
            QString cname=sqm.record(i).value("Caname").toString();
            if(i==0)
            {
                SetPos();
                int ppp=ui->comboBox_5->findText(cname);
                ui->comboBox_5->setCurrentIndex(ppp);
                ui->comboBox_11->insertItem(0,QString::number(position));
                ui->comboBox_11->setCurrentIndex(0);

                //ui->checkBox->setChecked(isP!=0);
                //ui->lineEdit_5->setText(QString::number(pdt));
                //ui->lineEdit_6->setText(sid);
                //ui->checkBox_2->setChecked(isu==0);
                ui->comboBox_6->setCurrentIndex(sct);

            }
            for(int j=0;j<g_item_num;j++)
            {
                if(pb1[j]->testid==tid)
                {
                    pb1[j]->setState(tt);
                    break;
                }
            }

        }
        //else ;
        ui->sr_yes->setEnabled(false);
    }
}

void CaTab::on_sr_yes_clicked()
{
    reg();
    initstate();
}

void CaTab::initstate()
{
    //page 1
    ui->comboBox_7->setCurrentIndex(0);
    //不可编辑


    showpage(0);

    this->clearBtn();


    this->refreshtable();
    SetPos();

    ui->lineEdit_7->setText(QString("C%1").arg(getfreeNo()));
    ui->sr_yes->setEnabled(false);
}

void CaTab::on_comboBox_5_currentIndexChanged(int index)
{
    ui->sr_yes->setEnabled(true);
}

void CaTab::on_comboBox_11_currentIndexChanged(int index)
{
    ui->sr_yes->setEnabled(true);
}

void CaTab::on_comboBox_6_currentIndexChanged(int index)
{
    ui->sr_yes->setEnabled(true);
}

void CaTab::ontoggle()
{
    ui->sr_yes->setEnabled(true);
}

void CaTab::on_lineEdit_7_textChanged(const QString &arg1)
{
    int num=ui->tableWidget_2->rowCount();
    for(int i=0;i<num;i++)
    {
        if(ui->tableWidget_2->item(i,0)->text()==ui->lineEdit_7->text())
        {
            ui->tableWidget_2->selectRow(i);
            return ;
        }
    }
    if(arg1!="")
    {
        ui->tableWidget_2->item(num-1,0)->setText(QString("*%1").arg(arg1));

        ui->tableWidget_2->selectRow(num-1);
    }
    else
    {
        ui->tableWidget_2->item(num-1,0)->setText(QString("*C%1").arg(getfreeNo()));

        //ui->tableWidget_2->selectRow(num-1);

    }
}

void CaTab::on_sr_del_clicked()
{
    QMessageBox box(QMessageBox::Information,"提示","是否删除?");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    //box.setStandardButtons ();
    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.setButtonText (QMessageBox::Cancel,QString("取 消"));

    if(QMessageBox::Ok==box.exec ())
    {
        QList<QTableWidgetItem*> items=ui->tableWidget_2->selectedItems();
        if(items.size()==0) return;
        QString no=items.at(0)->text();
        db.delCabyid(::g_current_index,no);
        refreshtable();
    }

}
