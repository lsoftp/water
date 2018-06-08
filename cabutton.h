#ifndef CABUTTON_H
#define CABUTTON_H

#include <QPushButton>

class CaButton : public QPushButton
{
    Q_OBJECT
public:
    int state;
    int testid;
    int type; //0 空白 定标 都有   ，1只有定标一种状态
    explicit CaButton(QWidget *parent = nullptr);

signals:

public slots:
    void setState();
};

#endif // CABUTTON_H
