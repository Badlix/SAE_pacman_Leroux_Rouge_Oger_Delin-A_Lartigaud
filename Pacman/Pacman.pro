TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        functions.cpp \
        main.cpp

HEADERS += \
    functions.h \
    constants.h

DISTFILES += \
    settings.yaml

include(../MinGL/mingl.pri)
