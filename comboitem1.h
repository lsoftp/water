#ifndef COMBOITEM1_H
#define COMBOITEM1_H

#include <QDialog>

namespace Ui {
class ComboItem1;
}

class ComboItem1 : public QDialog
{
    Q_OBJECT

public:
    explicit ComboItem1(QWidget *parent = 0);
    ~ComboItem1();

private:
    Ui::ComboItem1 *ui;
};

#endif // COMBOITEM1_H
