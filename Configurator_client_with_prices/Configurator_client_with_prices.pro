#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T11:41:14
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Configurator_client_with_prices
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

SOURCES += \
    components.cpp \
    configuratorwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    platform.cpp \
    accountdialog.cpp

HEADERS  += \
    components.h \
    configuratorwidget.h \
    mainwindow.h \
    platform.h \
    accountdialog.h

FORMS    += \
    configuratorwidget.ui \
    mainwindow.ui \
    accountdialog.ui

RC_FILE = appres.rc
