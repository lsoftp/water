#include "samplestatuswidget.h"

#define MY_PI 3.14159265358979323846
const QColor SampleStatusWidget::scolor[STATE_NUM]={QColor(255,255,255),QColor(0,255,0),QColor(170,0,127),QColor(170,0,255)};
const QColor SampleStatusWidget::tcolor[TYPE_NUM]={QColor(Qt::white),QColor(Qt::green),QColor(Qt::red),QColor(Qt::magenta), QColor(Qt::yellow),QColor(Qt::gray)};
SampleStatusWidget::SampleStatusWidget(QWidget *parent) : QWidget(parent)
{
    for(int i=0;i<40;i++)
    {
        m_status[i].s=STATE_IDLE;
        m_status[i].t=TYPE_NULL;
    }
    current=-1;
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


        paint.setPen(QPen(Qt::black,2,Qt::SolidLine));

    paint.drawEllipse(m_center,R,R);
    paint.drawEllipse(m_center,R-40,R-40);
   // paint.drawEllipse(m_center,R-20,R-20);
    int mr=getR(R-20);
    MR=R-20;
    r1=mr;
    r0=mr-5;
    for(int i=0;i<40;i++)
    {
        QPoint cp;
        QRect re;

        cp.setX(m_center.x()+qCos(2*MY_PI/40*i)*MR);
        cp.setY(m_center.y()+qSin(2*MY_PI/40*i)*MR);
        re.setLeft(cp.x()-6);
        re.setTop(cp.y()-4);
        re.setWidth(12);
        re.setHeight(8);
        draw(paint,cp,m_status[i]);
        paint.drawText(re,Qt::AlignCenter,QString::number(i+1));

    }
    if(current!=-1)
    {
        QPoint cp;
        //QRect re;

        cp.setX(m_center.x()+qCos(2*MY_PI/40*current)*MR);
        cp.setY(m_center.y()+qSin(2*MY_PI/40*current)*MR);
            paint.setPen(QPen(Qt::white,3,Qt::SolidLine));
            paint.drawEllipse(cp,r1,r1);

    }

    QPoint tp;
    status ts;
    tp.setX(m_center.x()-60);
    tp.setY(m_center.y()-(r1+2)*3);
    ts={STATE_IDLE,TYPE_NULL};
    drawLegend(paint,tp,ts,"空闲");

    tp.setY(m_center.y()-(r1+2));
    ts={STATE_REGISTERED,TYPE_NULL};
    drawLegend(paint,tp,ts,"已登记");

    tp.setY(m_center.y()+(r1+2));
    ts={STATE_DOING,TYPE_NULL};
    drawLegend(paint,tp,ts,"分析中");

    tp.setY(m_center.y()+(r1+2)*3);
    ts={STATE_FINISHED,TYPE_NULL};
    drawLegend(paint,tp,ts,"已完成");

    tp=m_center;
    tp.setX(m_center.x()+40);
    tp.setY(m_center.y()-(r1+2)*5);
    ts={STATE_IDLE,TYPE_NULL};
    drawLegend(paint,tp,ts,"空");
    tp.setY(m_center.y()-(r1+2)*3);
    ts={STATE_IDLE,TYPE_NORMAL};
    drawLegend(paint,tp,ts,"常规");
    tp.setY(m_center.y()-(r1+2)*1);
    ts={STATE_IDLE,TYPE_URGENT};
    drawLegend(paint,tp,ts,"急诊");
    tp.setY(m_center.y()+(r1+2)*1);
    ts={STATE_IDLE,TYPE_QU};
    drawLegend(paint,tp,ts,"质控");
    tp.setY(m_center.y()+(r1+2)*3);
    ts={STATE_IDLE,TYPE_CA};
    drawLegend(paint,tp,ts,"定标");
    tp.setY(m_center.y()+(r1+2)*5);
    ts={STATE_IDLE,TYPE_NOTENOUGH};
    drawLegend(paint,tp,ts,"不足");


        //paint.drawEllipse(0,0,50,60);
    paint.end();
}

void SampleStatusWidget::drawLegend( QPainter &pa, const QPoint &p, const SampleStatusWidget::status &s,const QString & str)
{
    draw(pa,p,s);
    QRect tr;
    tr.setLeft(p.x()+r1+3);
    tr.setTop(p.y()-6);
    tr.setWidth(40);
    tr.setHeight(12);
    pa.drawText(tr,Qt::AlignLeft,str);

}
static double square(const double num){return num * num;}
static double p2p(const QPoint& pt1, const QPoint& pt2)
{
    return sqrt(double(square(pt2.x() - pt1.x()) + square(pt2.y() - pt1.y())));
}

void SampleStatusWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {

        //QPoint p=e->globalPos() - frameGeometry().topLeft();
        QPoint p1=e->pos();
        for(int i=0;i<40; i++)
        {
            QPoint cp;
            QRect re;

            cp.setX(m_center.x()+qCos(2*MY_PI/40*i)*MR);
            cp.setY(m_center.y()+qSin(2*MY_PI/40*i)*MR);
            if( p2p(p1,cp)<r1) {
                current=i;
                this->update();
                return ;
            }
        }

        //e->accept();
    }

}

int SampleStatusWidget::getR(int r)
{
    double L= MY_PI *2*r;
    double r1=L/80;
    return r1;
    //PI
}

void SampleStatusWidget::draw( QPainter &pa, const QPoint &p, const SampleStatusWidget::status &s)
{
    pa.setBrush(scolor[s.s]);
    pa.drawEllipse(p,r1,r1);
    pa.setBrush(tcolor[s.t]);
    pa.drawEllipse(p,r0,r0);

    pa.setPen(QPen(Qt::black,2,Qt::SolidLine));
    pa.setBrush(Qt::NoBrush);
    pa.drawEllipse(p,r1,r1);
    pa.drawEllipse(p,r0,r0);

}
