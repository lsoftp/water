#ifndef QUDLG_H
#define QUDLG_H

#include <QDialog>

namespace Ui {
class QuDlg;
}

class QuDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QuDlg(QWidget *parent = 0);
    ~QuDlg();
    explicit QuDlg(QString a,QString b,QString c);
    QString name;
    QString no;
    QString valid;

private slots:
    void on_pushButton_clicked();

private:
    Ui::QuDlg *ui;

};

#endif // QUDLG_H
