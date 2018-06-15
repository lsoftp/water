#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class StopSDia : public QDialog
{
    Q_OBJECT

public:
    explicit StopSDia(QWidget *parent = 0);
    ~StopSDia();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
