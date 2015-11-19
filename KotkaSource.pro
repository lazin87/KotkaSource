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
    ctask.cpp \
    csubject.cpp \
    iproject.cpp \
    cprojectbase.cpp \
    cprojectsmodel.cpp \
    cprojectmanager.cpp \
    ccreateprojectdialog.cpp

HEADERS  += mainwindow.h \
    ctask.h \
    csubject.h \
    iproject.h \
    cprojectbase.h \
    cprojectsmodel.h \
    cprojectmanager.h \
    commonddefs.h \
    ccreateprojectdialog.h

FORMS    += mainwindow.ui \
    ccreateprojectdialog.ui
