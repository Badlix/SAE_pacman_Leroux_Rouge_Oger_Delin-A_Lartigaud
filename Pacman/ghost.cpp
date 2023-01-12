#include "constants.h"
#include "param.h"
#include "ghost.h"
#include <iostream>
#include <map>
#include <vector>
#include <math.h>

using namespace std;

// ---------- Funtions used for ghosts ---------- //

bool isGhostInCage(Character ghost, Param &param) {
    if (ghost.pos == getPosCage(param)) {
        return true;
    }
    return false;
}

Position getPosCage(Param &param) {
    if (param.skins["Maze"] == 1) return {20, 3};
    else if (param.skins["Maze"] == 2) return {15, 7};
   return {0,0};
}

// ---------- A* algorithm---------- //

unsigned nodeQuality(Position &currentPos, Position &pacmanPos){
    return fabs(currentPos.x-pacmanPos.x) + fabs(currentPos.y-pacmanPos.y);
}

bool isFree(char &pos){
    if (pos != '#' && pos != '-' && pos != '~') return true;
    else return false;
}
vector<Position> getAllNodes(vector<string> &maze){
    vector<Position> nodes;
    for (size_t i = 0 ; i < maze.size() ; ++i) {
        for (size_t j = 0 ; j < maze.size() ; ++j) {
            if (isFree(maze[i][j])) nodes.push_back(Position{static_cast<int>(i), static_cast<int>(j)});
        }
    }
    return nodes;
}
void setNodesQuality(vector<Position> &nodes, map<Position, unsigned> &openNodes, Position &pacmanPos){
    for (size_t i = 0 ; i < nodes.size() ; ++i) {
        openNodes.insert({nodes[i], nodeQuality(nodes[i], pacmanPos)});
    }
}
vector<string> possibleDirections(Position &currentPos, vector<string> &maze){
    vector<string> directions;
    if ( isFree(maze[currentPos.y-1][currentPos.x]) ) directions.push_back("up");
    if ( isFree(maze[currentPos.y+1][currentPos.x]) ) directions.push_back("down");
    if ( isFree(maze[currentPos.y][currentPos.x-1]) ) directions.push_back("left");
    if ( isFree(maze[currentPos.y][currentPos.x+1]) ) directions.push_back("right");
    return directions;
}

Position nextMove(string &direction, Position &currentPos){
    if (direction == "up") return Position{currentPos.x, currentPos.y-1};
    else if (direction == "down") return Position{currentPos.x, currentPos.y+1};
    else if (direction == "left") return Position{currentPos.x-1, currentPos.y};
    else return Position{currentPos.x+1, currentPos.y}; //if (direction == "right")
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

string getDirection(Position &pos1, Position &pos2){
    if ( pos1.x-1 == pos2.x && pos1.y == pos2.y ) return "up";
    else if ( pos1.x+1 == pos2.x && pos1.y == pos2.y ) return "down";
    else if ( pos1.x == pos2.x && pos1.y-1 == pos2.y ) return "left";
    else return "right"; //if ( pos1.x == pos2.x && pos1.y+1 == pos2.y )
}
string firstDirection(map<Position, Position> closedNodes, Position &currentNode, Position &ghostPos){
    if (closedNodes[currentNode] == ghostPos) return getDirection(ghostPos, currentNode);
    else return firstDirection(closedNodes, closedNodes[currentNode], ghostPos);
}
string aStar(vector<string> &maze, Position &ghostPos, Position &pacmanPos){
    Position currentNode = ghostPos;
    map<Position, unsigned> openNodes;
    map<Position, Position> closedNodes;
    vector<Position> nodes = getAllNodes(maze);
    setNodesQuality(nodes, openNodes, pacmanPos);
    aStarAlgorithm(openNodes, closedNodes, pacmanPos, maze, currentNode);
    return firstDirection(closedNodes, currentNode, ghostPos);
}

string randomDirection(Position &pos, vector<string> &maze){
    vector<string> directions = possibleDirections(pos, maze);
    return directions[(rand()%directions.size())-1];
}

Character randomCharacter(map<string, Character> &characters, vector<string> &characterList) {
    return characters[characterList[rand()%characterList.size()-1]];
}

string decideGhostDirection(Character &ghost, string &personality, unsigned &difficulty, vector<string> maze, Position &pacmanPos, map<string, Character> &characters, vector<string> &characterList) {
    unsigned aStarProba = difficulty*20;
    if(personality == "hardcore") aStarProba *= 1.5; //the hardcore personnality has higher chances to follow the a* algorithm
    if(rand()%100 <= aStarProba) return aStar(maze, ghost.pos, pacmanPos);
    else if (personality == "dumb" || personality == "hardcore") return randomDirection(ghost.pos, maze); //the dumb personnality, or the hardcore when failed, follow a random path
    else if (personality == "confused") { //the confused personnality sometime confuses pacman with another ghost or with a fruit...
        Character randomChar = randomCharacter(characters, characterList);
        return aStar(maze, ghost.pos, randomChar.pos);
    }
}

void initPersonality (vector<string> &characterList, map<string, string> personalities, unsigned &difficulty) {
    //Each personnality has a level of difficulty.
    //The chances of it to drop are in percentage.

    //Initialization of the personalities
    vector<string> easyPersonality {"dumb"};
    vector<string> normalPersonality {"confused"};
    vector<string> hardPersonality {"hardcore"};

    //Initialization of the droprate of each level of difficulty :
    unsigned easy = 100 - 30*difficulty;
    unsigned hard = 30 * difficulty - 20;
    unsigned normal = 100 - easy - hard ;

    //Application of a random personality to each characters
    unsigned random;
    string personality;
    for (size_t i = 0 ; i < characterList.size() ; ++i) {
        random = rand()%100;
        if (random <= easy) {
            personality = easyPersonality[(rand()%easyPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
        else if (random <= easy+normal){
            personality = normalPersonality[(rand()%normalPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
        else {
            personality = hardPersonality[(rand()%hardPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
    }
}
