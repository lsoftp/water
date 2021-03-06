#ifndef SAMPLEFRAME_H
#define SAMPLEFRAME_H

#include <QFrame>

namespace Ui {
class SampleFrame;
}

class SampleFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SampleFrame(QWidget *parent = 0);
    ~SampleFrame();

private slots:
    void on_printbtn_clicked();

private:
    Ui::SampleFrame *ui;
};

#endif // SAMPLEFRAME_H
