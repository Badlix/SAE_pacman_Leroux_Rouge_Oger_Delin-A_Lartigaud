#ifndef ASSERTIVES_H
#define ASSERTIVES_H
#include "constants.h"
#include "param.h"
#include <iostream>

/**
 * @brief check if the ghost is in the cage
 * @param[in] posGhost : position of the ghost
 * @param param
 * @return bool
 * @fn bool isGhostInCage(Character ghost, Param &param)
 */
bool isGhostInCage(const Position &posGhost, Param &param);

/**
 * @brief check if there is at least one ghost in the cage
 * @param mapCharact
 * @param param
 * @return bool
 * @fn bool isThereAGhostInCage(map<string, Character> &mapCharact, Param &param)
 */
bool isThereAGhostInCage(std::map<std::string, Character> &mapCharact, Param &param);

/**
 * @brief check if a emplacement is free
 * @param pos : char
 * @return true if free, false if not
 * @fn bool isFree(char &pos)
 */
bool isFree(char &pos);

/**
 * @brief check if all bubbles have been eaten
 * @param bubbleLeft : number of bubble left
 * @param isGameRunning
 * @param isVictory
 * @fn void isBubbleLeft(size_t &bubbleLeft , bool &isGameRunning, bool &isVictory)
 */
void isBubbleLeft(size_t &bubbleLeft , bool &isGameRunning, bool &isVictory);

/**
 * @brief check if the character has the same position of a big bubble
 * @param character
 * @param maze
 * @param score
 * @return bool
 * @fn bool isBigBubble(Character &character, std::vector<std::string> &maze, unsigned &score)
 */
bool isBigBubble(Character &character, std::vector<std::string> &maze, unsigned &score);

/**
 * @brief check if the character has the same position of a bubble
 * @param character
 * @param maze
 * @param score
 * @return bool
 * @fn bool isBubble(Character &character, std::vector<std::string> &maze, unsigned &score)
 */
bool isBubble(Character &character, std::vector<std::string> &maze, unsigned &score);

/**
 * @brief check if a move is posssible
 * @param maze
 * @param character
 * @param direction
 * @return bool
 * @fn bool isMovePossible(std::vector<std::string> &maze,Character &character, std::string direction)
 */
bool isMovePossible(std::vector<std::string> &maze,Character &character, std::string direction);

/**
 * @brief check if the character has the same position of a teleporter
 * @param maze
 * @param character
 * @return bool
 * @fn bool isTeleporter(std::vector<std::string> &maze, Character &character)
 */
bool isTeleporter(std::vector<std::string> &maze, Character &character);

/**
 * @brief check if two character have the same position
 * @param first character
 * @param second character
 * @return bool
 * @fn bool isSamePos(Character &character1, Character &character2)
 */
bool isSamePos(Character &character1, Character &character2);

#endif // ASSERTIVES_H
