#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "itembutton.h"
#include "cabutton.h"
#include "samplebutton.h"
#include <QDateTime>
#include "dbinterface.h"
#include <QFrame>
namespace Ui {
class MainWindow;
}

class SampleRegister;
enum GUIFrame{
    G_BLANK,
    G_HOME,
    G_REGISTER,
    G_ITEM,
    G_START,
    G_NUM

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    friend class SampleRegister;
    SampleRegister *sr;
private slots:
    void on_toolButton_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    //void on_pushButton_11_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_toolButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_4_currentIndexChanged(int index);

    void on_sr_del_clicked();

    void ontoggle(bool b);
    void on_pushButton_6_toggled(bool checked);

    void on_sr_yes_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_13_clicked();

    void on_toolButton_9_clicked();

private:
    Ui::MainWindow *ui;

    int itemnum;
    ItemButton *pb[38*2];
    CaButton *pb1[38*2];
    ItemButton *pb2[38*2];
    QFrame *pf[G_NUM];
    void initGUI();
    void initFrames();
    void initsabutton();//初始化样本登记按钮
    void initcabutton();//初始化定标定标按钮
    void initqubutton();//初始化质控安按钮
    void display(GUIFrame frame);


};
#define IB_LENGTH 50
extern MainWindow *g_w;
extern QString g_current_index;
#endif // MAINWINDOW_H
