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
    QString name;
    QString no;
    QString valid;

private:
    Ui::QuDlg *ui;
};

#endif // QUDLG_H
