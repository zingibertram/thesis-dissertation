#-------------------------------------------------
#
# Project created by QtCreator 2013-12-04T22:00:35
#
#-------------------------------------------------

QT       += core gui

TARGET = Packing_DFF
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
    utilsdff.cpp \
    mainpackio.cpp \
    translation.cpp \
    knapsacksolver.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
    utils.h \
    packing.h \
    mainpack.h \
    lbounds.h \
    figuregenerator.h \
    polygonview.h \
    doingframe.h \
    translation.h \
    knapsacksolver.h \
    dialogabout.h

FORMS    += mainwindow.ui \
    doingframe.ui \
    dialogabout.ui

OTHER_FILES += \
    data.in \
    gen.in

RESOURCES += \
    images.qrc

# добавляет иконку для ехе-файла в windows
RC_FILE = exeicon.rc
