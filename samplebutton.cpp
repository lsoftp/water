#include "samplebutton.h"
#include <QPainter>
#include <QPen>
SampleButton::SampleButton(QWidget *parent) : QPushButton(parent)
{
    f=0;
}

void SampleButton::paintEvent(QPaintEvent *)
{
    QPainter paint;
    paint.begin(this);
    if(f==0)
    {
        paint.setPen(QPen(Qt::blue,4,Qt::SolidLine));
    }
    else
    {
        paint.setPen(QPen(Qt::white,4,Qt::SolidLine));
    }
        paint.drawEllipse(0,0,50,60);
    paint.end();
}

void SampleButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        //m_bLeftDown=true;
        repaint();
    }
    QPushButton::mousePressEvent(e);
}

void SampleButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        //m_bLeftDown=false;
        repaint();
    }
    QPushButton::mouseReleaseEvent(e);
}

void SampleButton::focusInEvent(QFocusEvent *e)
{
       QPalette p=QPalette();
       p.setColor(QPalette::Base,Qt::green);    //QPalette::Base 对可编辑输入框有效，还有其他类型，具体的查看文档
       setPalette(p);
       f=1;
}

void SampleButton::focusOutEvent(QFocusEvent *e)
{
       QPalette p1=QPalette();
       p1.setColor(QPalette::Base,Qt::white);
       setPalette(p1);
       f=0;
}
