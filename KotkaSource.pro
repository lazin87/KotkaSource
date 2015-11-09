#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T18:02:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KotkaSource
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cproject.cpp \
    csubproject.cpp \
    ctask.cpp \
    csubject.cpp

HEADERS  += mainwindow.h \
    cproject.h \
    csubproject.h \
    ctask.h \
    csubject.h

FORMS    += mainwindow.ui
