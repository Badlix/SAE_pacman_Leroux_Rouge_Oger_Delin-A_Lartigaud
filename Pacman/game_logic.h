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
 * @fn void moveCharacterTeleporter (std::vector<std::string> &maze, Character &Character, Param& param)
 */
void moveCharacterTeleporter(std::vector<std::string> &maze, Character &character, Param& param);

/**
 * @brief free a ghost after a certain delay if there is one in the cage
 * @param mapCharact
 * @param jailGhostDuration : unsigned used as a timer
 * @param param
 * @fn void letGhostOut(std::map<std::string, Character> &mapCharact, unsigned &jailGhostDuration, Param &param)
 */
void letGhostOut(std::map<std::string, Character> &mapCharact, unsigned &jailGhostDuration, Param &param);

/**
 * @brief eat a bubble
 * @param[in] character
 * @param maze
 * @param bubbleLeft : number of bubble not eaten
 * @param score
 * @fn void eatBubble (const Character &character, std::vector<std::string> &maze, size_t &bubbleLeft, unsigned &score)
 */
void eatBubble(const Character &character, std::vector<std::string> &maze, size_t &bubbleLeft, unsigned &score);

/**
 * @brief eatBigBubble
 * @param[in] character
 * @param maze
 * @param bubbleLeft : number of bubble not eaten
 * @param score
 * @fn void eatBigBubble(const Character &character, std::vector<std::string> &maze, size_t &bubbleLeft, unsigned &score)
 */
void eatBigBubble(const Character &character, std::vector<std::string> &maze, size_t &bubbleLeft, unsigned &score);

/**
 * @brief change the state of a character
 * @param charact
 * @fn void changeState(Character &charact)
 */
void changeState(Character &charact);

/**
 * @brief change everyone state
 * @param mapCharact
 * @param newValue : new value to assign to the value isDefaultState of all characters
 * @param defaultMusic
 * @param madMusic
 * @fn void changeEveryoneState(std::map<std::string, Character> &mapCharact, bool newValue, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic)
 */
void changeEveryoneState(std::map<std::string, Character> &mapCharact, bool newValue, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic);

/**
 * @brief pacman eat a fruit
 * @param mapC
 * @param fruitKey : name of fruit which is the key of the fruit in mapC
 * @param score
 * @fn void eatFruit(std::map<std::string, Character> &mapC, std::string fruitKey, unsigned &score)
 */
void eatFruit(std::map<std::string, Character> &mapC, std::string fruitKey, unsigned &score);

/**
 * @brief ghost goes back to the cage and defaultState
 * @param param
 * @param ghost
 * @param score
 * @fn void eatGhost(Param &param, Character &ghost, unsigned &score);
 */
void eatGhost(Param &param, Character &ghost, unsigned &score);

/**
 * @brief check if a character is eating an another one
 * @param param
 * @param mapC
 * @param isGameRunning
 * @param score
 * @param audioEngine
 * @fn void checkEating(Param &param, std::map<std::string, Character> &mapC, bool &isGameRunning, unsigned &score, nsAudio::AudioEngine &audioEngine)
 */
void checkEating(Param &param, std::map<std::string, Character> &mapC, bool &isGameRunning, unsigned &score, nsAudio::AudioEngine &audioEngine);

#endif // GAMELOGIC_H
