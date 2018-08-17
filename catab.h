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

    void init();
private slots:
    void on_comboBox_7_currentIndexChanged(int index);

    void updateCayelist();
private:
    Ui::CaTab *ui;
    CaButton *pb1[38*2];
    void initcabutton();//初始化定标定标按钮
    void setbutton();
    void showpage(int i);
    void reg();
    bool isValid();
};

#endif // CATAB_H
