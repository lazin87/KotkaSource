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
    csubproject.cpp \
    ctask.cpp \
    csubject.cpp \
    cmainproject.cpp \
    iproject.cpp \
    cprojectbase.cpp \
    cprojectsmodel.cpp \
    cprojectmanager.cpp

HEADERS  += mainwindow.h \
    csubproject.h \
    ctask.h \
    csubject.h \
    cmainproject.h \
    iproject.h \
    cprojectbase.h \
    cprojectsmodel.h \
    cprojectmanager.h

FORMS    += mainwindow.ui
