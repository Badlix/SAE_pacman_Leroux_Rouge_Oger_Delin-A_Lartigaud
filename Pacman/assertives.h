#ifndef ASSERTIVES_H
#define ASSERTIVES_H
#include "constants.h"
#include "param.h"
#include <iostream>

/**
* @brief A function that checks if a ghost is currently in its cage
* @param posGhost The current position of the ghost
* @param param A struct containing the game's parameters
* @return true if the ghost is in its cage, false otherwise
*/
bool isGhostInCage(const Position &posGhost, Param &param);

/**
* @brief A function that checks if the pacman and a ghost have encountered each other
* @param ghost The ghost character
* @param pacman The pacman character
* @return true if the pacman and ghost have encountered each other, false otherwise
*/
bool isEncouterGhostPacman(Character &ghost, Character &pacman);

/**
* @brief A function that checks if there is a ghost currently in its cage
* @param mapCharact A map containing all the characters of the game
* @param param A struct containing the game's parameters
* @return true if there is a ghost in its cage, false otherwise
*/
bool isThereAGhostInCage(std::map<std::string, Character> &characterMap, Param &param);

/**
* @brief A function that checks if a given position is free
* @param pos A character representing the position on the maze
* @return true if the position is free, false otherwise
*/
bool isFree(char &pos);

/**
* @brief A function that checks if all the bubbles have been eaten and sets the game state accordingly
* @param bubbleLeft The number of bubbles left in the maze
* @param isGameRunning A flag indicating if the game is running
* @param isVictory A flag indicating if the player has won
*/
void isBubbleLeft(unsigned &bubbleLeft , bool &isGameRunning, bool &isVictory);

/**
* @brief A function that checks if the pacman is currently on a big bubble
* @param character The character object representing Pacman
* @param maze The game's maze
* @return true if the pacman is on a big bubble, false otherwise
*/
bool isBigBubble(Position pos, std::vector<std::string> &maze);

/**
* @brief A function that checks if the pacman is currently on a bubble
* @param character The character object representing Pacman
* @param maze The game's maze
* @return true if the pacman is on a bubble, false otherwise
*/
bool isBubble(Position pos, std::vector<std::string> &maze);

/**
* @brief A function that checks if a move is possible
* @param maze The game's maze
* @param character The character object representing Pacman
* @param direction The direction in which the character wants to move
* @return true if the move is possible, false otherwise
*/
bool isMovePossible(std::vector<std::string> &maze, Character &character, std::string direction);

/**
* @brief A function that checks if a character is on a teleporter
* @param maze The game's maze
* @param character The character object representing Pacman
* @return true if the character is on a teleporter and is moving towards it, false otherwise
*/
bool isTeleporter(std::vector<std::string> &maze, Character &character);

/**
* @brief A function that checks if two characters have the same position
* @param character1 The first character object
* @param character2 The second character object
* @return true if the two characters have the same position, false otherwise
*/
bool isSamePos(Character &character1, Character &character2);

#endif // ASSERTIVES_H
