TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    param.cpp \
    game_logic.cpp \
    general.cpp \
    initialization.cpp \
    draw.cpp \
    ghost_intelligence.cpp \
    assertives.cpp

HEADERS += \
    param.h \
    constants.h \
    game_logic.h \
    general.h \
    initialization.h \
    draw.h \
    ghost_intelligence.h \
    assertives.h

DISTFILES += \
    settings.yaml
    skins/
    audio/

include(../MinGL/mingl.pri)
