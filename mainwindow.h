#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "itembutton.h"
#include "cabutton.h"
#include "samplebutton.h"
#include <QDateTime>
#include "dbinterface.h"

namespace Ui {
class MainWindow;
}

class SampleRegister;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    friend class SampleRegister;
private slots:
    void on_toolButton_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_pushButton_11_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    SampleRegister *sr;
    ItemButton *pb[38];
    CaButton *pb1[38];
    ItemButton *pb2[38];

    void initGUI();
    void initsabutton();//初始化样本登记按钮
    void initcabutton();//初始化定标定标按钮
    void initqubutton();//初始化质控安按钮
    void setbutton(int i,ItemButton **p,QSqlQueryModel &sqm);

};
#define IB_LENGTH 50
#endif // MAINWINDOW_H
