#ifndef STATUSFRAME_H
#define STATUSFRAME_H

#include <QFrame>

namespace Ui {
class StatusFrame;
}

class StatusFrame : public QFrame
{
    Q_OBJECT

public:
    explicit StatusFrame(QWidget *parent = 0);
    ~StatusFrame();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::StatusFrame *ui;
};

#endif // STATUSFRAME_H
