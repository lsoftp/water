/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[408];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_toolButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_toolButton_5_clicked"
QT_MOC_LITERAL(4, 58, 23), // "on_toolButton_8_clicked"
QT_MOC_LITERAL(5, 82, 23), // "on_pushButton_9_clicked"
QT_MOC_LITERAL(6, 106, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(7, 134, 5), // "index"
QT_MOC_LITERAL(8, 140, 24), // "on_toolButton_13_clicked"
QT_MOC_LITERAL(9, 165, 24), // "on_pushButton_14_clicked"
QT_MOC_LITERAL(10, 190, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(11, 214, 23), // "on_pushButton_6_toggled"
QT_MOC_LITERAL(12, 238, 7), // "checked"
QT_MOC_LITERAL(13, 246, 24), // "on_pushButton_15_clicked"
QT_MOC_LITERAL(14, 271, 24), // "on_pushButton_16_clicked"
QT_MOC_LITERAL(15, 296, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(16, 321, 23), // "on_toolButton_9_clicked"
QT_MOC_LITERAL(17, 345, 13), // "display_blank"
QT_MOC_LITERAL(18, 359, 24), // "on_toolButton_11_clicked"
QT_MOC_LITERAL(19, 384, 23) // "on_MainWindow_destroyed"

    },
    "MainWindow\0on_toolButton_clicked\0\0"
    "on_toolButton_5_clicked\0on_toolButton_8_clicked\0"
    "on_pushButton_9_clicked\0"
    "on_tabWidget_currentChanged\0index\0"
    "on_toolButton_13_clicked\0"
    "on_pushButton_14_clicked\0"
    "on_pushButton_6_clicked\0on_pushButton_6_toggled\0"
    "checked\0on_pushButton_15_clicked\0"
    "on_pushButton_16_clicked\0"
    "on_pushButton_13_clicked\0"
    "on_toolButton_9_clicked\0display_blank\0"
    "on_toolButton_11_clicked\0"
    "on_MainWindow_destroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    1,   98,    2, 0x08 /* Private */,
       8,    0,  101,    2, 0x08 /* Private */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    1,  104,    2, 0x08 /* Private */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    0,  111,    2, 0x08 /* Private */,
      18,    0,  112,    2, 0x08 /* Private */,
      19,    0,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_toolButton_clicked(); break;
        case 1: _t->on_toolButton_5_clicked(); break;
        case 2: _t->on_toolButton_8_clicked(); break;
        case 3: _t->on_pushButton_9_clicked(); break;
        case 4: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_toolButton_13_clicked(); break;
        case 6: _t->on_pushButton_14_clicked(); break;
        case 7: _t->on_pushButton_6_clicked(); break;
        case 8: _t->on_pushButton_6_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_pushButton_15_clicked(); break;
        case 10: _t->on_pushButton_16_clicked(); break;
        case 11: _t->on_pushButton_13_clicked(); break;
        case 12: _t->on_toolButton_9_clicked(); break;
        case 13: _t->display_blank(); break;
        case 14: _t->on_toolButton_11_clicked(); break;
        case 15: _t->on_MainWindow_destroyed(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
