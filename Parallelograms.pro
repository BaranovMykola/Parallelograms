#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T21:07:39
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Parallelograms
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lego.cpp \
    parallelogram.cpp \
    clickedlabel.cpp \
    AbstractParallelogramState.cpp \
    MonochromeParallelogram.cpp \
    RandomParallelogram.cpp

HEADERS  += mainwindow.h \
    lego.h \
    parallelogram.h \
    clickedlabel.h \
    AbstractParallelogramState.h \
    MonochromeParallelogram.h \
    RandomParallelogram.h
