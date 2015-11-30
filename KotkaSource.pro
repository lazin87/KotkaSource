#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T18:02:47
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KotkaSource
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ctask.cpp \
    iproject.cpp \
    cprojectbase.cpp \
    cprojectmanager.cpp \
    ccreateprojectdialog.cpp \
    ccreatetaskdialog.cpp \
    cclientsandwritersdbmodel.cpp \
    cperson.cpp \
    ccreatecontactdialog.cpp \
    cpersonpropertis.cpp \
    csourcesmodel.cpp \
    isource.cpp \
    csourcepropertis.cpp \
    isourceparsestrategy.cpp

HEADERS  += mainwindow.h \
    ctask.h \
    iproject.h \
    cprojectbase.h \
    cprojectmanager.h \
    commonddefs.h \
    ccreateprojectdialog.h \
    ccreatetaskdialog.h \
    cclientsandwritersdbmodel.h \
    cperson.h \
    ccreatecontactdialog.h \
    cpersonpropertis.h \
    csourcesmodel.h \
    isource.h \
    csourcepropertis.h \
    isourceparsestrategy.h

FORMS    += mainwindow.ui \
    ccreateprojectdialog.ui \
    ccreatetaskdialog.ui \
    ccreatecontactdialog.ui
