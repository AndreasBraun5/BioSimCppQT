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
    gamemodel.cpp \
    landscape.cpp \
    libnoise/model/cylinder.cpp \
    libnoise/model/line.cpp \
    libnoise/model/plane.cpp \
    libnoise/model/sphere.cpp \
    libnoise/module/abs.cpp \
    libnoise/module/add.cpp \
    libnoise/module/billow.cpp \
    libnoise/module/blend.cpp \
    libnoise/module/cache.cpp \
    libnoise/module/checkerboard.cpp \
    libnoise/module/clamp.cpp \
    libnoise/module/const.cpp \
    libnoise/module/curve.cpp \
    libnoise/module/cylinders.cpp \
    libnoise/module/displace.cpp \
    libnoise/module/exponent.cpp \
    libnoise/module/invert.cpp \
    libnoise/module/max.cpp \
    libnoise/module/min.cpp \
    libnoise/module/modulebase.cpp \
    libnoise/module/multiply.cpp \
    libnoise/module/perlin.cpp \
    libnoise/module/power.cpp \
    libnoise/module/ridgedmulti.cpp \
    libnoise/module/rotatepoint.cpp \
    libnoise/module/scalebias.cpp \
    libnoise/module/scalepoint.cpp \
    libnoise/module/select.cpp \
    libnoise/module/spheres.cpp \
    libnoise/module/terrace.cpp \
    libnoise/module/translatepoint.cpp \
    libnoise/module/turbulence.cpp \
    libnoise/module/voronoi.cpp \
    libnoise/win32/dllmain.cpp \
    libnoise/latlon.cpp \
    libnoise/noisegen.cpp \
    libnoise/noiseutils.cpp

HEADERS += \
    util.hpp \
    textfilereader.hpp \
    landscape.hpp \
    imagetga.hpp \
    gamemodel.hpp \
    exceptions.hpp \
    creature.hpp \
    biosim.hpp \
    libnoise/include/noise/model/cylinder.h \
    libnoise/include/noise/model/line.h \
    libnoise/include/noise/model/model.h \
    libnoise/include/noise/model/plane.h \
    libnoise/include/noise/model/sphere.h \
    libnoise/include/noise/module/abs.h \
    libnoise/include/noise/module/add.h \
    libnoise/include/noise/module/billow.h \
    libnoise/include/noise/module/blend.h \
    libnoise/include/noise/module/cache.h \
    libnoise/include/noise/module/checkerboard.h \
    libnoise/include/noise/module/clamp.h \
    libnoise/include/noise/module/const.h \
    libnoise/include/noise/module/curve.h \
    libnoise/include/noise/module/cylinders.h \
    libnoise/include/noise/module/displace.h \
    libnoise/include/noise/module/exponent.h \
    libnoise/include/noise/module/invert.h \
    libnoise/include/noise/module/max.h \
    libnoise/include/noise/module/min.h \
    libnoise/include/noise/module/module.h \
    libnoise/include/noise/module/modulebase.h \
    libnoise/include/noise/module/multiply.h \
    libnoise/include/noise/module/perlin.h \
    libnoise/include/noise/module/power.h \
    libnoise/include/noise/module/ridgedmulti.h \
    libnoise/include/noise/module/rotatepoint.h \
    libnoise/include/noise/module/scalebias.h \
    libnoise/include/noise/module/scalepoint.h \
    libnoise/include/noise/module/select.h \
    libnoise/include/noise/module/spheres.h \
    libnoise/include/noise/module/terrace.h \
    libnoise/include/noise/module/translatepoint.h \
    libnoise/include/noise/module/turbulence.h \
    libnoise/include/noise/module/voronoi.h \
    libnoise/include/noise/basictypes.h \
    libnoise/include/noise/exception.h \
    libnoise/include/noise/interp.h \
    libnoise/include/noise/latlon.h \
    libnoise/include/noise/mathconsts.h \
    libnoise/include/noise/misc.h \
    libnoise/include/noise/noise.h \
    libnoise/include/noise/noisegen.h \
    libnoise/include/noise/vectortable.h \
    libnoise/model/cylinder.h \
    libnoise/model/line.h \
    libnoise/model/model.h \
    libnoise/model/plane.h \
    libnoise/model/sphere.h \
    libnoise/module/abs.h \
    libnoise/module/add.h \
    libnoise/module/billow.h \
    libnoise/module/blend.h \
    libnoise/module/cache.h \
    libnoise/module/checkerboard.h \
    libnoise/module/clamp.h \
    libnoise/module/const.h \
    libnoise/module/curve.h \
    libnoise/module/cylinders.h \
    libnoise/module/displace.h \
    libnoise/module/exponent.h \
    libnoise/module/invert.h \
    libnoise/module/max.h \
    libnoise/module/min.h \
    libnoise/module/module.h \
    libnoise/module/modulebase.h \
    libnoise/module/multiply.h \
    libnoise/module/perlin.h \
    libnoise/module/power.h \
    libnoise/module/ridgedmulti.h \
    libnoise/module/rotatepoint.h \
    libnoise/module/scalebias.h \
    libnoise/module/scalepoint.h \
    libnoise/module/select.h \
    libnoise/module/spheres.h \
    libnoise/module/terrace.h \
    libnoise/module/translatepoint.h \
    libnoise/module/turbulence.h \
    libnoise/module/voronoi.h \
    libnoise/win32/resource.h \
    libnoise/basictypes.h \
    libnoise/exception.h \
    libnoise/interp.h \
    libnoise/latlon.h \
    libnoise/mathconsts.h \
    libnoise/misc.h \
    libnoise/noise.h \
    libnoise/noisegen.h \
    libnoise/vectortable.h \
    ../../Users/Andreas Braun/Desktop/noiseutils/noiseutils.h \
    libnoise/noiseutils.h

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
    GraficsTextfiles/Fehler_in_CreatureTable.txt \
    libnoise/bin/libnoise.dll \
    libnoise/bin/libnoise.lib \
    libnoise.dll

FORMS += \
    biosim.ui

RESOURCES += \
    resources.qrc

