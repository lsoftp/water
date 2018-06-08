#ifndef SAMPLEBUTTON_H
#define SAMPLEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class SampleButton : public QPushButton
{
    Q_OBJECT
public:
    int f;
    explicit SampleButton(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);
signals:

public slots:
};

#endif // SAMPLEBUTTON_H
