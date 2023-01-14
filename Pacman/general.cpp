#include "mingl/mingl.h"
#include "param.h"
#include "constants.h"
#include "game_logic.h"
#include "assertives.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

// ---------- Game Control ---------- //


void keyboardInput(MinGL &window, Param &param, Character &pacman, vector<string> &maze){
    // called inbetween every transition
    // allows to press many directions simultanuously without causing errors and fluidify the movements and the ergonomy
    if(window.isPressed({param.moveKeys["KeyUp"], false}) && pacman.direction != "up" && (isMovePossible(maze,pacman, "up"))) {
            moveCharacter(pacman, "up");
    }
    else if(window.isPressed({param.moveKeys["KeyRight"], false}) && pacman.direction != "right" && (isMovePossible(maze,pacman, "right"))) {
            moveCharacter(pacman, "right");
    }
    else if(window.isPressed({param.moveKeys["KeyDown"], false}) && pacman.direction != "down" && (isMovePossible(maze,pacman, "down"))) {
            moveCharacter(pacman, "down");
    }
    else if(window.isPressed({param.moveKeys["KeyLeft"], false}) && pacman.direction != "left" && (isMovePossible(maze,pacman, "left"))) {
            moveCharacter(pacman, "left");
    }
    else if (isMovePossible(maze,pacman, pacman.direction)){
            moveCharacter(pacman, pacman.direction);// continue in the same direction
    }
}

void gameOver(bool &isisisGameRunning) {
    isisisGameRunning = false;
}


// ---------- General Functions ---------- //


vector<string> possibleDirections(Position &currentPos, vector<string> &maze){
    vector<string> directions = {};
    if (isFree(maze[currentPos.y-1][currentPos.x])) directions.push_back("up");
    if (isFree(maze[currentPos.y+1][currentPos.x])) directions.push_back("down");
    if (isFree(maze[currentPos.y][currentPos.x-1])) directions.push_back("left");
    if (isFree(maze[currentPos.y][currentPos.x+1])) directions.push_back("right");
    return directions;
}

string randomDirection(Position &pos, vector<string> &maze){
    vector<string> directions = possibleDirections(pos, maze);
    return directions[rand()%(directions.size())];
    // rand between [0, directions.size()-1]
}

Character randomCharacter(map<string, Character> &characters, vector<string> &characterList) {
    return characters[characterList[rand()%characterList.size()]];
}

Position nextMove(string &direction, Position &currentPos){
    if (direction == "up") return Position{currentPos.x, currentPos.y-1};
    else if (direction == "down") return Position{currentPos.x, currentPos.y+1};
    else if (direction == "left") return Position{currentPos.x-1, currentPos.y};
    else return Position{currentPos.x+1, currentPos.y}; //if (direction == "right")
}

string getDirection(Position &pos1, Position &pos2){
    if ( pos1.x-1 == pos2.x && pos1.y == pos2.y ) return "up";
    else if ( pos1.x+1 == pos2.x && pos1.y == pos2.y ) return "down";
    else if ( pos1.x == pos2.x && pos1.y-1 == pos2.y ) return "left";
    else return "right"; //if ( pos1.x == pos2.x && pos1.y+1 == pos2.y )
}

vector<Position> getPosTeleporter(Param &param) {
    if (param.skins["Maze"] == 1) {
        return {{11,0}, {11,11}};
    } else if (param.skins["Maze"] == 2) {
        return {{0,5},{22,5}}; // take the position of the two teleporter on the first map
    }
    return {{0,0}, {0,0}};
}

Position getPosCage(Param &param) {
    if (param.skins["Maze"] == 1) return {20, 3};
    else if (param.skins["Maze"] == 2) return {15, 7};
   return {0,0};
}


// ---------- Functions used for tests ---------- //

void tmpMoveGhost(std::vector<std::string> &maze, map<std::string, Character> &characterMap, Param &param) {
    for (auto it (characterMap.begin()) ; it != characterMap.end() ; ++it) {
        if (it->second.type == "Ghost") {
            if (it->second.type == "Ghost" && it->second.pos == getPosCage(param)) continue;
            it->second.direction = randomDirection(it->second.pos, maze);
            moveCharacter(it->second, it->second.direction);
        }
    }
}

void showMap(const std::map<string, Character> &myMap) {
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        cout << it->first << " -> ";
        cout << " pos.x : " << it->second.pos.x;
        cout << "  |  pos.y : " << it->second.pos.y;
        cout << "  |  direction : " << it->second.direction;
        cout << "  |  isDefaultState : " << it->second.isDefaultState << endl;
    }
}

void showMaze(const vector<string> & maze) {
    for (const string &line : maze) {
        for (char c : line) {
            cout << c << ' ';
        }
        cout << endl;
    }
}

