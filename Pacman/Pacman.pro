TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        functions.cpp \
        main.cpp \
        param.cpp

HEADERS += \
    functions.h \
    param.h \
    constants.h

DISTFILES += \
    settings.yaml

include(../MinGL/mingl.pri)
