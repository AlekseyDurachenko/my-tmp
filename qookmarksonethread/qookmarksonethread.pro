# Copyright 2014, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
TARGET          = qookmarksonethread
TEMPLATE        = app

CONFIG         += console debug_and_release
QT             += core gui network webkit xml

DESTDIR         = bin
OBJECTS_DIR     = build/release_obj
MOC_DIR         = build/release_moc
UI_DIR          = build/release_ui
RCC_DIR         = build/release_rcc

include($$PWD/submodules/qt-json/qt-json.pri)

DEFINES        +=                                           \

INCLUDEPATH    +=                                           \
    $$PWD/src                                               \
    $$PWD/src/manager                                       \
    $$PWD/src/bookmarkimport                                \
    $$PWD/src/tagitemmodel                                  \
    $$PWD/src/widget/bookmarkview                           \
    $$PWD/src/widget/navigationview                         \


HEADERS        +=                                           \
    src/mainwindow.h \
    src/manager/cbookmark.h \
    src/manager/cbookmarkitem.h \
    src/manager/cbookmarkmgr.h \
    src/manager/ctagitem.h \
    src/manager/ctag.h \
    src/bookmarkimport/bookmarkimportchromium.h \
    #src/tagitemmodel/ctagitemmodel.h
    src/manager/ctagmgr.h \
    src/manager/cmanager.h \
    src/manager/cbookmarkfilter.h \
    src/consts.h \
    src/manager/cabstractbookmarkfilter.h \
    src/manager/cbookmarkfilterdatamodel.h \
    src/widget/bookmarkview/cbookmarkfavoritesdelegate.h \
    src/widget/bookmarkview/cbookmarkreadlaterdelegate.h \
    src/widget/bookmarkview/cbookmarkfilteritemmodel.h \
    src/widget/navigationview/cnavigationitemmodel.h

SOURCES        +=                                           \
    src/mainwindow.cpp \
    src/manager/cbookmark.cpp \
    src/manager/cbookmarkitem.cpp \
    src/manager/cbookmarkmgr.cpp \
    src/manager/ctagitem.cpp \
    src/manager/ctag.cpp \
    src/bookmarkimport/bookmarkimportchromium.cpp \
    #src/tagitemmodel/ctagitemmodel.cpp
    src/manager/ctagmgr.cpp \
    src/manager/cmanager.cpp \
    src/manager/cbookmarkfilter.cpp \
    src/manager/cabstractbookmarkfilter.cpp \
    src/manager/cbookmarkfilterdatamodel.cpp \
    src/widget/bookmarkview/cbookmarkfavoritesdelegate.cpp \
    src/widget/bookmarkview/cbookmarkreadlaterdelegate.cpp \
    src/widget/bookmarkview/cbookmarkfilteritemmodel.cpp \
    src/widget/navigationview/cnavigationitemmodel.cpp

FORMS          +=                                           \
    src/mainwindow.ui

RESOURCES      +=                                           \
    qrc/icons.qrc

OTHER_FILES    +=                                           \

# if you want to test the project, do: qmake "QT += testlib"
contains(QT, testlib) {
    SOURCES   +=                                            \

    HEADERS   +=                                            \

} else {
    SOURCES   +=                                            \
        src/main.cpp                                        \

}

win32 {
    CONFIG += embed_manifest_exe
    RC_FILE = qookmarks.rc
}

# debug
build_pass:CONFIG(debug, debug|release) {
    TARGET      = $$join(TARGET,,,d)
    OBJECTS_DIR = $$join(OBJECTS_DIR,,,d)
    MOC_DIR     = $$join(MOC_DIR,,,d)
    UI_DIR      = $$join(UI_DIR,,,d)
    RCC_DIR     = $$join(RCC_DIR,,,d)

    win32 {
    }

    unix {
        LIBS +=
    }
}

# release
build_pass:CONFIG(release, debug|release) {
    win32 {
        CONFIG -= console
        LIBS +=
    }

    unix {
        LIBS +=
    }
}

DISTFILES +=
