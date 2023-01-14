#ifndef GENERAL_H
#define GENERAL_H
#include "mingl/mingl.h"
#include "param.h"
#include "constants.h"
#include <iostream>

// game control

void keyboardInput(MinGL &window, Param &param, Character &pacman, std::vector<std::string> &maze);

void gameOver(bool &gameRunning);

// general functions

/**
 * @brief give a random direction to go
 * @param pos : Position
 * @param maze : std::vector<std::string>
 * @return a random direction
 * @fn std::string randomDirection(Position &pos, std::vector<std::string> &maze)
 */
std::string randomDirection(Position &pos, std::vector<std::string> &maze);

/**
 * @brief give a random character
 * @param characters : map<std::string, Character>
 * @param characterList : std::vector<std::string>
 * @return a random character
 * @fn Character randomCharacter(map<std::string, Character> &characters, std::vector<std::string> &characterList)
 */
Character randomCharacter(std::map<std::string, Character> &characters, std::vector<std::string> &characterList);

/**
 * @brief give the position in wich the direction goes
 * @param direction : std::string
 * @param currentPos : Position
 * @return the Position in wich the direction goes
 * @fn Position nextMove(std::string &direction, Position &currentPos)
 */
Position nextMove(std::string &direction, Position &currentPos);

/**
 * @brief give all the possible directions from a given position
 * @param currentPos : Position
 * @param maze : std::vector<std::string>
 * @return the list of the possible directions
 * @fn std::vector<std::string> possibleDirections(Position &currentPos, std::vector<std::string> &maze)
 */
std::vector<std::string> possibleDirections(Position &currentPos, std::vector<std::string> &maze);

// get functions

/**
 * @brief give the direction used to go from the first position to the second
 * @param pos1 : Position
 * @param pos2 : Position
 * @return the direction used to go from the first position to the second
 * @fn std::string getDirection(Position &pos1, Position &pos2)
 */
std::string getDirection(Position &pos1, Position &pos2);

std::vector<Position> getPosTeleporter(Param &param);

Position getPosCage(Param &param);

// tests

void showMaze(const std::vector<std::string> &maze);

void showMap(std::map<std::string, Character> &myMap);

#endif // GENERAL_H
