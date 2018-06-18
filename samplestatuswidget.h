#ifndef SAMPLESTAUSWIDGET_H
#define SAMPLESTAUSWIDGET_H

#include <QWidget>
#include <QPoint>

class SampleStatusWidget : public QWidget
{
    Q_OBJECT
    enum state{
        STATE_IDLE,
        STATE_REGISTERED,
        STATE_DOING,
        STATE_FINISHED,
        STATE_NUM,

    };
    enum type{
        TYPE_NULL,
        TYPE_NORMAL,
        TYPE_URGENT,
        TYPE_QU,
        TYPE_CA,
        TYPE_NOTENOUGH,
        TYPE_NUM
    };

    struct status{
        state s;
        type t;
    };

public:
    status m_status[40];
    int r0; //内圈半径
    int r1; //外圈半径
    int R;//大圈半径
    const static int margin=10;
    //static const int i[2]={1.2};
    //static const  Qt::GlobalColor y=Qt::red;
     static const  Qt::GlobalColor scolor[STATE_NUM];//={Qt::white,Qt::green,Qt::magenta,Qt::black};
    QPoint m_center;
    explicit SampleStatusWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
signals:

public slots:
};

#endif // SAMPLESTAUSWIDGET_H
