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
    fragmentation.cpp \
    figuregenerator.cpp \
    polygonview.cpp \
    packingbinarytree.cpp \
    doingframe.cpp \
    utilsdff.cpp

HEADERS  += mainwindow.h \
    utils.h \
    packing.h \
    mainpack.h \
    lbounds.h \
    figuregenerator.h \
    polygonview.h \
    doingframe.h

FORMS    += mainwindow.ui \
    doingframe.ui

OTHER_FILES += \
    result.txt \
    data.in \
    gen.in

RESOURCES += \
    images.qrc
