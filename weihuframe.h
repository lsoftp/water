#ifndef WEIHUFRAME_H
#define WEIHUFRAME_H

#include <QFrame>

namespace Ui {
class WeihuFrame;
}

class WeihuFrame : public QFrame
{
    Q_OBJECT

public:
    explicit WeihuFrame(QWidget *parent = 0);
    ~WeihuFrame();

private:
    Ui::WeihuFrame *ui;
};

#endif // WEIHUFRAME_H
