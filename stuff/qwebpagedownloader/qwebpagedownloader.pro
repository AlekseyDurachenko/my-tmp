#-------------------------------------------------
#
# Project created by QtCreator 2015-02-20T14:50:44
#
#-------------------------------------------------

QT       += core network webkit webkitwidgets

TARGET = qwebpagedownloader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    src/cwebfiledownloader.cpp \
    src/main.cpp \
    src/cwebpagedownloader.cpp \
    src/cwebpagescreenshot.cpp

HEADERS += \
    src/cwebfiledownloader.h \
    src/cwebpagedownloader.h \
    src/cwebpagescreenshot.h
