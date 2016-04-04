QT += core
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = BioSimCppQT
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    creature.cpp \
    textfilereader.cpp \
    biosim.cpp \
    imagetga.cpp \
    gamemodel.cpp

HEADERS += \
    creature.hpp \
    exceptions.hpp \
    gamemodel.hpp \
    imagetga.hpp \
    landscape.hpp \
    textfilereader.hpp \
    biosim.hpp

DISTFILES += \
    Notizen \
    Grafics&Textfiles/cursor.tga \
    Grafics&Textfiles/dead.tga \
    Grafics&Textfiles/path.tga \
    Grafics&Textfiles/CreatureTable.txt \
    Grafics&Textfiles/CreatureTable_mitFehlern.txt \
    Grafics&Textfiles/Fehler_in_CreatureTable.txt \
    Grafics&Textfiles/wasser/algen.tga \
    Grafics&Textfiles/wasser/delphin.tga \
    Grafics&Textfiles/wasser/forelle.tga \
    Grafics&Textfiles/wasser/hai.tga \
    Grafics&Textfiles/wasser/krabbe.tga \
    Grafics&Textfiles/wasser/plankton.tga \
    Grafics&Textfiles/wasser/seetang.tga \
    Grafics&Textfiles/wasser/wels.tga \
    Grafics&Textfiles/terrain/deep_sea.tga \
    Grafics&Textfiles/terrain/earth.tga \
    Grafics&Textfiles/terrain/rocks.tga \
    Grafics&Textfiles/terrain/sand.tga \
    Grafics&Textfiles/terrain/shallow_water.tga \
    Grafics&Textfiles/terrain/snow.tga \
    Grafics&Textfiles/land/birne.tga \
    Grafics&Textfiles/land/busch.tga \
    Grafics&Textfiles/land/eiche.tga \
    Grafics&Textfiles/land/emu.tga \
    Grafics&Textfiles/land/gras.tga \
    Grafics&Textfiles/land/hund.tga \
    Grafics&Textfiles/land/kaktus.tga \
    Grafics&Textfiles/land/kuh.tga \
    Grafics&Textfiles/land/pferd.tga \
    Grafics&Textfiles/land/schaf.tga \
    Grafics&Textfiles/land/sonnenblume.tga \
    Grafics&Textfiles/land/tanne.tga \
    Grafics&Textfiles/land/tiger.tga \
    Grafics&Textfiles/land/ursus.tga \
    Grafics&Textfiles/Aufgabenblaetter.pdf \
    BioSim.qmodel \
    GraficsTextfiles/Aufgabenbl�tter.pdf \
    GraficsTextfiles/cursor.tga \
    GraficsTextfiles/dead.tga \
    GraficsTextfiles/path.tga \
    GraficsTextfiles/CreatureTable.txt \
    GraficsTextfiles/CreatureTable_mitFehlern.txt \
    GraficsTextfiles/Fehler_in_CreatureTable.txt

FORMS += \
    biosim.ui

RESOURCES += \
    resources.qrc
