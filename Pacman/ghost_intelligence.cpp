#include "constants.h"
#include "assertives.h"
#include "general.h"
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string codePosition (Position &pos) {
    //Code a Position to make it a string.
    string codex, codey;
    unsigned x = pos.x;
    unsigned y = pos.y;
    codex = to_string(x);
    codey = to_string(y);
    return codex + "," + codey ;
}

Position uncodePosition (string & str) {
    //Uncode a string to make it a Position.
    string x, y = "";
    unsigned valx, valy;

    //Separe the string in two strings using the coma as a separator
    unsigned i = 0;
    while (true) {
        if ( str[i] == ',') break;
        x += str[i];
        i+=1;
    }
    i += 1;
    while (true) {
        if ( i == str.size() ) break;
        y += str[i];
        i+=1;
    }


    valx = stoul(x);
    valy = stoul(y);
    return Position {valx, valy};
}

/**
* @brief This function calculates the node quality by using Manhattan distance between the current position and the pacman's position
* @param currentPos The current position of the ghost
* @param pacmanPos The current position of the pacman
* @return The node quality as the Manhattan distance between the current position and the pacman's position
*/
unsigned nodeQuality(Position &currentPos, Position &pacmanPos){
    //Give the quality of a node.
    return sqrt((currentPos.x-pacmanPos.x)*(currentPos.x-pacmanPos.x)) + sqrt((currentPos.y-pacmanPos.y)*(currentPos.y-pacmanPos.y));
}

/**
@brief Get all nodes in the maze
@param maze The maze represented as a vector of strings
@return A vector of Position containing all the nodes in the maze
*/
vector<Position> getAllNodes(vector<string> &maze){
    //Get all the free Positions from the maze in order to make them nodes in the openNodes map.
    vector<Position> nodes = {};
    for (unsigned i(0) ; i < maze.size() ; ++i) {
        for (unsigned j(0) ; j < maze[i].size() ; ++j) {
            if (isFree(maze[i][j])) nodes.push_back(Position{j, i});
        }
    }
    return nodes;
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
void setNodesQuality(vector<Position> &nodes, map<string, unsigned> &openNodes, Position &pacmanPos){
    //Set the quality of all the nodes (&nodes) judging by their distance to pacman (&pacmanPos).
    //The results are in &openNodes.
    Position tmp, temp;
    for (size_t i = 0 ; i < nodes.size() ; ++i) {
        tmp = nodes[i];
        temp = Position{tmp.x, tmp.y};
        openNodes.insert( {codePosition(temp), nodeQuality(nodes[i], pacmanPos) } );
    }
}

/**
* @brief Find the best direction to move to next based on the quality of each node
* @param directions The available directions to move in
* @param openNodes A map containing the quality of each node
* @param currentPos The current position of the ghost
* @return unsigned The index of the best direction
*/
unsigned bestDirection(vector<string> &directions, map<string, unsigned> &openNodes, Position &currentPos){
    //Chose the best direction judging by its quality (from the openNodes map) among the directions list.

    //We first chose an arbitrary bestIndex (wich indicates the index of the best direction)
    unsigned bestIndex = 0;

    unsigned qualIndex, qualBestIndex ;
    string tmp;
    Position tmpPos;

    //Let's test all the directions...
    for (size_t i = 1 ; i < directions.size() ; ++i) {

        //Get the quality from the next Position, going with the tested direction
        tmpPos = nextMove(directions[i], currentPos);
        tmp = codePosition(tmpPos);
        qualIndex = openNodes.find(tmp)->second;

        //Get the quality from the next Position, going with the actual bestIndex
        tmpPos = nextMove(directions[bestIndex], currentPos);
        tmp = codePosition(tmpPos);
        qualBestIndex = openNodes.find(tmp)->second;

        cout << "qualIndex : " << qualIndex << "   qualBestIndex : " << qualBestIndex << endl ;
        //If the tested direction is better...
        if (qualIndex < qualBestIndex) {
            //Make it the new bestIndex.
            bestIndex = i;
        }
    }
    return bestIndex;
}

vector<string> remove(vector<string> &V, string &rm) {
    //Remove a given string from a vector of string
    vector<string> res;
    for ( size_t i = 0 ; i < V.size() ; ++i) {
        if (V[i] != rm) res.push_back(V[i]);
    }
    return res;
}


/**
* @brief This function is used to set the quality value of all the nodes in the openNodes map
* @param nodes a vector containing all the nodes of the maze
* @param openNodes a map containing all the nodes that the ghost can move to, and their quality value
* @param pacmanPos the current position of the pacman
*/
void aStarAlgorithm(map<string, unsigned> &openNodes, map<string, string> &closedNodes, Position &pacmanPos, vector<string> &maze, Position &currentNode){
    vector<string> directions;
    Position move {};
    string tmp;
    Position tmpPos;
    unsigned iteration = 0;
    while(currentNode!= pacmanPos) {
        //In case of a loop bug...
        if (iteration >= 50)  break;

        //get all the possible directions from the current Node
        directions = possibleDirections(currentNode, maze);

        //take out the directions wich takes to an already-visited Position
        for (size_t i = 0 ; i < directions.size() ; ++i ) {
            tmpPos = nextMove(directions[i], currentNode);
            tmp = codePosition(tmpPos);
            if ( closedNodes.count(tmp) >= 1 ) directions = remove(directions, directions[i]);
            for (auto it=closedNodes.begin(); it!=closedNodes.end(); it++){
                tmp = it->second;
                if ( tmp == directions[i] ) directions = remove(directions, directions[i]);
            }
        }

        //If there is no directions possibilities :
        if (directions.size() == 0) {
            //Go back to the currentNode's parent
            currentNode = uncodePosition(closedNodes[codePosition(currentNode)]);
        }

        //If there is any direction possibilities :
        else {
            //Chose the best direction,
            move = nextMove(directions[bestDirection(directions, openNodes, currentNode)], currentNode);
            //go to the position...
            if (codePosition(move) != closedNodes[codePosition(currentNode)])closedNodes.insert({codePosition(move), codePosition(currentNode)});
            //And it becomes the new current node.
            currentNode = move;
        }
        iteration += 1;
    }
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
* @brief The function A* algorithm
* This function is used to calculate the best path for the ghost to catch the pacman using the A* algorithm.
* It takes in input the maze, the position of the ghost and the position of the pacman.
* The function returns the first move the ghost needs to do to catch the pacman.
* @param maze A vector of strings representing the maze
* @param ghostPos Position of the ghost in the maze
* @param pacmanPos Position of the pacman in the maze
* @return string The first move for the ghost to catch the pacman
*/
string aStar(vector<string> &maze, Position &ghostPos, Position &pacmanPos){

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
