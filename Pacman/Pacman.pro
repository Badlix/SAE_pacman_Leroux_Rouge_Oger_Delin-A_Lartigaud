TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        functions.cpp \
        main.cpp \
        param.cpp \
    ghost.cpp

HEADERS += \
    functions.h \
    param.h \
    constants.h \
    ghost.h

DISTFILES += \
    settings.yaml
    skins/

include(../MinGL/mingl.pri)
