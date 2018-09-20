#ifndef REAGENTSTATUSWIDGET_H
#define REAGENTSTATUSWIDGET_H

#include <QWidget>
#include <QPoint>
#include <qpainter.h>
#include <QtCore/qmath.h>
#include <QRect>
#include <QMouseEvent>
class ReagentStatusWidget : public QWidget
{
    Q_OBJECT
    enum state{
        S_ENOUGH,
        S_LACK,
        S_IDLE,
        S_NUM
    };
    const static  int rnum=40;
    static const  QColor scolor[S_NUM];
    int R,R1,R2,r00,r01,r10,r11;
    int cr,cr1;//小圆圆心所在的大圆的半径
    int lr; //试剂圆的半径
    QPoint m_center;
public:
    int current;
    int cur_cir;//内圈为0，外圈为1
    state m_status[rnum];
    explicit ReagentStatusWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    //int getR(int r);
    void drawRect( QPainter &pa, int i,QColor c,bool isfill=true);
    void drawRect1(QPainter &pa, int i,QColor c,bool isfill=true);
    void drawCircle( QPainter &pa, int i,QColor c);
    void drawCircle1( QPainter &pa, int i,QColor c);
    int getR(int r);
    //void drawLegend(QPainter &pa, const QPoint &p, const SampleStatusWidget::status &s,const QString &str);
    void mousePressEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // REAGENTSTATUSWIDGET_H
