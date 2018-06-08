#include "itembutton.h"

ItemButton::ItemButton(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet("selection-color: rgb(0, 255, 255); \
                  background-color: rgb(170, 170, 255);");
    setCheckable(true);
    testid=-1;
}
