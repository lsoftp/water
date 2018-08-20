#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class CloseDlg : public QDialog
{
    Q_OBJECT

public:
    int i;
    explicit CloseDlg(QWidget *parent = 0);
    ~CloseDlg();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
