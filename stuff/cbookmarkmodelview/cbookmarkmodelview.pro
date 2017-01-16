#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T21:58:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cbookmarkmodelview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cbookmark.cpp \
    cbookmarkrepresentationorigin.cpp \
    cbookmarkrepresentation.cpp \
    ccorefacade.cpp \
    cbookmarkitemmodel.cpp

HEADERS  += mainwindow.h \
    cbookmark.h \
    cbookmarkrepresentationorigin.h \
    cbookmarkrepresentation.h \
    ccorefacade.h \
    cbookmarkitemmodel.h

FORMS    += mainwindow.ui
