#include "constants.h"
#include "general.h"
#include "assertives.h"
#include <iostream>
#include "math.h"

using namespace std;

/**
* @brief This function calculates the node quality by using Manhattan distance between the current position and the pacman's position
* @param currentPos The current position of the ghost
* @param pacmanPos The current position of the pacman
* @return The node quality as the Manhattan distance between the current position and the pacman's position
*/
unsigned nodeQuality(Position &currentPos, Position &pacmanPos){
    return fabs(currentPos.x-pacmanPos.x) + fabs(currentPos.y-pacmanPos.y);
}

/**
* @brief Assign a quality value to all the nodes in the openNodes map
* @param nodes a vector of all the nodes in the map
* @param openNodes a map that contains all the nodes as keys and their quality as value
* @param pacmanPos the position of the pacman
* This function assigns a quality value to all the nodes in the openNodes map based on the distance between the node and the pacman.
* The quality value is the sum of the absolute differences between the x and y coordinates of the node and the pacman.
* The higher the quality, the farther the node is from the pacman.
*/
void setNodesQuality(vector<Position> &nodes, map<Position, unsigned> &openNodes, Position &pacmanPos){
    for (size_t i = 0 ; i < nodes.size() ; ++i) {
        openNodes.insert({nodes[i], nodeQuality(nodes[i], pacmanPos)});
    }
}

/**
@brief Get all nodes in the maze
@param maze The maze represented as a vector of strings
@return A vector of Position containing all the nodes in the maze
*/
vector<Position> getAllNodes(vector<string> &maze){
    vector<Position> nodes = {};
    for (size_t i = 0 ; i < maze.size() ; ++i) {
        for (size_t j = 0 ; j < maze.size() ; ++j) {
            if (isFree(maze[i][j])) nodes.push_back(Position{static_cast<int>(i), static_cast<int>(j)});
        }
    }
    return nodes;
}

/**
* @brief Find the best direction to move to next based on the quality of each node
* @param directions The available directions to move in
* @param openNodes A map containing the quality of each node
* @param currentPos The current position of the ghost
* @return unsigned The index of the best direction
*/
unsigned bestDirection(vector<string> &directions, map<Position, unsigned> &openNodes, Position &currentPos){
    unsigned bestIndex = 0;
    for (size_t i = 0 ; i < directions.size() ; ++i) {
        if (openNodes[nextMove(directions[i], currentPos)] > openNodes[nextMove(directions[bestIndex], currentPos)]) {
            bestIndex = i;
        }
    }
    return bestIndex;
}

/**
* @brief This function finds the first direction that the ghost needs to take to reach the Pacman
* @param closedNodes a map that contains the path that the ghost needs to take to reach the Pacman
* @param currentNode the current position of the ghost
* @param ghostPos the initial position of the ghost
* @return A string representing the first direction that the ghost needs to take.
*/
string firstDirection(map<string, string> closedNodes, Position &currentNode, Position &ghostPos){
    //Recursive algorithm used to browse the closedNodes map.

    //If the parrent of the current node (&currentNode) is the root (&ghostPos) of the closedNodes,
    if (uncodePosition(closedNodes.find(codePosition(currentNode))->second) == ghostPos) {
        //Then it is the end of the function.
        return getDirection(ghostPos, currentNode);
    }
    //If the parent of the current node isn't the root...
    else  {
        //The parent becomes the new current node.
        Position parentNode = uncodePosition(closedNodes[codePosition(currentNode)]);
        return firstDirection(closedNodes, parentNode, ghostPos);
    }
}

/**
* @brief This function is used to set the quality value of all the nodes in the openNodes map
* @param nodes a vector containing all the nodes of the maze
* @param openNodes a map containing all the nodes that the ghost can move to, and their quality value
* @param pacmanPos the current position of the pacman
*/
void aStarAlgorithm(map<Position, unsigned> &openNodes, map<Position, Position> &closedNodes, Position &pacmanPos, vector<string> &maze, Position &currentNode){
    Position tmpNode;
    vector<string> directions;
    Position move;
    while(currentNode != pacmanPos) {
        directions = possibleDirections(currentNode, maze);
        if (directions.size() == 0) {
            openNodes.erase(currentNode);
            tmpNode = closedNodes[currentNode];
            closedNodes.erase(currentNode);
            currentNode = closedNodes[tmpNode];
        }
        else {
            move = nextMove(directions[bestDirection(directions, openNodes, currentNode)], currentNode);
            closedNodes.insert({move, currentNode});
            currentNode = move;
        }
    }
}

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
string aStar(std::vector<string> &maze, Position &ghostPos, Position &pacmanPos){

    //Create all the used variables
    Position currentNode = ghostPos;
    map<string, unsigned> openNodes;
    map<string, string> closedNodes;

    //First, get the list of all the free positions in the maze.
    vector<Position> nodes = getAllNodes(maze);

    //Second, create the openNodes, wich attribute a quality to all the positions ; they become nodes.
    setNodesQuality(nodes, openNodes, pacmanPos);

    //Third, create the closedNodes, a tree wich has the &ghostPos as a root and &pacmanPos as it's final leef.
    aStarAlgorithm(openNodes, closedNodes, pacmanPos, maze, currentNode);

    //Finally, we browse the closedNodes from the leef up to the root,
    //to return the first movement our little ghost has to do in order to catch pacman !
    return firstDirection(closedNodes, currentNode, ghostPos);
}

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
string decideGhostDirection(Character &ghost, string &personality, unsigned &difficulty, vector<string> maze, Position &pacmanPos, map<string, Character> &characters, vector<string> &characterList) {
    unsigned aStarProba = difficulty*20;
    if(personality == "hardcore") aStarProba *= 1.5; //the hardcore personnality has higher chances to follow the a* algorithm
    if(rand()%100 <= aStarProba) return aStar(maze, ghost.pos, pacmanPos);
    else if (personality == "dumb" || personality == "hardcore") return randomDirection(ghost.pos, maze); //the dumb personnality, or the hardcore when failed, follow a random path
    else if (personality == "confused") { //the confused personnality sometime confuses pacman with another ghost or with a fruit...
        Character randomChar = randomCharacter(characters);
        return aStar(maze, ghost.pos, randomChar.pos);
    }
}
