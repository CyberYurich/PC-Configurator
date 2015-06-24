#-------------------------------------------------
#
# Project created by QtCreator 2014-09-03T13:18:41
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Configurator
TEMPLATE = app

CONFIG += c++11

DEFINES += QUAZIP_BUILD
DEFINES += QUAZIP_STATIC

INCLUDEPATH += $$PWD/quazip
DEPENDPATH += $$PWD/quazip

#закомментировать для статической сборки
LIBS += -L$$PWD -lquazip

#раскомментировать для статической сборки
#SOURCES += $$PWD/quazip/*.cpp
#SOURCES += $$PWD/quazip/*.c
#HEADERS += $$PWD/quazip/*.h

SOURCES += main.cpp\
        mainwindow.cpp \
    platformswidget.cpp \
    configuratorwidget.cpp \
    componentswidget.cpp \
    platform.cpp \
    addeditplatformdialog.cpp \
    components.cpp \
    addeditcompoents.cpp \
    mytabwidget.cpp \
    mydelegates.cpp

HEADERS  += mainwindow.h \
    platformswidget.h \
    configuratorwidget.h \
    componentswidget.h \
    platform.h \
    addeditplatformdialog.h \
    components.h \
    addeditcompoents.h \
    mytabwidget.h \
    mydelegates.h \
    mytreewidget.h

FORMS    += mainwindow.ui \
    platformswidget.ui \
    configuratorwidget.ui \
    componentswidget.ui \
    addeditplatformdialog.ui \
    addeditcompoents.ui

RC_FILE = appres.rc

