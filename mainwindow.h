#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include "cabutton.h"

#include <QDateTime>
#include "dbinterface.h"
#include <QFrame>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}


enum GUIFrame{
    G_WARN,
    G_HOME,
    G_REGISTER,
    G_ITEM,
    G_START,
    G_STATUS,
    G_CACURVE,
    G_QUFRAME,
    G_WEIHU,
    G_SYSTEM,
    G_SAMPLE,
    G_NUM

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initsignal();
    void closeEvent(QCloseEvent *e);

private slots:
    void on_toolButton_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_8_clicked();

    void on_srreturnbtn_clicked();



    //void on_pushButton_11_clicked();

    void on_srtabWidget_currentChanged(int index);

    void on_toolButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_6_clicked();



    void on_pushButton_6_toggled(bool checked);


    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_13_clicked();

    void on_toolButton_9_clicked();

    void display_blank();

    void on_toolButton_11_clicked();

    void on_MainWindow_destroyed();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_7_clicked();



    void on_toolButton_14_clicked();

    //void slot1(int index);

    void displayHome();
    void on_toolButton_10_clicked();

    void on_toolButton_12_clicked();

    void on_warn_back_btn_clicked();

private:
    Ui::MainWindow *ui;


    QFrame *pf[G_NUM];
    QToolButton *ptb[G_NUM];
    void initGUI();
    void initFrames();

    void display(GUIFrame frame);
    void warnInittable();

    void fromRawtoSr();
};
#define IB_LENGTH 50
//extern MainWindow *g_w;
extern QString g_current_index;
extern int g_item_num;
#endif // MAINWINDOW_H
