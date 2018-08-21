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
    QString item;
    int testid;
    explicit ComboItem1(QWidget *parent = 0);
    explicit ComboItem1(QString name);
    ~ComboItem1();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ComboItem1 *ui;
    void initTestList();
};

#endif // COMBOITEM1_H
