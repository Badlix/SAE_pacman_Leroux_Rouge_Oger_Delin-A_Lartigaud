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

unsigned nodeQuality(Position &currentPos, Position &pacmanPos){
    //Give the quality of a node.
    return sqrt((currentPos.x-pacmanPos.x)*(currentPos.x-pacmanPos.x)) + sqrt((currentPos.y-pacmanPos.y)*(currentPos.y-pacmanPos.y));
}

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
