#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include <vector>
#include <map>

#include "constants.h"
#include "param.h"

using namespace std;

// functions used for ghosts

bool isGhostInCage(Character ghost, Param &param);
Position getPosCage(Param &param);

// A* algorithm

/**
 * @brief give a quality to a node, for the a* algorithm
 * @param currentPos : Position
 * @param pacmanPos : Position
 * @return the node's quality, judging by its distance to pacman. Lower is the value, higher is the quality.
 * @fn unsigned nodeQuality(Position &currentPos, Position &pacmanPos)
 */
unsigned nodeQuality(Position &currentPos, Position &pacmanPos);

/**
 * @brief check if a emplacement is free
 * @param pos : char
 * @return true if free, false if not
 * @fn bool isFree(char &pos)
 */
bool isFree(char &pos);

/**
 * @brief get all the usable nodes from the maze, for the a* algorithm
 * @param maze : vector<string>
 * @return a vector of Position wich contains all the usable nodes from the maze
 * @fn vector<Position> getAllNodes(vector<string> &maze)
 */
vector<Position> getAllNodes(vector<string> &maze);

/**
 * @brief set the quality all the nodes, for a* algorithm
 * @param nodes : vector<Position>
 * @param openNodes : map<Position, unsigned>
 * @param pacmanPos : Position
 * @fn void setNodesQuality(vector<Position> &nodes, map<Position, unsigned> &openNodes, Position &pacmanPos)
 */
void setNodesQuality(vector<Position> &nodes, map<Position, unsigned> &openNodes, Position &pacmanPos);

/**
 * @brief give all the possible directions from a given position
 * @param currentPos : Position
 * @param maze : vector<string>
 * @return the list of the possible directions
 * @fn vector<string> possibleDirections(Position &currentPos, vector<string> &maze)
 */
vector<string> possibleDirections(Position &currentPos, vector<string> &maze);

/**
 * @brief chose the best direction judging by its quality
 * @param directions : vector<string>
 * @param openNodes : map<Position, unsigned>
 * @return return the index of the best direction to take
 * @fn unsigned bestDirection(vector<string> &directions, map<Position, unsigned> &openNodes)
 */
unsigned bestDirection(vector<string> &directions, map<Position, unsigned> &openNodes);

/**
 * @brief give the position in wich the direction goes
 * @param direction : string
 * @param currentPos : Position
 * @return the Position in wich the direction goes
 * @fn Position nextMove(string &direction, Position &currentPos)
 */
Position nextMove(string &direction, Position &currentPos);

/**
 * @brief the core of the a* algorithm, used after all the initialization process
 * @param openNodes : map<Position, unsigned>
 * @param closedNodes : map<Position, Position>
 * @param pacmanPos : Position
 * @param maze : vector<string>
 * @param currentNode : Position
 * @fn void aStarAlgorithm(map<Position, unsigned> &openNodes, map<Position, Position> &closedNodes, Position &pacmanPos, vector<string> &maze, Position &currentNode)
 */
void aStarAlgorithm(map<Position, unsigned> &openNodes, map<Position, Position> &closedNodes, Position &pacmanPos, vector<string> &maze, Position &currentNode);

/**
 * @brief give the direction used to go from the first position to the second
 * @param pos1 : Position
 * @param pos2 : Position
 * @return the direction used to go from the first position to the second
 * @fn string getDirection(Position &pos1, Position &pos2)
 */
string getDirection(Position &pos1, Position &pos2);

/**
 * @brief recursive function used to get up to the origin of the binary tree, used in a* algorithm
 * @param closedNodes : map<Position, Position>
 * @param currentNode : Position
 * @param ghostPos: Position
 * @return the first direction generatoed from the a* algorithm
 * @fn string firstDirection(map<Position, Position> closedNodes, Position &currentNode, Position &ghostPos)
 */
string firstDirection(map<Position, Position> closedNodes, Position &currentNode, Position &ghostPos);

/**
 * @brief the main function of all the a* algorithm
 * @param maze : vector<string>
 * @param ghostPos : Position
 * @param pacmanPos : Position
 * @return the direction wich the ghost has to take
 * @fn string aStar(vector<string> &maze, Position &ghostPos, Position &pacmanPos)
 */
string aStar(vector<string> &maze, Position &ghostPos, Position &pacmanPos);

/**
 * @brief give a random direction to go
 * @param pos : Position
 * @param maze : vector<string>
 * @return a random direction
 * @fn string randomDirection(Position &pos, vector<string> &maze)
 */
string randomDirection(Position &pos, vector<string> &maze);

/**
 * @brief give a random character
 * @param characters : map<string, Character>
 * @param characterList : vector<string>
 * @return a random character
 * @fn Character randomCharacter(map<string, Character> &characters, vector<string> &characterList)
 */
Character randomCharacter(map<string, Character> &characters, vector<string> &characterList);

/**
 * @brief check if a move is possible
 * @param ghost : Character
 * @param personality : string
 * @param difficulty : unsigned
 * @param maze : vector<string>
 * @param pacmanPos : Position
 * @param characters : map<string, Character>
 * @param characterList : vector<string>
 * @return true if the move is possible, if not return false
 * @fn bool isMovePossible(vector<string> &maze,Character &character, string direction)
 */
string decideGhostDirection(Character &ghost, string &personality, unsigned &difficulty, vector<string> maze, Position &pacmanPos, map<string, Character> &characters, vector<string> &characterList);

#endif // GHOST_H
