#ifndef SYSTEMFRAME_H
#define SYSTEMFRAME_H

#include <QFrame>
#include <QMessageBox>
#include "dbinterface.h"
namespace Ui {
class SystemFrame;
}

class SystemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SystemFrame(QWidget *parent = 0);
    ~SystemFrame();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_tableWidget_2_itemSelectionChanged();
    void on_careturnbtn_clicked();
    void on_tabWidget_currentChanged(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_singlebtn_toggled(bool checked);

    void on_doublebtn_toggled(bool checked);

    void on_return_btn_clicked();

    void on_careturnbtn_2_clicked();

    void on_careturnbtn_3_clicked();

    void on_careturnbtn_4_clicked();

    void on_return_btn_2_clicked();

    void on_tableWidget_7_cellDoubleClicked(int row, int column);

    void on_tableWidget_itemSelectionChanged();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

signals:
    void back();
private:
    Ui::SystemFrame *ui;
    bool ifSelectCa(bool b=false);
    QString selCaname;
    QString selTestname;
    QString selOrdername;
    bool ifSelectTest();
    void refreshtable();
    void refreshtable1(QString sel);
    void refreshItemOrderTable();
    int ifSelectItemOrder(bool b);
    void init_item_order();
    void init_dict();
    void init_serial_port_list();
    void Calcu_init();
    void caluItem_refresh_table();
    void cacuItem_selectrow(int row);
    void caluItem_new();
    void caluItem_save();
    void caluItem_del();


    void calcuItem_load(CalcuItem &ci);
    bool calcuItem_ifSelectCa();
};

#endif // SYSTEMFRAME_H
