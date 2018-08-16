#ifndef CAQUDLG_H
#define CAQUDLG_H

#include <QDialog>
#include "dbinterface.h"

namespace Ui {
class CaQuDlg;
}

class CaQuDlg : public QDialog
{
    Q_OBJECT

public:
    QString testname;
    QString con;
    QString unit;
    explicit CaQuDlg(QWidget *parent = 0);
    explicit CaQuDlg(QString a,QString b,QString c);
    ~CaQuDlg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CaQuDlg *ui;

    void initTestList();
};

#endif // CAQUDLG_H
