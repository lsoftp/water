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
    void on_tabWidget_currentChanged(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_singlebtn_toggled(bool checked);

    void on_doublebtn_toggled(bool checked);

signals:
    void back();
private:
    Ui::SystemFrame *ui;
    bool ifSelectCa(bool b=false);
    QString selCaname;
    QString selTestname;
    QString selOrdername;
    bool ifSelectTest();
    void refreshtable();
    void refreshtable1(QString sel);
    void refreshItemOrderTable();
    int ifSelectItemOrder(bool b);
    void init_item_order();
    void init_dict();
};

#endif // SYSTEMFRAME_H
