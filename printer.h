#ifndef PRINTER_H
#define PRINTER_H
#include <QtPrintSupport/QPrinter>

#include <QObject>

class Printer : public QObject
{
    Q_OBJECT
public:
    QPrinter p;
    explicit Printer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PRINTER_H
