#include "reagentstatuswidget.h"
#include <QStyleOption>
#define MY_PI 3.14159265358979323846
#define MY_PI_SPAN MY_PI/180
const QColor ReagentStatusWidget::scolor[S_NUM]={QColor(Qt::green),QColor(Qt::red),QColor(Qt::white)};
ReagentStatusWidget::ReagentStatusWidget(QWidget *parent) : QWidget(parent)
{
    current=-1;
    for(int i=0;i<rnum;i++)
    {
        m_status[i]=state(i%S_NUM);
    }
}

void ReagentStatusWidget::paintEvent(QPaintEvent *e)
{
    R=width()/2-6;
    R1=R-40;
    R2=R-100;

    r00=R2+6;
    r01=R1-6;
    r10=R1+6;
    r11=R-6;

    cr=r00+(r01-r00)*2/3;
    cr1=r10+(r11-r10)*4/7;
    lr=getR(cr);
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
    paint.drawEllipse(m_center,R2,R2);
    // paint.drawEllipse(m_center,R-20,R-20);
    for(int i=0;i<rnum;i++)
    {
        drawRect(paint,i,Qt::black);
        drawRect1(paint,i,Qt::black);
        drawCircle(paint,i,scolor[m_status[i]]);
        drawCircle1(paint,i,scolor[m_status[i]]);
    }
    if(current!=-1)
    {
        if(cur_cir==0)
            drawRect(paint,current,Qt::white,false);
        else
            drawRect1(paint,current,Qt::white,false);
    }
    paint.end();
    //QWidget::paintEvent(e);

}

void ReagentStatusWidget::drawCircle(QPainter &pa, int i, QColor c)
{
    QPoint cp;
    cp.setX(m_center.x()+qCos(MY_PI/rnum*(i+i+1))*cr);
    cp.setY(m_center.y()+qSin(MY_PI/rnum*(i+i+1))*cr);
    pa.setBrush(c);
    pa.drawEllipse(cp,lr,lr);
    pa.setPen(QPen(Qt::black,1,Qt::SolidLine));
    pa.setBrush(Qt::NoBrush);
    pa.drawEllipse(cp,lr,lr);
        QRect re;
    re.setLeft(cp.x()-6);
    re.setTop(cp.y()-4);
    re.setWidth(12);
    re.setHeight(8);
    pa.drawText(re,Qt::AlignCenter,QString::number(i+1));

}

void ReagentStatusWidget::drawCircle1(QPainter &pa, int i, QColor c)
{
    QPoint cp;
    QRect re;
    cp.setX(m_center.x()+qCos(MY_PI/rnum*(i+i+1))*cr1);
    cp.setY(m_center.y()+qSin(MY_PI/rnum*(i+i+1))*cr1);
    pa.setBrush(c);
    pa.drawEllipse(cp,lr,lr);
    pa.setPen(QPen(Qt::black,1,Qt::SolidLine));
    pa.setBrush(Qt::NoBrush);
    pa.drawEllipse(cp,lr,lr);
    re.setLeft(cp.x()-6);
    re.setTop(cp.y()-4);
    re.setWidth(12);
    re.setHeight(8);
    pa.drawText(re,Qt::AlignCenter,QString::number(i+1));
}

int ReagentStatusWidget::getR(int r)
{

        double L= MY_PI *2*r;
        double r1=L/80;
        return r1-3;
        //PI

}

void ReagentStatusWidget::drawRect(QPainter &pa, int i, QColor c,bool isfill)
{
    QPoint cp,cp1,cp2,cp3;
    QPainterPath pp;
    pa.setPen(QPen(c,1,Qt::SolidLine));
    if(!isfill) pa.setPen(QPen(c,2,Qt::SolidLine));
    cp.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r00);
    cp.setY(m_center.y()+qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r00);
    cp1.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r00);
    cp1.setY(m_center.y()+qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r00);
    cp2.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r01);
    cp2.setY(m_center.y()+qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r01);
    cp3.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r01);
    cp3.setY(m_center.y()+qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r01);
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
    if(isfill) pa.fillPath(pp,QBrush(Qt::gray));

}

void ReagentStatusWidget::drawRect1(QPainter &pa, int i, QColor c,bool isfill)
{
    QPoint cp,cp1,cp2,cp3;
    QPainterPath pp;
    pa.setPen(QPen(c,1,Qt::SolidLine));
    if(!isfill) pa.setPen(QPen(c,2,Qt::SolidLine));
    cp.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r10);
    cp.setY(m_center.y()+qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r10);
    cp1.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r10);
    cp1.setY(m_center.y()+qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r10);
    cp2.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r11);
    cp2.setY(m_center.y()+qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r11);
    cp3.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r11);
    cp3.setY(m_center.y()+qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r11);
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
    if(isfill) pa.fillPath(pp,QBrush(Qt::gray));

}

void ReagentStatusWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {

        //QPoint p=e->globalPos() - frameGeometry().topLeft();
        QPoint p1=e->pos();
        for(int i=0;i<rnum; i++)
        {
            QPoint cp,cp1,cp2,cp3;
            QPainterPath pp;
            //pa.setPen(QPen(c,1,Qt::SolidLine));
            //QRect re;
            cp.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r10);
            cp.setY(m_center.y()+qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r10);
            cp1.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r10);
            cp1.setY(m_center.y()+qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r10);
            cp2.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r11);
            cp2.setY(m_center.y()+qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r11);
            cp3.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r11);
            cp3.setY(m_center.y()+qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r11);
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
                cur_cir=1;
                this->update();
                return ;
            }
            cp.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r00);
            cp.setY(m_center.y()+qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r00);
            cp1.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r00);
            cp1.setY(m_center.y()+qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r00);
            cp2.setX(m_center.x()+qCos(2*MY_PI/rnum*i+MY_PI_SPAN)*r01);
            cp2.setY(m_center.y()+qSin(2*MY_PI/rnum*i+MY_PI_SPAN)*r01);
            cp3.setX(m_center.x()+qCos(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r01);
            cp3.setY(m_center.y()+qSin(2*MY_PI/rnum*(i+1)-MY_PI_SPAN)*r01);
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
