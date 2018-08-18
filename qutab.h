#ifndef QUTAB_H
#define QUTAB_H

#include <QWidget>
#include "mainwindow.h"
#include "itembutton.h"

namespace Ui {
class QuTab;
}

class QuTab : public QWidget
{
    Q_OBJECT

public:
    explicit QuTab(QWidget *parent = 0);
    ~QuTab();
    void initstate();

    void init();
public slots:
    void ontoggle();
private slots:
    void on_comboBox_7_currentIndexChanged(int index);
    void updatezhikongyelist();
    void on_sr_yes_clicked();

    void on_sr_del_clicked();

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_11_currentIndexChanged(int index);

    void on_comboBox_6_currentIndexChanged(int index);

    void on_tableWidget_2_itemSelectionChanged();

    void on_lineEdit_7_textChanged(const QString &arg1);

private:
    Ui::QuTab *ui;
    void initcabutton();
    void setbutton();
    void showpage(int i);
    ItemButton *pb1[38*2];

    void reg();
    bool isValid();
    int getfreeNo();
    void SetPos();
    void clearBtn();
    void refreshtable();
    void readytoaddnew();
};

#endif // QUTAB_H
