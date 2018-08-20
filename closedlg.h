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
    explicit CloseDlg(QWidget *parent = 0);
    ~CloseDlg();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
