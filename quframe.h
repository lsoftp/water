#ifndef QUFRAME_H
#define QUFRAME_H

#include <QFrame>

namespace Ui {
class QuFrame;
}

class QuFrame : public QFrame
{
    Q_OBJECT

public:
    explicit QuFrame(QWidget *parent = 0);
    ~QuFrame();

private:
    Ui::QuFrame *ui;
};

#endif // QUFRAME_H
