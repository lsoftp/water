#include "samplestatuswidget.h"
#include <qpainter.h>

const Qt::GlobalColor SampleStatusWidget::scolor[STATE_NUM]={Qt::white,Qt::green,Qt::magenta,Qt::black};

SampleStatusWidget::SampleStatusWidget(QWidget *parent) : QWidget(parent)
{

}

void SampleStatusWidget::paintEvent(QPaintEvent *e)
{
    R=width()/2-10;
    r0=width();
    r1=height();
    m_center.setX(width()/2);
    m_center.setY(height()/2);
    QPainter paint;
    paint.begin(this);


        paint.setPen(QPen(Qt::black,1,Qt::SolidLine));
    paint.drawEllipse(m_center,R,R);
        //paint.drawEllipse(0,0,50,60);
    paint.end();
}
