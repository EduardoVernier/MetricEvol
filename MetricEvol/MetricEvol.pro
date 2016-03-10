#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T01:32:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MetricEvol
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    repository.cpp \
    clonedialog.cpp \
    trie.cpp \
    metricextractor.cpp

HEADERS  += mainwindow.h \
    repository.h \
    clonedialog.h \
    trie.h \
    metricextractor.h

FORMS    += mainwindow.ui \
    clonedialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/libgit2-0.23.4/build/release/ -lgit2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/libgit2-0.23.4/build/debug/ -lgit2
else:unix: LIBS += -L$$PWD/../libs/libgit2-0.23.4/build/ -lgit2

INCLUDEPATH += $$PWD/../libs/libgit2-0.23.4/build
DEPENDPATH += $$PWD/../libs/libgit2-0.23.4/build
