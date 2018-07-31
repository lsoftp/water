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

    void refreshtable();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CaCurveFrame *ui;
};

#endif // CACURVEFRAME_H
