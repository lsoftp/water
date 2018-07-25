#ifndef CACURVEFRAME_H
#define CACURVEFRAME_H

#include <QFrame>

namespace Ui {
class CaCurveFrame;
}

class CaCurveFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CaCurveFrame(QWidget *parent = 0);
    ~CaCurveFrame();

private:
    Ui::CaCurveFrame *ui;
};

#endif // CACURVEFRAME_H
