#-------------------------------------------------
#
# Project created by QtCreator 2018-06-08T02:12:22
#
#-------------------------------------------------

QT       += core gui
QT  += sql
QT +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = water
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    itembutton.cpp \
    cabutton.cpp \
    samplebutton.cpp \
    dbinterface.cpp \
    LogFile.cpp \
    debugout.cpp \
    clientsockt.cpp \
    myprocess.cpp \
    handlethread.cpp \
    interface.cpp \
    stopsampledia.cpp \
    srtab.cpp \
    catab.cpp \
    qutab.cpp \
    itemframe.cpp


HEADERS += \
        mainwindow.h \
    itembutton.h \
    cabutton.h \
    samplebutton.h \
    dbinterface.h \
    LogFile.h \
    debugout.h \
    clientsockt.h \
    myprocess.h \
    handlethread.h \
    interface.h \
    stopsampledia.h \
    srtab.h \
    catab.h \
    qutab.h \
    itemframe.h

LIBS += -lws2_32

FORMS += \
        mainwindow.ui \
    srtab.ui \
    stopsampledlg.ui \
    catab.ui \
    qutab.ui \
    itemframe.ui

RC_FILE += \
    water.rc
