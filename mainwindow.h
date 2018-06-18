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


enum GUIFrame{
    G_BLANK,
    G_HOME,
    G_REGISTER,
    G_ITEM,
    G_START,
    G_STATUS,
    G_NUM

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initsignal();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_8_clicked();

    void on_pushButton_9_clicked();



    //void on_pushButton_11_clicked();

    void on_tabWidget_currentChanged(int index);

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

private:
    Ui::MainWindow *ui;


    QFrame *pf[G_NUM];
    void initGUI();
    void initFrames();

    void display(GUIFrame frame);


};
#define IB_LENGTH 50
extern MainWindow *g_w;
extern QString g_current_index;
extern int g_item_num;
#endif // MAINWINDOW_H
