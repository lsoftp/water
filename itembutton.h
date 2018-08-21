#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QPushButton>
#include <QList>
class ItemButton : public QPushButton
{
    Q_OBJECT
public:
    int type;
    int testid;
    QList<int> tidlist;
    explicit ItemButton(QWidget *parent = nullptr);

signals:
    void combo_toggle(bool,const QList<int>&);
public slots:
private slots:
    void on_toggled(bool b);
};

#endif // ITEMBUTTON_H
