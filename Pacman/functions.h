#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>
#include <map>
#include "mingl/mingl.h"
#include "mingl/transition/transition_engine.h"
#include "constants.h"
#include "param.h"
#include <cmath>
#include <ostream>

using namespace std;

    // types

    struct Position {
        int x;
        int y;
        bool operator == (const Position& p) const {
            return x == p.x && y == p.y;
        }
        bool operator != (const Position& p) const {
            return x != p.x || y != p.y;
        }
        bool operator > (const Position& p) const {
            return x > p.x || y > p.y;
        }
        bool operator < (const Position& p) const {
            return x < p.x || y < p.y;
        }
    };


    struct Character {
        Position pos;
        string direction;
        bool isDefaultState;
    };

    // move fonctions

    void keyboardInput(MinGL &window, Param &param, Character &pacman, vector<string> &maze, Skin &skin);
    bool isMovePossible(vector<string> &maze,Character &character, string direction);
    void moveCharacter(Character &c, string direction, Skin &skin);
    void moveCharacterTeleporter (vector<string> &maze, Character &character, Param& param);
    bool isTeleporter(vector<string> &maze,Character & character);
    nsGraphics::Vec2D calcPosTransition(const Vec2D &posBegin, Character &charact);
    bool isSamePos(Character &c1, Character &c2);

    // initialization functions

    void initCharacters(map<string, Character> &mapC, Param &param);
    void initSkins(map<string, Skin> &mapSkins, Param &param);

    // functions used to draw

    void drawCharacter(MinGL &window, vector<string> &characterList , map<string, Skin> &skinMap, map<string, Character> &charactMap);
    void drawMaze(MinGL &window, vector<string> &maze);
    void launchTransitions(nsTransition::TransitionEngine &t, map<string, Character> & characterMap, bool &isTransitionFinished, map<string,Skin> &skinMap, vector<string> &names);

    // functions used for ghosts

    bool isGhostInCage(Character ghost, Param &param);
    //void letGhostsOut();

    // A* algorithm
    unsigned nodeQuality(Position &currentPos, Position &pacmanPos);
    bool isFree(char &pos);
    vector<Position> getAllNodes(vector<string> &maze);
    void setNodesQuality(vector<Position> &nodes, map<Position, unsigned> &openNodes, Position &pacmanPos);
    vector<string> possibleMoves(Position &currentPos, vector<string> &maze);
    unsigned bestMove(vector<string> &directions, map<Position, unsigned> &openNodes);
    Position nextMove(string &direction, Position &currentPos);
    void aStarAlgorithm(map<Position, unsigned> &openNodes, map<Position, Position> &closedNodes, Position &pacmanPos, vector<string> &maze, Position &currentNode);
    string getDirection(Position &pos1, Position &pos2);
    string firstDirection(map<Position, Position> closedNodes, Position &currentNode, Position &ghostPos);
    string aStar(vector<string> &maze, Character &ghost, Character &pacman);
    string randomDirection(Character &character, vector<string> &maze);
    Character randomCharacter(map<string, Character> &characters, vector<string> &characterList);
    string decideGhostDirection(Character &ghost, string &personality, unsigned &difficulty, vector<string> maze, Position &pacmanPos, map<string, Character> &characters, vector<string> &characterList);

    // functions used to get value

    Position getPosCage(Param &param);
    vector<Position> getPosTeleporter(Param &param);

    // functions used for tests

    void showMaze(const vector<string> &maze);
    void showMap(map<string, Character> &myMap);

    // Others

    bool isBigBubble (Character &character, vector<string> &maze);
    bool isBubble (Character &character, vector<string> &maze);
    void eatBubble (Character &character, vector<string> &maze);
    void eatBigBubble (Character &character, vector<string> &maze);

#endif // FUNCTIONS_H
