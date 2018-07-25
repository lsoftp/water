#ifndef SYSTEMFRAME_H
#define SYSTEMFRAME_H

#include <QFrame>

namespace Ui {
class SystemFrame;
}

class SystemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SystemFrame(QWidget *parent = 0);
    ~SystemFrame();

private:
    Ui::SystemFrame *ui;
};

#endif // SYSTEMFRAME_H
