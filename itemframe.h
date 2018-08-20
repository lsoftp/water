#ifndef ITEMFRAME_H
#define ITEMFRAME_H

#include <QFrame>
#include <QWidget>
#include "dbinterface.h"

namespace Ui {
class ItemFrame;
}

class ItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ItemFrame(QWidget *parent = 0);
    ~ItemFrame();
    void init();
    void setDbstatus(int s);

    void add();
    void load(Item &it);
    void refreshtable();
    void initCombo();
    int getfreeNo();
public slots:

private slots:
    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);
    void display_blank();


    void on_pushButton_2_clicked();

    void on_tableWidget1_itemSelectionChanged();

    void on_pushButton_4_clicked();

    void on_return_btn_clicked();

private:
    Ui::ItemFrame *ui;
    int dbstatus;
signals:
    void back();
};

#endif // ITEMFRAME_H
