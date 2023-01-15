#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "mingl/audio/audioengine.h"
#include "mingl/shape/rectangle.h"
#include "constants.h"
#include "param.h"
#include <iostream>

std::vector<std::string> initMaze(Param &param);

std::vector<nsShape::Rectangle> initWalls(std::vector<std::string> &maze);

std::map<std::string, Character> initCharacters(Param &param);

Skin initSkin(std::string type, std::string skinName);

PacmanMouth initPacmanmouth(Param &param);

size_t nbBubbleInMaze(std::vector<std::string> &maze);

void initPersonality (std::vector<std::string> &characterList, std::map<std::string, std::string> personalities, unsigned &difficulty);

void initMusicsEngine(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, nsAudio::AudioEngine &gameOverMusic);

#endif // INITIALIZATION_H
