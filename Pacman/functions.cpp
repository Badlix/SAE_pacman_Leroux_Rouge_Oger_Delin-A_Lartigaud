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

void keyboardInput(MinGL &window, Param &param, Character &pacman, vector<string> &maze){
    // priority of directions change for a better control of the character [pas clair]
    if(window.isPressed({param.moveKeys["KeyUp"], false}) && pacman.direction != "up" && (isMovePossible(maze,pacman, "up"))) {
            pacman.direction = "up";
            moveCharacter(pacman, "up");}
    else if(window.isPressed({param.moveKeys["KeyRight"], false}) && pacman.direction != "right" && (isMovePossible(maze,pacman, "right"))) {
            pacman.direction = "right";
            moveCharacter(pacman, "right");}
    else if(window.isPressed({param.moveKeys["KeyDown"], false}) && pacman.direction != "down" && (isMovePossible(maze,pacman, "down"))) {
            pacman.direction = "down";
            moveCharacter(pacman, "down");}
    else if(window.isPressed({param.moveKeys["KeyLeft"], false}) && pacman.direction != "left" && (isMovePossible(maze,pacman, "left"))) {
            pacman.direction = "left";
            moveCharacter(pacman, "left");}
    else if (isMovePossible(maze,pacman, pacman.direction)){
            moveCharacter(pacman, pacman.direction); // continue in the same direction
    }
}

bool isMovePossible(vector<string> &maze,Character &character, string direction) {
    if ((direction == "up") && (maze[character.pos.y-1][character.pos.x] != '#' && (maze[character.pos.y-1][character.pos.x] != '~' ))) return true;
    else if ((direction == "down") && (maze[character.pos.y+1][character.pos.x] != '#' && (maze[character.pos.y+1][character.pos.x] != '~' ))) return true;
    else if ((direction == "left") && (maze[character.pos.y][character.pos.x-1] != '#' && (maze[character.pos.y][character.pos.x-1] != '~' ))) return true;
    else if ((direction == "right") && (maze[character.pos.y][character.pos.x+1] != '#' && (maze[character.pos.y][character.pos.x+1] != '~' ))) return true;
    else return false;
}

void moveCharacter(Character &character, string direction) {
    if (direction == "up") --character.pos.y;
    else if (direction == "right") ++character.pos.x;
    else if (direction == "down") ++character.pos.y;
    else if (direction == "left") --character.pos.x;
    character.direction = direction;
}

Vec2D calcPosTransition(const Vec2D &posBegin, Character &charact, const Vec2D &posNow) {
    return {posBegin.getX() + charact.pos.x*50 + (posNow.getX() - posBegin.getX())%50,
            posBegin.getY() + charact.pos.y*50 + (posNow.getY() - posBegin.getY())%50};
}

bool isSamePos(Character &c1, Character &c2) {
    if (c1.pos.x == c2.pos.x && c1.pos.y == c2.pos.y) return true;
    else return false;
}

// ---------- Functions used in initialisation ---------- //

// PAS FINI
void initCharacters(map<string, Character> &mapC, Param &param) {
    Character tmp = {Position {1, 1}, "right", true};
    mapC["Pacman"] = tmp;
    // on initialise la position de tt les fantomes dans la cage au début de la partie
    // pour l'instant on va coder l'emplacement de la cage des fantomes en dur
    tmp = {getPosCage(param), "up", true};
    for (unsigned i(1); i <= param.difficulty["GhostNumber"]; ++i) {
        mapC["Ghost"+to_string(i)] = tmp;
        tmp = {Position {static_cast<int>(15+i), 7}, "up", true}; // a changer
    }
}

void initSkins(map<string, Skin> &mapSkins, Param &param) {
    if (param.skins["Pacman"] == 1) mapSkins["Pacman"] = skinPacman1;
    //else if (param.skins["Pacman"] == 2) mapSkins["Pacman"] = skinPacman2;
    if (param.skins["Ghost"] == 1) mapSkins["Ghost1"] = skinGhost1;
    for (size_t i(2); i <= param.difficulty["GhostNumber"]; ++i) {
        mapSkins["Ghost"+to_string(i)] = mapSkins["Ghost1"];
        // change the color of the ghost
        for (Circle &circle : mapSkins["Ghost"+to_string(i)].backLayer.circles) circle.setFillColor(skinGhostColor1[i-1]);
        for (Triangle &triangle : mapSkins["Ghost"+to_string(i)].backLayer.triangles) triangle.setFillColor(skinGhostColor1[i-1]);
        for (Rectangle &rectangle : mapSkins["Ghost"+to_string(i)].backLayer.rectangles) rectangle.setFillColor(skinGhostColor1[i-1]);
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
            }
        }
    }
}

