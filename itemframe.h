#ifndef ITEMFRAME_H
#define ITEMFRAME_H

#include <QFrame>
#include <QWidget>

namespace Ui {
class ItemFrame;
}

class ItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ItemFrame(QWidget *parent = 0);
    ~ItemFrame();
    void init();
    void setDbstatus(int s);

public slots:

private slots:
    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);
    void display_blank();


private:
    Ui::ItemFrame *ui;
    int dbstatus;
};

#endif // ITEMFRAME_H
