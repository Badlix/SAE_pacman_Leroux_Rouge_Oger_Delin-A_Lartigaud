/**
 * @file   assertives.cpp
 * @author  Mathieu Leroux, Elliot Lartigaud, Gabriel Rouge, Alexis Delain, Léo Oger
 * @date    Janvier 2023
 * @brief   all "is" functions
 **/

#include "constants.h"
#include "general.h"
#include <iostream>

using namespace std;


bool isGhostInCage(const Position &posGhost, Param &param) {
    if (posGhost == getPosCage(param)) {
        return true;
    }
    return false;
}

bool isEncouterGhostPacman(Character &ghost, Character &pacman) {
    if (ghost.direction == "up" && pacman.direction == "down" && ghost.pos == Position{pacman.pos.x, pacman.pos.y-1}) return true;
    if (ghost.direction == "down" && pacman.direction == "up" && ghost.pos == Position{pacman.pos.x, pacman.pos.y+1}) return true;
    if (ghost.direction == "right" && pacman.direction == "left" && ghost.pos == Position{pacman.pos.x-1, pacman.pos.y}) return true;
    if (ghost.direction == "left" && pacman.direction == "right" && ghost.pos == Position{pacman.pos.x+1, pacman.pos.y}) return true;
    return false;
}

bool isThereAGhostInCage(map<string, Character> &characterMap, Param &param) {
    for (auto it(characterMap.begin()) ; it != characterMap.end() ; ++it) {
        if (isGhostInCage(it->second.pos, param)) return true;
    }
    return false;
}

bool isFree(char &pos){
    if (pos != '#' && pos != '-' && pos != '=') return true;
    else return false;
}

bool isBubble (Position pos, vector<string> &maze){
    if(maze[pos.y][pos.x] == '.') return true;
    else return false;
}

bool isBigBubble (Position pos, vector<string> &maze){
    if(maze[pos.y][pos.x] == 'o') return true;
    else return false;
}

void isBubbleLeft (unsigned &bubbleLeft , bool &isGameRunning, bool &isVictory) {
    if (bubbleLeft == 0){
        gameOver(isGameRunning);
        isVictory = true;
    }
}

bool isMovePossible(vector<string> &maze,Character &character, string direction) {
    // check if the player is going to leave the maze
    if (direction == "up" && character.pos.y <= 0) return false;
    else if (direction == "down" && character.pos.y >= maze.size()-1) return false;
    else if (direction == "left" && character.pos.x <= 0) return false;
    else if (direction == "right" && character.pos.x >= maze[0].size()-1) return false;

    // check if the next position is a wall
    else if ((direction == "up") && (maze[character.pos.y-1][character.pos.x] != '#' && (maze[character.pos.y-1][character.pos.x] != '-' ))) return true;
    else if ((direction == "down") && (maze[character.pos.y+1][character.pos.x] != '#' && (maze[character.pos.y+1][character.pos.x] != '-' ))) return true;
    else if ((direction == "left") && (maze[character.pos.y][character.pos.x-1] != '#' && (maze[character.pos.y][character.pos.x-1] != '-' ))) return true;
    else if ((direction == "right") && (maze[character.pos.y][character.pos.x+1] != '#' && (maze[character.pos.y][character.pos.x+1] != '-' ))) return true;
    else return false;
}

bool isTeleporter(vector<string> &maze, Character & character) {
    //checking if the player is on a teleporter. If yes, it check if the player is taking the teleporter from the right way.
    if ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "up" && isMovePossible(maze, character, "down")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "down" && isMovePossible(maze, character, "up")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "right" && isMovePossible(maze, character, "left")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "left" && isMovePossible(maze, character, "right")) return true;
    else return false;
}

bool isSamePos(Character &character1, Character &character2) {
    if (character1.pos == character2.pos) return true;
    else return false;
}
