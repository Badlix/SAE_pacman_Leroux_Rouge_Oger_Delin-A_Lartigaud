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

void keyboardInput(MinGL &window, Param &param, Character &pacman, vector<string> &maze, size_t &nbBubbleLeft, vector<string> &listCharact, map<string, Character> &mapCharact){
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
    if (isTeleporter(maze, pacman)) moveCharacterTeleporter(maze, pacman,param);
    else if (isBubble(pacman, maze)) eatBubble(pacman, maze, nbBubbleLeft);
    else if (isBigBubble(pacman, maze)) {
        eatBigBubble(pacman, maze, nbBubbleLeft);
        for (string &name : listCharact) {
            changeState(mapCharact[name]);
        }
    }
}

bool isMovePossible(vector<string> &maze,Character &character, string direction) {
    // check if the player is going to leave the maze
    if ((direction == "up") && (character.pos.y <= 0)) return false;
    else if ((direction == "down") && (character.pos.y >= maze.size()-1)) return false;
    else if ((direction == "left") && (character.pos.x <= 0)) return false;
    else if ((direction == "right") && (character.pos.x >= maze[0].size()-1)) return false;

    // check if the next position is a wall
    else if ((direction == "up") && (maze[character.pos.y-1][character.pos.x] != '#' && (maze[character.pos.y-1][character.pos.x] != '-' ))) return true;
    else if ((direction == "down") && (maze[character.pos.y+1][character.pos.x] != '#' && (maze[character.pos.y+1][character.pos.x] != '-' ))) return true;
    else if ((direction == "left") && (maze[character.pos.y][character.pos.x-1] != '#' && (maze[character.pos.y][character.pos.x-1] != '-' ))) return true;
    else if ((direction == "right") && (maze[character.pos.y][character.pos.x+1] != '#' && (maze[character.pos.y][character.pos.x+1] != '-' ))) return true;
    else return false;
}

