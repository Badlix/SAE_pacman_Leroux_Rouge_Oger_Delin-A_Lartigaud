#include "functions.h"
#include "param.h"
#include "constants.h"
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include "mingl/mingl.h"
#include "mingl/transition/transition_engine.h"
#include <math.h>

using namespace std;
using namespace nsTransition;
using namespace nsGraphics;
using namespace nsShape;

// ---------- Functions used to move ---------- //

void keyboardInput(MinGL &window, Param &param, Character &pacman, vector<string> &maze, Skin &skin){
    // called inbetween every transition
    // allows to press many directions simultanuously without causing errors and fluidify the movements and the ergonomy
    if(window.isPressed({param.moveKeys["KeyUp"], false}) && pacman.direction != "up" && (isMovePossible(maze,pacman, "up"))) {
            moveCharacter(pacman, "up", skin);
    }
    else if(window.isPressed({param.moveKeys["KeyRight"], false}) && pacman.direction != "right" && (isMovePossible(maze,pacman, "right"))) {
            moveCharacter(pacman, "right", skin);
    }
    else if(window.isPressed({param.moveKeys["KeyDown"], false}) && pacman.direction != "down" && (isMovePossible(maze,pacman, "down"))) {
            moveCharacter(pacman, "down", skin);
    }
    else if(window.isPressed({param.moveKeys["KeyLeft"], false}) && pacman.direction != "left" && (isMovePossible(maze,pacman, "left"))) {
            moveCharacter(pacman, "left", skin);
    }
    else if (isMovePossible(maze,pacman, pacman.direction)){
            moveCharacter(pacman, pacman.direction, skin);// continue in the same direction
    }
    if (isTeleporter(maze, pacman)) moveCharacterTeleporter(maze, pacman,param);
    if (isBubble(pacman, maze)) eatBubble(pacman, maze);
    if (isBigBubble(pacman, maze))eatBigBubble(pacman, maze);
}

bool isMovePossible(vector<string> &maze,Character &character, string direction) {
    //check if the player is going to leave the maze
    if ((direction == "up") && (character.pos.y <= 0)) return false;
    else if ((direction == "down") && (character.pos.y >= maze.size()-1)) return false;
    else if ((direction == "left") && (character.pos.x <= 0)) return false;
    else if ((direction == "right") && (character.pos.x >= maze[0].size()-1)) return false;
    // without these instructions, the player could exit the maze when using the teleporter

    else if ((direction == "up") && (maze[character.pos.y-1][character.pos.x] != '#' && (maze[character.pos.y-1][character.pos.x] != '-' ))) return true;
    else if ((direction == "down") && (maze[character.pos.y+1][character.pos.x] != '#' && (maze[character.pos.y+1][character.pos.x] != '-' ))) return true;
    else if ((direction == "left") && (maze[character.pos.y][character.pos.x-1] != '#' && (maze[character.pos.y][character.pos.x-1] != '-' ))) return true;
    else if ((direction == "right") && (maze[character.pos.y][character.pos.x+1] != '#' && (maze[character.pos.y][character.pos.x+1] != '-' ))) return true;
    else return false;
}

void moveCharacter(Character &character, string direction, Skin &skin) {
    if (direction != character.direction) {
        skin.defaultState[direction].setPosition(skin.defaultState[character.direction].getPosition());
    }
    if (direction == "up") --character.pos.y;
    else if (direction == "right") ++character.pos.x;
    else if (direction == "down") ++character.pos.y;
    else if (direction == "left") --character.pos.x;
    character.direction = direction;
}

void moveCharacterTeleporter (vector<string> &maze, Character &character, Param& param) {
    if(isTeleporter(maze,character)){
        if(character.pos == (getPosTeleporter(param))[0]){ // check if the player is on the first teleporter to know on wich teleporter the player have to move.
            character.pos = (getPosTeleporter(param))[1]; // change the positionof the player to set it on the linked teleporter.
        }else if(character.pos == (getPosTeleporter(param))[1]){
                character.pos = (getPosTeleporter(param))[0];
        }
    }
}

