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
    QString name;
    explicit ComBoItem(QWidget *parent = 0);
    explicit ComBoItem(QString n);
    ~ComBoItem();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ComBoItem *ui;
};

#endif // COMBOITEM_H
