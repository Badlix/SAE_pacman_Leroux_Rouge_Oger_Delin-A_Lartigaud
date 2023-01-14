#ifndef ASSERTIVES_H
#define ASSERTIVES_H
#include "constants.h"
#include "param.h"
#include <iostream>


/**
 * @brief check if the ghost is in the cage
 * @param[in] posGhost : position of the ghost
 * @param[in] param
 * @return bool
 * @fn bool isGhostInCage(Character ghost, Param &param)
 */
bool isGhostInCage(const Position posGhost, const Param &param);

/**
 * @brief check if a emplacement is free
 * @param pos : char
 * @return true if free, false if not
 * @fn bool isFree(char &pos)
 */
bool isFree(char &pos);

void isBubbleLeft(size_t &bubbleLeft , bool &gameRunning, bool &isVictory);

bool isBigBubble(Character &character, std::vector<std::string> &maze, unsigned &score);

bool isBubble(Character &character, std::vector<std::string> &maze, unsigned &score);

bool isMovePossible(std::vector<std::string> &maze,Character &character, std::string direction);

bool isTeleporter(std::vector<std::string> &maze,Character &character);

bool isSamePos(Character &c1, Character &c2);

#endif // ASSERTIVES_H
