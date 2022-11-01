QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MoveGraphicsItem
TEMPLATE = app

CONFIG += c++1z

SOURCES += main.cpp\
    dialog.cpp \
    dialogdel.cpp \
    dialoglink.cpp \
    linkitem.cpp \
    methodsdescr.cpp \
        widget.cpp \
    moveitem.cpp

HEADERS  += widget.h \
    dialog.h \
    dialogdel.h \
    dialoglink.h \
    linkitem.h \
    methodsdescr.h \
    moveitem.h

FORMS    += widget.ui \
    dialog.ui \
    dialogdel.ui \
    dialoglink.ui \
    methodsdescr.ui

DISTFILES +=
