#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <iostream>

using namespace std;

void moveCharacter(Character &c, string direction);

void moveCharacterTeleporter (vector<string> &maze, Character &character, Param& param);

void eatBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft);

void eatBigBubble (Character &character, vector<string> &maze, size_t &bubbleLeft);

void bigBubbleDuration(map<string, Character> &mapCharact);

void changeState(Character &charact);

void changeEveryoneState(map<string, Character> &mapCharact, bool newValue);

void checkEating(map<string, Character> mapC, bool &gameRunning);

#endif // GAMELOGIC_H
