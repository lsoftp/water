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

    void init();
private slots:
    void on_comboBox_7_currentIndexChanged(int index);

private:
    Ui::QuTab *ui;
    void initcabutton();
    void setbutton();
    void showpage(int i);
    ItemButton *pb1[38*2];
};

#endif // QUTAB_H
