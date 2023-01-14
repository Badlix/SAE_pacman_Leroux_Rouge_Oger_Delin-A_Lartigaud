#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "mingl/audio/audioengine.h"
#include "constants.h"
#include "param.h"
#include <iostream>

/**
 * @brief change the position of a character depending a position
 * @param character
 * @param direction
 * @fn void moveCharacter(Character &c, std::string direction)
 */
void moveCharacter(Character &character, std::string direction);

/**
 * @brief teleport pacman
 * @param maze
 * @param character
 * @param param
 */
void moveCharacterTeleporter (std::vector<std::string> &maze, Character &Character, Param& param);

void eatBubble (const Character &character, std::vector<std::string> &maze, size_t &bubbleLeft, unsigned &score);

void eatBigBubble (Character &character, std::vector<std::string> &maze, size_t &bubbleLeft, unsigned &score);

void changeState(Character &charact);

void changeEveryoneState(std::map<std::string, Character> &mapCharact, bool newValue, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic);

void eatFruit(std::map<std::string, Character> &mapC, std::string fruitKey, unsigned &score);

void eatGhost(Param &param, Character &ghost, unsigned &score);

void checkEating(Param &param, std::map<std::string, Character> &mapC, bool &isGameRunning, unsigned &score, nsAudio::AudioEngine &audioEngine);

#endif // GAMELOGIC_H
