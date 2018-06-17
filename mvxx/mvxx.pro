#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T13:53:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = mvxx
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
    lib/qcustomplot.cpp \
    model/list/harmonicitem.cpp \
    utils/trigonometric.cpp \
    model/list/harmonicitembuilder.cpp \
    view/listview.cpp \
    view/editharmonicview.cpp \
    model/list/harmoniclist.cpp \
    model/harmonicsmodel.cpp \
    model/harmoniclistviewmodel.cpp \
    controller/listcontroller.cpp \
    model/editharmonicviewmodel.cpp \
    controller/editharmoniccontroller.cpp \
    view/harmonicplotview.cpp \
    model/harmonicfunctionviewmodel.cpp \
    model/newharmonicviewmodel.cpp

HEADERS += \
        mainwindow.h \
    lib/qcustomplot.h \
    utils/trigonometric.h \
    model/list/harmonicitem.h \
    model/list/harmonicitembuilder.h \
    view/listview.h \
    view/editharmonicview.h \
    model/harmoniclistviewmodel.h \
    model/list/harmoniclist.h \
    model/harmonicsmodel.h \
    model/iharmonicsmodel.h \
    controller/listcontroller.h \
    model/editharmonicviewmodel.h \
    model/iharmonicviewmodel.h \
    controller/editharmoniccontroller.h \
    view/harmonicplotview.h \
    model/harmonicfunctionviewmodel.h \
    model/newharmonicviewmodel.h

FORMS += \
        mainwindow.ui \
    insertdialog.ui
