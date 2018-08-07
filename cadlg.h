#ifndef CADLG_H
#define CADLG_H

#include <QDialog>

namespace Ui {
class CaDlg;
}

class CaDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CaDlg(QWidget *parent = 0);
    explicit CaDlg(QString a,QString b,QString c);
    ~CaDlg();
    QString name;
    QString no;
    QString valid;



private slots:
    void on_pushButton_clicked();

private:
    Ui::CaDlg *ui;
};

#endif // CADLG_H
