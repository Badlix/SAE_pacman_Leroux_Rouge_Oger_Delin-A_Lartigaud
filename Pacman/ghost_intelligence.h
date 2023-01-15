#ifndef GHOST_INTELLIGENCE_H
#define GHOST_INTELLIGENCE_H
#include "constants.h"
#include <iostream>

/**
* @brief This function decide the next direction of the ghost, depending on its personality, the difficulty level and the current position of Pacman.
* @param ghost The ghost character
* @param personality The string that defines the personality of the ghost
* @param difficulty The unsigned integer that defines the difficulty level
* @param maze The vector of strings that represents the game's maze
* @param pacmanPos The position of Pacman
* @param characters The map that contains all the characters of the game
* @param characterList A vector of strings that contains all the characters' names
* @return A string that represents the next direction of the ghost
*/
std::string decideGhostDirection(Character &ghost, std::string &personality, unsigned &difficulty, std::vector<std::string> maze, Position &pacmanPos, std::map<std::string, Character> &characters, std::vector<std::string> &characterList);

/**
* @brief The function A* algorithm
* This function is used to calculate the best path for the ghost to catch the pacman using the A* algorithm.
* It takes in input the maze, the position of the ghost and the position of the pacman.
* The function returns the first move the ghost needs to do to catch the pacman.
* @param maze A vector of strings representing the maze
* @param ghostPos Position of the ghost in the maze
* @param pacmanPos Position of the pacman in the maze
* @return string The first move for the ghost to catch the pacman
*/
std::string aStar(std::vector<std::string> &maze, Position &ghostPos, Position &pacmanPos);

/**
* @brief This function is used to set the quality value of all the nodes in the openNodes map
* @param nodes a vector containing all the nodes of the maze
* @param openNodes a map containing all the nodes that the ghost can move to, and their quality value
* @param pacmanPos the current position of the pacman
*/
void aStarAlgorithm(std::map<std::string, unsigned> &openNodes, std::map<std::string, std::string> &closedNodes, Position &pacmanPos, std::vector<std::string> &maze, Position &currentNode);

/**
* @brief This function calculates the node quality by using Manhattan distance between the current position and the pacman's position
* @param currentPos The current position of the ghost
* @param pacmanPos The current position of the pacman
* @return The node quality as the Manhattan distance between the current position and the pacman's position
*/
unsigned nodeQuality(Position &currentPos, Position &pacmanPos);

/**
@brief Get all nodes in the maze
@param maze The maze represented as a vector of strings
@return A vector of Position containing all the nodes in the maze
*/
std::vector<Position> getAllNodes(std::vector<std::string> &maze);

/**
* @brief Assign a quality value to all the nodes in the openNodes map
* @param nodes a vector of all the nodes in the map
* @param openNodes a map that contains all the nodes as keys and their quality as value
* @param pacmanPos the position of the pacman
* This function assigns a quality value to all the nodes in the openNodes map based on the distance between the node and the pacman.
* The quality value is the sum of the absolute differences between the x and y coordinates of the node and the pacman.
* The higher the quality, the farther the node is from the pacman.
*/
void setNodesQuality(std::vector<Position> &nodes, std::map<std::string, unsigned> &openNodes, Position &pacmanPos);

/**
* @brief Find the best direction to move to next based on the quality of each node
* @param directions The available directions to move in
* @param openNodes A map containing the quality of each node
* @param currentPos The current position of the ghost
* @return unsigned The index of the best direction
*/
unsigned bestDirection(std::vector<std::string> &directions, std::map<std::string, unsigned> &openNodes);

/**
* @brief This function finds the first direction that the ghost needs to take to reach the Pacman
* @param closedNodes a map that contains the path that the ghost needs to take to reach the Pacman
* @param currentNode the current position of the ghost
* @param ghostPos the initial position of the ghost
* @return A string representing the first direction that the ghost needs to take.
*/
std::string firstDirection(std::map<std::string, std::string> closedNodes, Position &currentNode, Position &ghostPos);

/**
 * @brief convert a string to a Position
 * @param str "x,y"
 * @return Position(x,y)
 */
Position uncodePosition (std::string & str);

/**
 * @brief convert a Position to a string
 * @param Position(x, y)
 * @return "x,y"
 */
std::string codePosition (Position &pos);

#endif // GHOST_INTELLIGENCE_H
