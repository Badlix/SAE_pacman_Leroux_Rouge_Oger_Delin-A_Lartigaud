#ifndef GHOST_INTELLIGENCE_H
#define GHOST_INTELLIGENCE_H
#include "constants.h"
#include <iostream>

/**
 * @brief check if a move is possible
 * @param ghost : Character
 * @param personality : string
 * @param difficulty : unsigned
 * @param maze : std::vector<std::string>
 * @param pacmanPos : Position
 * @param characters : std::map<std::string, Character>
 * @param characterList : std::vector<std::string>
 * @return true if the move is possible, if not return false
 * @fn bool isMovePossible(std::vector<std::string> &maze,Character &character, std::string direction)
 */
std::string decideGhostDirection(Character &ghost, std::string &personality, unsigned &difficulty, std::vector<std::string> maze, Position &pacmanPos, std::map<std::string, Character> &characters, std::vector<std::string> &characterList);

/**
 * @brief the main function of all the a* algorithm
 * @param maze : std::vector<std::string>
 * @param ghostPos : Position
 * @param pacmanPos : Position
 * @return the direction wich the ghost has to take
 * @fn std::string aStar(std::vector<std::string> &maze, Position &ghostPos, Position &pacmanPos)
 */
std::string aStar(std::vector<std::string> &maze, Position &ghostPos, Position &pacmanPos);

/**
 * @brief the core of the a* algorithm, used after all the initialization process
 * @param openNodes : std::map<Position, unsigned>
 * @param closedNodes : std::map<Position, Position>
 * @param pacmanPos : Position
 * @param maze : std::vector<std::string>
 * @param currentNode : Position
 * @fn void aStarAlgorithm(std::map<Position, unsigned> &openNodes, std::map<Position, Position> &closedNodes, Position &pacmanPos, std::vector<std::string> &maze, Position &currentNode)
 */
void aStarAlgorithm(std::map<Position, unsigned> &openNodes, std::map<Position, Position> &closedNodes, Position &pacmanPos, std::vector<std::string> &maze, Position &currentNode);

/**
 * @brief give a quality to a node, for the a* algorithm
 * @param currentPos : Position
 * @param pacmanPos : Position
 * @return the node's quality, judging by its distance to pacman. Lower is the value, higher is the quality.
 * @fn unsigned nodeQuality(Position &currentPos, Position &pacmanPos)
 */
unsigned nodeQuality(Position &currentPos, Position &pacmanPos);

/**
 * @brief get all the usable nodes from the maze, for the a* algorithm
 * @param maze : std::vector<std::string>
 * @return a std::vector of Position wich contains all the usable nodes from the maze
 * @fn std::vector<Position> getAllNodes(std::vector<std::string> &maze)
 */
std::vector<Position> getAllNodes(std::vector<std::string> &maze);

/**
 * @brief set the quality all the nodes, for a* algorithm
 * @param nodes : std::vector<Position>
 * @param openNodes : std::map<Position, unsigned>
 * @param pacmanPos : Position
 * @fn void setNodesQuality(std::vector<Position> &nodes, std::map<Position, unsigned> &openNodes, Position &pacmanPos)
 */
void setNodesQuality(std::vector<Position> &nodes, std::map<Position, unsigned> &openNodes, Position &pacmanPos);

/**
 * @brief chose the best direction judging by its quality
 * @param directions : std::vector<std::string>
 * @param openNodes : std::map<Position, unsigned>
 * @return return the index of the best direction to take
 * @fn unsigned bestDirection(std::vector<std::string> &directions, std::map<Position, unsigned> &openNodes)
 */
unsigned bestDirection(std::vector<std::string> &directions, std::map<Position, unsigned> &openNodes);

/**
 * @brief recursive function used to get up to the origin of the binary tree, used in a* algorithm
 * @param closedNodes : std::map<Position, Position>
 * @param currentNode : Position
 * @param ghostPos: Position
 * @return the first direction generatoed from the a* algorithm
 * @fn std::string firstDirection(std::map<Position, Position> closedNodes, Position &currentNode, Position &ghostPos)
 */
std::string firstDirection(std::map<Position, Position> closedNodes, Position &currentNode, Position &ghostPos);

std::string codePosition (Position &pos);

Position uncodePosition (std::string & str);

#endif // GHOST_INTELLIGENCE_H
