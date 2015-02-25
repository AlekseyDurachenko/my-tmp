#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T14:58:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qookmarksonethread
TEMPLATE = app


INCLUDEPATH += bookmarkmgr

SOURCES += main.cpp\
        mainwindow.cpp \
    bookmarkmgr/cbookmark.cpp \
    bookmarkmgr/cbookmarkmgr.cpp \
    bookmarkmgr/cbookmarkitem.cpp \
    bookmarkmgr/ctagitem.cpp \
    bookmarkmgr/ctagdata.cpp \
    bookmarkmgr/ctagmgr.cpp

HEADERS  += mainwindow.h \
    bookmarkmgr/cbookmark.h \
    bookmarkmgr/cbookmarkmgr.h \
    bookmarkmgr/cbookmarkitem.h \
    bookmarkmgr/ctagitem.h \
    bookmarkmgr/ctagdata.h \
    bookmarkmgr/ctagmgr.h

FORMS    += mainwindow.ui