void drawCharacter(MinGL &window, vector<string> &characterList, map<string, Skin> &skinMap) {
    for (string &name : characterList) {
        for (Circle &circle : skinMap[name].backLayer.circles) {
            window << circle;
        }
        for (Triangle &triangle : skinMap[name].backLayer.triangles) {
            window << triangle;
        }
        for (Rectangle &rectangle : skinMap[name].backLayer.rectangles) {
            window << rectangle;
        }
        for (Circle &circle : skinMap[name].frontLayer.circles) {
            window << circle;
        }
        for (Triangle &triangle : skinMap[name].frontLayer.triangles) {
            window << triangle;
        }
        for (Rectangle &rectangle : skinMap[name].frontLayer.rectangles) {
            window << rectangle;
        }
    }
}

void launchCircleTransition(TransitionEngine &t, Circle &circle, Character &charact, string &name, bool &isTransitionFinished) {
    Vec2D posEnd;
    posEnd = calcPosTransition(posBegin, charact, circle.getPosition());
    TransitionContract a(circle, circle.TRANSITION_POSITION, chrono::milliseconds(500),{(float)(posEnd.getX()), (float)(posEnd.getY())});
    if (name == "Pacman" && circle.getRadius() == 25) {
        a.setDestinationCallback([&] {
            isTransitionFinished = true;
        });
    }
    t.startContract(a);
}

template <typename rectOrLineOrTri>
void launchTwoCornerTransition(TransitionEngine &t, rectOrLineOrTri &aShape, Character &charact) {
    Vec2D posEnd;
    // First Corner
    posEnd = calcPosTransition(posBegin, charact, aShape.getFirstPosition());
    TransitionContract b(aShape, aShape.TRANSITION_FIRST_POSITION, chrono::milliseconds(500),{(float)(posEnd.getX()), (float)(posEnd.getY())});
    t.startContract(b);
    // Second Corner
    posEnd = calcPosTransition(posBegin, charact, aShape.getSecondPosition());
    TransitionContract c(aShape, aShape.TRANSITION_SECOND_POSITION, chrono::milliseconds(500), {(float)(posEnd.getX()), (float)(posEnd.getY())});
    t.startContract(c);
}

void launchThirdCornerTransition(TransitionEngine &t, Triangle &triangle, Character &charact) {
    Vec2D posEnd;
    // Third Corner
    posEnd = calcPosTransition(posBegin, charact, triangle.getThirdPosition());
    TransitionContract d(triangle, triangle.TRANSITION_THIRD_POSITION, chrono::milliseconds(500),{(float)(posEnd.getX()), (float)(posEnd.getY())});
    t.startContract(d);
}

void launchAllTransition(vector<string> &characterList, map<string,Skin> &skinMap, map<string,Character> &characterMap, TransitionEngine &t, bool &isTransitionFinished) {
    for (string &name : characterList) {
        // draw back layer
        for (Circle &circle : skinMap[name].backLayer.circles) {
            launchCircleTransition(t, circle, characterMap[name], name, isTransitionFinished);
        }
        for (Triangle &triangle : skinMap[name].backLayer.triangles) {
            launchTwoCornerTransition(t, triangle, characterMap[name]);
            launchThirdCornerTransition(t, triangle, characterMap[name]);
        }
        for (Rectangle &rectangle : skinMap[name].backLayer.rectangles) {
            launchTwoCornerTransition(t, rectangle, characterMap[name]);
        }
        // draw front layer
        for (Circle &circle : skinMap[name].frontLayer.circles) {
            launchCircleTransition(t, circle, characterMap[name], name, isTransitionFinished);
        }
        for (Triangle &triangle : skinMap[name].frontLayer.triangles) {
            launchTwoCornerTransition(t, triangle, characterMap[name]);
            launchThirdCornerTransition(t, triangle, characterMap[name]);
        }
        for (Rectangle &rectangle : skinMap[name].frontLayer.rectangles) {
            launchTwoCornerTransition(t, rectangle, characterMap[name]);
        }
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
            tmpNode = closedNodes.currentNode;
            closedNodes.erase(currentNode);
            currentNode = closedNodes.tmpNode;
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
    else if ( pos1.x == pos2.x && pos1.y+1 == pos2.y ) return "right";
}
string firstDirection(map<Position, Position> closedNodes, Position &currentNode, Position &ghostPos){
    if (closedNodes[currentNode] == ghostPos) return getDirection(ghostPos, currentNode);
    firstDirection(closedNodes, closedNodes[currentNode], ghostPos);
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

// ---------- Functions used to get values ---------- //

Position getPosCage(Param &param) {
    if (param.skins["Maze"] == 1) {
        return {15, 7};
    }
    return {0,0};
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
