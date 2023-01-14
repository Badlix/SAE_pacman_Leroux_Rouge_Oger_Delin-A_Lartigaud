TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(../../mingl.pri)
include(../07-Audio/res/music.wav)
include(../07-Audio/res/sound1.wav)
include(../07-Audio/res/sound2.wav)

SOURCES += \
        main.cpp
