#ifndef CATAB_H
#define CATAB_H

#include <QWidget>
#include <mainwindow.h>
#include "cabutton.h"
namespace Ui {
class CaTab;
}

class CaTab : public QWidget
{
    Q_OBJECT

public:
    explicit CaTab(QWidget *parent = 0);
    ~CaTab();
    void initstate();
    void init();
public slots:
    void ontoggle();
private slots:
    void on_comboBox_7_currentIndexChanged(int index);

    void updateCayelist();
    //void on_tableWidget_2_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_tableWidget_2_itemSelectionChanged();

    void on_sr_yes_clicked();

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_11_currentIndexChanged(int index);

    void on_comboBox_6_currentIndexChanged(int index);

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_sr_del_clicked();

private:
    Ui::CaTab *ui;
    CaButton *pb1[38*2];
    void initcabutton();//初始化定标定标按钮
    void setbutton();
    void showpage(int i);
    void reg();
    bool isValid();
    int getfreeNo();
    void SetPos();
    void clearBtn();
    void refreshtable();

    void readytoaddnew();
};

#endif // CATAB_H
