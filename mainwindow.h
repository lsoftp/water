#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "itembutton.h"
#include "cabutton.h"
#include "samplebutton.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_5_clicked();

private:
    Ui::MainWindow *ui;
    ItemButton *pb[38];
    CaButton *pb1[38];

    void initcabutton();
};

#endif // MAINWINDOW_H
