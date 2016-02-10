QT += core
QT -= gui

CONFIG += c++11

TARGET = BioSimCppQT
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    creature.cpp \
    textfilereader.cpp

HEADERS += \
    main.h \
    config.h \
    creature.h \
    textfilereader.h

DISTFILES += \
    Notizen
