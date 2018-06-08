#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QPushButton>

class ItemButton : public QPushButton
{
    Q_OBJECT
public:
    int testid;
    explicit ItemButton(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // ITEMBUTTON_H
