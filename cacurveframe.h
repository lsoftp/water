#ifndef CACURVEFRAME_H
#define CACURVEFRAME_H

#include <QFrame>
#include <QGraphicsScene>
namespace Ui {
class CaCurveFrame;
}

class CaCurveFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CaCurveFrame(QWidget *parent = 0);
    ~CaCurveFrame();
    bool ifSelectCa();
    bool ifSelectCa1();
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

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::CaCurveFrame *ui;
    QString selCaname;
    QString selTestname;
    QGraphicsScene scene;
};

#endif // CACURVEFRAME_H