bool isTeleporter(vector<string> &maze, Character & character) {
    //checking if the player is on a teleporter. If yes, it check if the player is taking the teleporter from the right way.
    if ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "up" && isMovePossible(maze, character, "down")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "down" && isMovePossible(maze, character, "up")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "right" && isMovePossible(maze, character, "left")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "left" && isMovePossible(maze, character, "right")) return true;
    else return false;
}

Vec2D calcPosTransition(const Vec2D &posBegin, Character &charact) {
    return {posBegin.getX() + charact.pos.x*50, posBegin.getY() + charact.pos.y*50};
}

bool isSamePos(Character &c1, Character &c2) {
    if (c1.pos.x == c2.pos.x && c1.pos.y == c2.pos.y) return true;
    else return false;
}

// ---------- Functions used in initialisation ---------- //

void initCharacters(map<string, Character> &mapC, Param &param) {
    Character tmp = {Position {1, 1}, "right", true};
    mapC["Pacman"] = tmp;
    tmp = {getPosCage(param), "up", true};
    for (unsigned i(1); i <= param.difficulty["GhostNumber"]; ++i) {
        tmp = {Position {15+i, 7}, "up", true}; // a changer
        mapC["Ghost"+to_string(i)] = tmp;
    }
}


// PAS FINI
void initSkins(map<string, Skin> &mapSkins, Param &param) {
    if (param.skins["Pacman"] == 1) mapSkins["Pacman"] = skinPacman1;
    //else if (param.skins["Pacman"] == 2) mapSkins["Pacman"] = skinPacman2;
    if (param.skins["Ghost"] == 1) mapSkins["Ghost1"] = skinGhost1;
    vector<RGBAcolor> listColors;
    for (unsigned i(2); i <= param.difficulty["GhostNumber"]; ++i) {
        listColors = skinGhost1.defaultState["up"].getPixelData();
        for (RGBAcolor &color : listColors) {
            if (color == skinGhostColors[0]) {
                color = skinGhostColors[i-1];
            }
        }
        Skin tmp = {
             {{"up", nsGui::Sprite(listColors, 50)},
              {"down", nsGui::Sprite(listColors, 50)},
              {"right", nsGui::Sprite(listColors, 50)},
              {"left", nsGui::Sprite(listColors, 50)}
             }, {}
        };
        mapSkins["Ghost"+to_string(i)] = tmp;
    }
}

// ---------- Functions used to draw ---------- //


// PAS FINI -> pour l'instant affiche uniquement les murs en dur
void drawMaze(MinGL &window, vector<string> &maze) {
    for (size_t i(0); i < maze.size(); ++i) {
        for (size_t j(0); j < maze[0].size(); ++j) {
            switch (maze[i][j]) {
            case '#':
                window << Rectangle(posBegin + Vec2D(j*50,i*50), posBegin + Vec2D(j*50+50, i*50+50), KRed);
                break;
            case '.':
                window << Circle(posBegin + Vec2D(j*50+25, i*50+25), 3, KYellow);
                break;
            case 'o':
                window << Circle(posBegin + Vec2D(j*50+25, i*50+25), 8, KYellow);
                break;
            case '-':
                window << Rectangle(posBegin + Vec2D(j*50,i*50), posBegin + Vec2D(j*50+50, i*50+50), KSilver);
            }
        }
    }
}

void drawCharacter(MinGL &window, vector<string> &characterList, map<string, Skin> &skinMap, map<string, Character> &charactMap) {
    for (string &name : characterList) {
        if (charactMap[name].isDefaultState) {
            window << skinMap[name].defaultState[charactMap[name].direction];
        }
    }
}

void launchTransitions(TransitionEngine &t, map<string, Character> &charactMap, bool &isTransitionFinished, map<string,Skin> &skinMap, vector<string> &names) {
    Vec2D posEnd;
    for (const string &name : names) {
        posEnd = calcPosTransition(posBegin, charactMap[name]);
        TransitionContract a(skinMap[name].defaultState[charactMap[name].direction], skinMap[name].defaultState[charactMap[name].direction].TRANSITION_POSITION, chrono::milliseconds(500),{(float)(posEnd.getX()), (float)(posEnd.getY())});
        if (name == "Pacman") {
            a.setDestinationCallback([&] {
                isTransitionFinished = true;
            });}
        t.startContract(a);
    }
}


