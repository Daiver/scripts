#-------------------------------------------------
#
# Project created by QtCreator 2013-04-21T18:31:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphVizion
TEMPLATE = app

QMAKE_CXXFLAGS += --std=c++11

LIBS +=  -lboost_system -lboost_filesystem 


SOURCES += main.cpp\
        mainwindow.cpp \
    graphcanvas.cpp

HEADERS  += mainwindow.h \
    graphcanvas.h \
    typedefs.h

FORMS    += mainwindow.ui
