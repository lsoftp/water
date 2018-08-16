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
    bool ifSelectCa(bool b=false);

    bool ifSelectTest();

    void refreshtable();//刷新标准列表
    void refreshtable1(QString sel);//刷新选择标准液的测试

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_tableWidget_itemSelectionChanged();

private:
    Ui::QuFrame *ui;
    QString selCaname;
    QString selTestname;

};

#endif // QUFRAME_H
