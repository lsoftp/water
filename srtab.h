//样本登记页面
#ifndef SRTAB_H
#define SRTAB_H

#include <QWidget>
#include "itembutton.h"
namespace Ui {
class SrTab;
}

class SrTab : public QWidget
{
    Q_OBJECT

public:
    explicit SrTab(QWidget *parent = 0);
    ~SrTab();
    void initstate();
private slots:
    void on_comboBox_4_currentIndexChanged(int index);
    void ontoggle(bool b);
    void on_sr_yes_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_checkBox_toggled(bool checked);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_checkBox_2_toggled(bool checked);

    void on_comboBox_3_currentIndexChanged(int index);



    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_sr_del_clicked();

    void on_lineEdit_4_editingFinished();

    void on_srreturnbtn_clicked();

    void updateComboBtn();
    void on_Combo_toggled(bool b, const QList<int> &tl);
private:
    Ui::SrTab *ui;
    ItemButton *pb[38*2];   //测试项目按钮
    ItemButton *cpb[11*2]; //组合项目按钮
    void initsabutton();//初始化样本登记按钮
    void SetSampleNo();
    void SetPos();

    void setYesEnable(bool b);

    void setbutton();
    void showpage(int i);

    void uncheckbt();
    void refreshtable();
    void reg();
    int getfreeNo();
    void readytoaddnew();
    bool isValid();
signals:
    void back();
};

#endif // SRTAB_H
