#-------------------------------------------------
#
# Project created by QtCreator 2013-09-22T13:01:07
#
#-------------------------------------------------

# It's about diploma theme
# Dual Feasible Function for a
# figure made up of rectangles
# orthogonal packing

QT       += core
QT       -= gui

TARGET = packing
CONFIG   -= console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    utils.cpp \
    lbounds.cpp \
    packing.cpp \
    fragmentation.cpp \
    main.cpp \

OTHER_FILES += \
    data.in \
    result.txt

HEADERS += \
    utils.h \
    lbounds.h \
    packing.h \
    fragmentation.h \






