#-------------------------------------------------
#
# Project created by QtCreator 2013-12-04T22:00:35
#
#-------------------------------------------------

QT       += core gui

TARGET = D_Packing_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utils.cpp \
    packing.cpp \
    mainpack.cpp \
    lbounds.cpp \
    fragmentation.cpp

HEADERS  += mainwindow.h \
    utils.h \
    packing.h \
    mainpack.h \
    lbounds.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    result.txt \
    data.in
