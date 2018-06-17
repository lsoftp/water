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

private:
    Ui::SrTab *ui;
    ItemButton *pb[38*2];
    void initsabutton();//初始化样本登记按钮
    void SetSampleNo();
    void SetPos();

    void setYesEnable(bool b);

    void setbutton();
    void showpage(int i);

    void uncheckbt();
    void refreshtable();
    void reg();
};

#endif // SRTAB_H
