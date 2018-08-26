#ifndef PRINTER_H
#define PRINTER_H
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QObject>

class Printer : public QObject
{
    Q_OBJECT
public:
    QPrinter p;
    explicit Printer(QObject *parent = nullptr);

signals:

public slots:
    void printDocument(QPrinter *printer);
};

#endif // PRINTER_H
