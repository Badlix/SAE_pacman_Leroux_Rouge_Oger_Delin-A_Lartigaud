#ifndef GENERAL_H
#define GENERAL_H
#include "mingl/mingl.h"
#include "param.h"
#include "constants.h"
#include <iostream>

// game control

/**
 * @brief check the keyboard input and move the character is possible
 * @param window
 * @param param
 * @param pacman
 * @param maze
 * @fn void keyboardInput(MinGL &window, Param &param, Character &pacman, std::vector<std::string> &maze)
 */
void keyboardInput(MinGL &window, Param &param, Character &pacman, std::vector<std::string> &maze);

/**
 * @brief end the game by setting isGameRuuning to false
 * @param isGameRunning
 */
void gameOver(bool &isGameRunning);

// general functions

/**
 * @brief give a random direction to go
 * @param pos : position of a character
 * @param maze
 * @return a random direction
 * @fn std::string randomDirection(Position &pos, std::vector<std::string> &maze)
 */
std::string randomDirection(Position &pos, std::vector<std::string> &maze);

/**
 * @brief give a random character
 * @param characters
 * @param characterList
 * @return a random character
 * @fn Character randomCharacter(map<std::string, Character> &characters, std::vector<std::string> &characterList)
 */
Character randomCharacter(std::map<std::string, Character> &characters, std::vector<std::string> &characterList);

/**
 * @brief give the position in wich the direction goes
 * @param direction
 * @param currentPos
 * @return the Position in wich the direction goes
 * @fn Position nextMove(std::string &direction, Position &currentPos)
 */
Position nextMove(std::string &direction, Position &currentPos);

/**
 * @brief give all the possible directions from a given position
 * @param currentPos
 * @param maze
 * @return the list of the possible directions
 * @fn std::vector<std::string> possibleDirections(Position &currentPos, std::vector<std::string> &maze)
 */
std::vector<std::string> possibleDirections(Position &currentPos, std::vector<std::string> &maze);

// get functions

/**
 * @brief give the direction used to go from the first position to the second
 * @param pos1 : first position
 * @param pos2 : second position
 * @return the direction used to go from the first position to the second
 * @fn std::string getDirection(Position &pos1, Position &pos2)
 */
std::string getDirection(Position &pos1, Position &pos2);

/**
 * @brief get the position of the two teleporter depending of the maze
 * @param param
 * @return the two position of the two teleporter
 * @fn std::vector<Position> getPosTeleporter(Param &param)
 */
std::vector<Position> getPosTeleporter(Param &param);

/**
 * @brief get the position of the ghost cage depending on the maze
 * @param param
 * @return position of the middle of the ghost cage
 * @fn Position getPosCage(Param &param)
 */
Position getPosCage(Param &param);

// tests

/**
 * @brief show the maze
 * @param[in] maze
 * @fn void showMaze(const std::vector<std::string> &maze);
 */
void showMaze(const std::vector<std::string> &maze);

/**
 * @brief show a map of character
 * @param[in] myMap
 * @fn void showMap(const std::map<std::string, Character> &myMap)
 */
void showMap(const std::map<std::string, Character> &myMap);

#endif // GENERAL_H
