#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "constants.h"
#include "param.h"
#include <iostream>

void moveCharacter(Character &c, std::string direction);

void moveCharacterTeleporter (std::vector<std::string> &maze, Character &character, Param& param);

void eatBubble (const Character &character, std::vector<std::string> &maze, size_t &bubbleLeft);

void eatBigBubble (Character &character, std::vector<std::string> &maze, size_t &bubbleLeft);

void changeState(Character &charact);

void changeEveryoneState(map<std::string, Character> &mapCharact, bool newValue);

void checkEating(map<std::string, Character> mapC, bool &gameRunning);

#endif // GAMELOGIC_H
