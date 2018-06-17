#include "cabutton.h"

CaButton::CaButton(QWidget *parent) : QPushButton(parent)
{
    testid=-1;
    type=0;
    state=0;
    setStyleSheet("background-color: rgb(170, 170, 255);");
    setEnabled(false);
    connect(this,SIGNAL(clicked(bool)),this,SLOT(setState()));
}

void CaButton::setState(int s)
{
    //state=s;
    if(s==1)
    {
        state=1;
        this->setStyleSheet("background-color: rgb(85, 255, 0);");
        return;
    }
    if(s==2)
    {
        state=2;
        this->setStyleSheet("background-color:  rgb(255, 255, 0);");
        return;
    }
    if(s==0)
    {
        state=0;
        setStyleSheet("background-color: rgb(170, 170, 255);");
        return;
    }


}

void CaButton::setState()
{
    if(!type)
    {
        if(state==0)
        {
            state=1;
            this->setStyleSheet("background-color: rgb(85, 255, 0);");
            return;
        }
        if(state==1)
        {
            state=2;
            this->setStyleSheet("background-color:  rgb(255, 255, 0);");
            return;
        }
        if(state==2)
        {
            state=0;
            setStyleSheet("background-color: rgb(170, 170, 255);");
            return;
        }
    }
    if(type==1)
    {
        if(state==0)
        {
            state=2;
            this->setStyleSheet("background-color:  rgb(255, 255, 0);");
            return;
        }
        if(state==2)
        {
            state=0;
            setStyleSheet("background-color: rgb(170, 170, 255);");
            return;
        }

    }
}
