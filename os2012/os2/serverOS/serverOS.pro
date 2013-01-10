#-------------------------------------------------
#
# Project created by QtCreator 2012-10-27T12:10:00
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = serverOS
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -fno-stack-protector

SOURCES += main.cpp \
    comandexecuter.cpp \
    taskmanager.cpp \
    receiver.cpp \
    epollreciver.cpp

HEADERS += \
    comandexecuter.h \
    taskmanager.h \
    task.h \
    receiver.h \
    epollreciver.h
