#include "constants.h"
#include "general.h"
#include "assertives.h"
#include <iostream>
#include "math.h"

using namespace std;

unsigned nodeQuality(Position &currentPos, Position &pacmanPos){
    return fabs(currentPos.x-pacmanPos.x) + fabs(currentPos.y-pacmanPos.y);
}

void setNodesQuality(vector<Position> &nodes, map<Position, unsigned> &openNodes, Position &pacmanPos){
    for (size_t i = 0 ; i < nodes.size() ; ++i) {
        openNodes.insert({nodes[i], nodeQuality(nodes[i], pacmanPos)});
    }
}

vector<Position> getAllNodes(vector<string> &maze){
    vector<Position> nodes = {};
    for (size_t i = 0 ; i < maze.size() ; ++i) {
        for (size_t j = 0 ; j < maze.size() ; ++j) {
            if (isFree(maze[i][j])) nodes.push_back(Position{static_cast<int>(i), static_cast<int>(j)});
        }
    }
    return nodes;
}

unsigned bestDirection(vector<string> &directions, map<Position, unsigned> &openNodes, Position &currentPos){
    unsigned bestIndex = 0;
    for (size_t i = 0 ; i < directions.size() ; ++i) {
        if (openNodes[nextMove(directions[i], currentPos)] > openNodes[nextMove(directions[bestIndex], currentPos)]) {
            bestIndex = i;
        }
    }
    return bestIndex;
}

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
