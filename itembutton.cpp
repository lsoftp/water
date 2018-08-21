#include "itembutton.h"
#include "mainwindow.h"
ItemButton::ItemButton(QWidget *parent) : QPushButton(parent),type(0)
{
    setStyleSheet("QPushButton:checked{background-color: rgb(85, 255, 255);} \
                  QPushButton{background-color: rgb(170, 170, 255);}");
    setCheckable(false);
    setEnabled(false);
    testid=-1;
    connect(this,SIGNAL(toggled(bool)),this,SLOT(on_toggled(bool)));
}

void ItemButton::on_toggled(bool b)
{
    if(1==type)
        emit combo_toggle(b,tidlist);
}
