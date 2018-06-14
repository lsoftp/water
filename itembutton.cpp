#include "itembutton.h"
#include "mainwindow.h"
ItemButton::ItemButton(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet("selection-color: rgb(0, 255, 255); \
                  background-color: rgb(170, 170, 255);");
    setCheckable(false);
    setEnabled(false);
    testid=-1;
    //connect(this,SIGNAL(toggled(bool)),g_w,SLOT(on_pushButton_6_toggled(bool)));
}