// ---------- Funtions used for ghosts ---------- //

bool isGhostInCage(Character ghost, Param &param) {
    if (ghost.pos == getPosCage(param)) {
        return true;
    }
    return false;
}

// Met en pause tt le programme
//void letGhostsOut() {
//    this_thread::sleep_for(chrono::seconds(5));
//    cout << "ok" << endl;
//}

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
vector<string> possibleMoves(Position &currentPos, vector<string> &maze){
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

unsigned bestMove(vector<string> &directions, map<Position, unsigned> &openNodes, Position &currentPos){
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
        directions = possibleMoves(currentNode, maze);
        if (directions.size() == 0) {
            openNodes.erase(currentNode);
            tmpNode = closedNodes[currentNode];
            closedNodes.erase(currentNode);
            currentNode = closedNodes[tmpNode];
        }
        else {
            move = nextMove(directions[bestMove(directions, openNodes, currentNode)], currentNode);
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
string aStar(vector<string> &maze, Character &ghost, Character &pacman){
    Position currentNode = ghost.pos;
    map<Position, unsigned> openNodes;
    map<Position, Position> closedNodes;
    vector<Position> nodes = getAllNodes(maze);
    setNodesQuality(nodes, openNodes, pacman.pos);
    aStarAlgorithm(openNodes, closedNodes, pacman.pos, maze, currentNode);
    return firstDirection(closedNodes, currentNode, ghost.pos);
}

// ---------- Other Functions ---------- //

//void changeState(Character &caract, Skin &mapSkin) {
//    caract.isDefaultState = !caract.isDefaultState;
//    if (caract.isDefaultState) {
//        S
//    }
//}

bool isBubble (Character &character, vector<string> &maze){
     if (character.direction == "up" && (maze[character.pos.y+1][character.pos.x] == '.'))return true;
     else if(character.direction == "down" && (maze[character.pos.y-1][character.pos.x] == '.'))return true;
     else if(character.direction == "left" && (maze[character.pos.y][character.pos.x+1] == '.'))return true;
     else if(character.direction == "right" && (maze[character.pos.y][character.pos.x-1] == '.')) return true;
     else return false;
}

void eatBubble (Character &character, vector<string> &maze){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = '\t';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = '\t';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = '\t';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = '\t';
}


bool isBigBubble (Character &character, vector<string> &maze){
     if (character.direction == "up" && (maze[character.pos.y+1][character.pos.x] == 'o'))return true;
     else if(character.direction == "down" && (maze[character.pos.y-1][character.pos.x] == 'o'))return true;
     else if(character.direction == "left" && (maze[character.pos.y][character.pos.x+1] == 'o'))return true;
     else if(character.direction == "right" && (maze[character.pos.y][character.pos.x-1] == 'o')) return true;
     else return false;
}
void eatBigBubble (Character &character, vector<string> &maze){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = '\t';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = '\t';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = '\t';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = '\t';
}

// ---------- Functions used to get values ---------- //

Position getPosCage(Param &param) {
    if (param.skins["Maze"] == 1) {
        return {15, 7};
    }
   return {0,0};
}

vector<Position> getPosTeleporter(Param &param) {
    if (param.skins["Maze"] == 1) {
        return {{11,0}, {11,11}};
    } else if (param.skins["Maze"] == 2) {
        return {{0,5},{22,5}};//take the position of the two teleporter on the first map
    }
    return {{0,0}, {0,0}};
}

// ---------- Functions used for tests ---------- //

void showMap(map<string, Character> &myMap) {
    vector<string> keys;
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        keys.push_back(it->first);
    }
    for (size_t i (0); i < keys.size(); ++i) {
        cout << keys[i] << " -> ";
        cout << " pos.x : " << myMap[keys[i]].pos.x;
        cout << "  |  pos.y : " << myMap[keys[i]].pos.y;
        cout << "  |  direction : " << myMap[keys[i]].direction;
        cout << "  |  isDefaultState : " << myMap[keys[i]].isDefaultState << endl;
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
