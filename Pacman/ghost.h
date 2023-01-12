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

unsigned nodeQuality(Position &currentPos, Position &pacmanPos);
bool isFree(char &pos);
vector<Position> getAllNodes(vector<string> &maze);
void setNodesQuality(vector<Position> &nodes, map<Position, unsigned> &openNodes, Position &pacmanPos);
vector<string> possibleMoves(Position &currentPos, vector<string> &maze);
unsigned bestMove(vector<string> &directions, map<Position, unsigned> &openNodes);
Position nextMove(string &direction, Position &currentPos);
void aStarAlgorithm(map<Position, unsigned> &openNodes, map<Position, Position> &closedNodes, Position &pacmanPos, vector<string> &maze, Position &currentNode);
string getDirection(Position &pos1, Position &pos2);
string firstDirection(map<Position, Position> closedNodes, Position &currentNode, Position &ghostPos);
string aStar(vector<string> &maze, Position &ghost, Position &pacman);
string randomDirection(Character &character, vector<string> &maze);
Character randomCharacter(map<string, Character> &characters, vector<string> &characterList);
string decideGhostDirection(Character &ghost, string &personality, unsigned &difficulty, vector<string> maze, Position &pacmanPos, map<string, Character> &characters, vector<string> &characterList);

#endif // GHOST_H