void moveCharacter(Character &character, string direction) {
//    if (direction != character.direction) {

//    }
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

Vec2D calcPosTransition(Character &charact) {
    return {posBegin.getX() + charact.pos.x*50, posBegin.getY() + charact.pos.y*50};
}

bool isSamePos(Character &c1, Character &c2) {
    if (c1.pos == c2.pos) return true;
    else return false;
}

// ---------- Functions used in initialisation ---------- //

vector<string> initMaze(Param &param) {
    if (param.skins["Maze"] == 1) return maze1;
    else if (param.skins["Maze"] == 2) return maze2;
}


// VALUE ARE NOT COMPLETE
map<string, Character> initCharacters(Param &param) {
    map<string, Character> mapC;
    /* Set Pacman Skin*/
    Skin skin;
    Skin skinMouthClose;
    if (param.skins["Pacman"] == 1) {skin = flowerPacman; skinMouthClose = flowerPacmanClose;}
    else if (param.skins["Pacman"] == 2) {skin = candyPacman; skinMouthClose = flowerPacmanClose;}
    else if (param.skins["Pacman"] == 3) {skin = penguinPacman; skinMouthClose = penguinPacmanClose;}

    Character tmp = {
        "Pacman",  // type
        Position {1, 1}, // position
        "right", // direction
        true, // isDefaultState
        500, // vitesse
        {}, // sprites
        skin,
        skinMouthClose
    };
    mapC["Pacman"] = tmp;

    /* Set Ghost1 Skin*/
    if (param.skins["Ghost"] == 1) skin = butterflyGhost;
    else if (param.skins["Ghost"] == 2) skin = lolipopGhost;
    else if (param.skins["Ghost"] == 3) skin = iceCreamGhost;

    tmp = {
        "Ghost",
        getPosCage(param),
        "up",
        true,
        500,
        {},
        skin,
        skin
    };
    mapC["Ghost1"] = tmp;
    vector<RGBAcolor> listPixel;
    vector<string> directions = {"up", "down", "right", "left"};
    for (unsigned i(2); i <= param.difficulty["GhostNumber"]; ++i) {
        for (const string &direction : directions) {
            mapC["Ghost"+to_string(i)] = tmp;
            listPixel = mapC["Ghost1"].skins.defaultState.find(direction)->second;
            for (RGBAcolor &color : listPixel) {
                if (color == skinGhostColors[0]) {
                    color = skinGhostColors[i-1];
                }
            }
            mapC["Ghost"+to_string(i)].skins.defaultState[direction] = listPixel;
        }
    }
    return mapC;
}

size_t nbBubbleInMaze(vector<string> &maze){
    size_t bubbleLeft = 0;
    for (size_t i(0); i < maze.size(); ++i){
        for (size_t j=0; j<maze[i].size(); ++j){
            if (maze[i][j] == '.' || maze[i][j] == 'o'){
                ++bubbleLeft;
            }
        }
    }
    return bubbleLeft;
}

// ---------- Functions used to draw ---------- //

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

void drawCharacter(MinGL &window, vector<string> &characterList, map<string, Character> &charactMap) {
    for (string &name : characterList) {
        if (charactMap[name].isDefaultState) {
            charactMap[name].sprite[0].setPixelData(charactMap[name].skins.defaultState.find(charactMap[name].direction)->second);
        } else {
            charactMap[name].sprite[0].setPixelData(charactMap[name].skins.madState.find(charactMap[name].direction)->second);
        }
        charactMap[name].sprite[0].draw(window);
    }
}

void switchMouthPacmanOpenClose(Character &pacman, bool &isMouthOpen) {
    vector<RGBAcolor> tmp;
    vector<string> directions = {"up", "right", "down", "left"};
    for (const string &direction : directions) {
        if (pacman.isDefaultState) {
            if (isMouthOpen) pacman.sprite[0].setPixelData(pacman.skins.defaultState.find(pacman.direction)->second);
            else pacman.sprite[0].setPixelData(pacman.openMouthSkins.defaultState.find(pacman.direction)->second);
        } else {
            if (isMouthOpen) pacman.sprite[0].setPixelData(pacman.skins.madState.find(pacman.direction)->second);
            else pacman.sprite[0].setPixelData(pacman.openMouthSkins.madState.find(pacman.direction)->second);
        }
    }
}

void launchTransitions(TransitionEngine &t, map<string, Character> &charactMap, bool &isTransitionFinished, vector<string> &names) {
    Vec2D posEnd;
    for (const string &name : names) {
        posEnd = calcPosTransition(charactMap[name]);
        TransitionContract a(charactMap[name].sprite[0],
                             charactMap[name].sprite[0].TRANSITION_POSITION, chrono::milliseconds(charactMap[name].vitesse),{(float)(posEnd.getX()), (float)(posEnd.getY())});
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
        directions = possibleDirections(currentNode, maze);
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
string aStar(vector<string> &maze, Position &ghostPos, Position &pacmanPos){
    Position currentNode = ghostPos;
    map<Position, unsigned> openNodes;
    map<Position, Position> closedNodes;
    vector<Position> nodes = getAllNodes(maze);
    setNodesQuality(nodes, openNodes, pacmanPos);
    aStarAlgorithm(openNodes, closedNodes, pacmanPos, maze, currentNode);
    return firstDirection(closedNodes, currentNode, ghostPos);
}

string randomDirection(Character &character, vector<string> &maze){
    vector<string> directions = possibleDirections(character.pos, maze);
    return directions[rand()%5-1];
}

Character randomCharacter(map<string, Character> &characters, vector<string> &characterList) {
    return characters[characterList[rand()%characterList.size()-1]];
}

string decideGhostDirection(Character &ghost, string &personality, unsigned &difficulty, vector<string> maze, Position &pacmanPos, map<string, Character> &characters, vector<string> &characterList) {
    unsigned aStarProba = difficulty*20;
    if(personality == "hardcore") aStarProba *= 1.5;
    if(rand()%100 <= aStarProba) return aStar(maze, ghost.pos, pacmanPos);
    else if (personality == "dumb" || personality == "hardcore") return randomDirection(ghost, maze);
    else if (personality == "confused") {
        Character randomChar = randomCharacter(characters, characterList);
        return aStar(maze, ghost.pos, randomChar.pos);
    }
}


// ---------- Other Functions ---------- //

bool isBubble (Character &character, vector<string> &maze){
    if (character.direction == "up" && (maze[character.pos.y+1][character.pos.x] == '.')) return true;
    else if(character.direction == "down" && (maze[character.pos.y-1][character.pos.x] == '.')) return true;
    else if(character.direction == "left" && (maze[character.pos.y][character.pos.x+1] == '.')) return true;
    else if(character.direction == "right" && (maze[character.pos.y][character.pos.x-1] == '.')) return true;
    else return false;
}

void eatBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
}


bool isBigBubble (Character &character, vector<string> &maze){
    if (character.direction == "up" && (maze[character.pos.y+1][character.pos.x] == 'o')) return true;
    else if(character.direction == "down" && (maze[character.pos.y-1][character.pos.x] == 'o')) return true;
    else if(character.direction == "left" && (maze[character.pos.y][character.pos.x+1] == 'o')) return true;
    else if(character.direction == "right" && (maze[character.pos.y][character.pos.x-1] == 'o')) return true;
    else return false;
}

void eatBigBubble (Character &character, vector<string> &maze, size_t &bubbleLeft){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
}

void isBubbleLeft (size_t &bubbleLeft , bool &gameRunning) {
    if (bubbleLeft == 0){
        gameOver(gameRunning);
    }
}

void gameOver(bool &gameRunning) {
    gameRunning = false;
}

void changeState(Character &charact) {
    charact.isDefaultState = !charact.isDefaultState;
    if (charact.type == "Pacman"){
        if (charact.isDefaultState) charact.vitesse = 500;
        else charact.vitesse = 250;
    }
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
        return {{0,5},{22,5}}; // take the position of the two teleporter on the first map
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
