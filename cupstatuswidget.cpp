#include "cupstatuswidget.h"
#include <QStyleOption>
#define MY_PI 3.14159265358979323846
#define MY_PI_SPAN MY_PI/180
const QColor CupStatusWidget::scolor[S_NUM]={QColor(Qt::green),QColor(Qt::red),QColor(Qt::white)};
CupStatusWidget::CupStatusWidget(QWidget *parent) : QWidget(parent)
{
    current=-1;
    for(int i=0;i<rnum;i++)
    {
        m_status[i]=S_IDLE;
    }
}


void CupStatusWidget::paintEvent(QPaintEvent *e)
{
    R=width()/2-6;
    R1=R-60;
    R2=R-100;

//    r00=R2+6;
//    r01=R1-6;
    r00=R1+6;
    r01=R-6;

    cr1=r00+(r01-r00)*2/3;
    //cr1=r10+(r11-r10)*4/7;
    //lr=getR(cr);
    m_center.setX(width()/2);
    m_center.setY(height()/2);

    QStyleOption o;
    o.initFrom(this);
    QPainter paint;

    paint.begin(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &paint, this);
    paint.setRenderHint(QPainter::Antialiasing);
    paint.setPen(QPen(Qt::black,1,Qt::SolidLine));

    paint.drawEllipse(m_center,R,R);
    paint.drawEllipse(m_center,R1,R1);

    // paint.drawEllipse(m_center,R-20,R-20);
    for(int i=0;i<rnum;i++)
    {
        drawRect(paint,i,Qt::black,scolor[m_status[i]]);

    }
    if(current!=-1)
    {
                drawRect(paint,current,Qt::white,Qt::green,false);

    }
    paint.end();
    //QWidget::paintEvent(e);

}


void CupStatusWidget::drawRect(QPainter &pa, int i, QColor c, QColor fillcolor,bool isfill)
{
    QPoint cp,cp1,cp2,cp3;
    QPainterPath pp;
    pa.setPen(QPen(c,1,Qt::SolidLine));
    if(!isfill) pa.setPen(QPen(c,2,Qt::SolidLine));
    cp.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r00);
    cp.setY(m_center.y()-qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r00);
    cp1.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r00);
    cp1.setY(m_center.y()-qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r00);
    cp2.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r01);
    cp2.setY(m_center.y()-qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r01);
    cp3.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r01);
    cp3.setY(m_center.y()-qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r01);
//    pa.drawLine(cp,cp1);
//    pa.drawLine(cp1,cp3);
//    pa.drawLine(cp3,cp2);
//    pa.drawLine(cp,cp2);
    pp.moveTo(cp.x(),cp.y());
    pp.lineTo(cp1.x(),cp1.y());
    pp.lineTo(cp3.x(),cp3.y());
    pp.lineTo(cp2.x(),cp2.y());
    pp.lineTo(cp.x(),cp.y());
    pa.drawPath(pp);
    QRect re;
    cp.setX(m_center.x()+qCos(MY_PI/rnum*(i+i+1))*cr1);
    cp.setY(m_center.y()-qSin(MY_PI/rnum*(i+i+1))*cr1);

    re.setLeft(cp.x()-6);
    re.setTop(cp.y()-4);
    re.setWidth(12);
    re.setHeight(8);

    if(isfill) pa.fillPath(pp,QBrush(fillcolor));
    pa.setPen(QPen(Qt::black,1,Qt::SolidLine));
    pa.drawText(re,Qt::AlignCenter,QString::number(i+1));

}

void CupStatusWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {

        //QPoint p=e->globalPos() - frameGeometry().topLeft();
        QPoint p1=e->pos();
        for(int i=0;i<rnum; i++)
        {
            QPoint cp,cp1,cp2,cp3;
            QPainterPath pp;

            cp.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r00);
            cp.setY(m_center.y()-qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r00);
            cp1.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r00);
            cp1.setY(m_center.y()-qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r00);
            cp2.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r01);
            cp2.setY(m_center.y()-qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r01);
            cp3.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r01);
            cp3.setY(m_center.y()-qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r01);
        //    pa.drawLine(cp,cp1);
        //    pa.drawLine(cp1,cp3);
        //    pa.drawLine(cp3,cp2);
        //    pa.drawLine(cp,cp2);
            pp.moveTo(cp.x(),cp.y());
            pp.lineTo(cp1.x(),cp1.y());
            pp.lineTo(cp3.x(),cp3.y());
            pp.lineTo(cp2.x(),cp2.y());
            pp.lineTo(cp.x(),cp.y());
            if( pp.contains(p1))
            {
                current=i;
                cur_cir=0;
                this->update();
                return ;
            }
        }

        //e->accept();
    }


}
