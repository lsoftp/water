#ifndef SYSTEMFRAME_H
#define SYSTEMFRAME_H

#include <QFrame>
#include <QMessageBox>
namespace Ui {
class SystemFrame;
}

class SystemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SystemFrame(QWidget *parent = 0);
    ~SystemFrame();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_tableWidget_2_itemSelectionChanged();
    void on_careturnbtn_clicked();
signals:
    void back();
private:
    Ui::SystemFrame *ui;
    bool ifSelectCa(bool b=false);
    QString selCaname;
    QString selTestname;
    bool ifSelectTest();
    void refreshtable();
    void refreshtable1(QString sel);
};

#endif // SYSTEMFRAME_H
