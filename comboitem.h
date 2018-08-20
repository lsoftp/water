#ifndef COMBOITEM_H
#define COMBOITEM_H

#include <QDialog>

namespace Ui {
class ComBoItem;
}

class ComBoItem : public QDialog
{
    Q_OBJECT

public:
    explicit ComBoItem(QWidget *parent = 0);
    ~ComBoItem();

private:
    Ui::ComBoItem *ui;
};

#endif // COMBOITEM_H
