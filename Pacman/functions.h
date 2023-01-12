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

    // move fonctions
    void keyboardInput(MinGL &window, Param &param, Character &pacman, vector<string> &maze);

    /**
     * @brief check if a move is possible
     * @param maze : vector<string>
     * @param character : ?
     * @param[in] direction : ?
     * @return true if the move is possible, if not return false
     * @fn bool isMovePossible(vector<string> &maze,Character &character, string direction)
     */
    bool isMovePossible(vector<string> &maze,Character &character, string direction);
    void moveCharacter(Character &c, string direction);
    void moveCharacterTeleporter (vector<string> &maze, Character &character, Param& param);
    bool isTeleporter(vector<string> &maze,Character & character);
    nsGraphics::Vec2D calcPosTransition(Character &charact);
    bool isSamePos(Character &c1, Character &c2);

    // initialization functions

    vector<string> initMaze(Param &param);
    map<string, Character> initCharacters(Param &param);
    PacmanMouth initPacmanmouth(Param &param);
    size_t nbBubbleInMaze(vector<string> &maze);

    // functions used to draw

    void drawCage(MinGL &window, Vec2D pos);
    void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth);
    void drawCharacter(MinGL &window, vector<string> &characterList, map<string, Character> &charactMap);
    void drawMaze(MinGL &window, vector<string> &maze, Param &param);
    void launchTransitions(nsTransition::TransitionEngine &t, map<string, Character> & characterMap, bool &isTransitionFinished, vector<string> &names);

    // functions used to get value

    vector<Position> getPosTeleporter(Param &param);

    // functions used for tests

    void showMaze(const vector<string> &maze);
    void showMap(map<string, Character> &myMap);

    // Others

    void isBubbleLeft (size_t &bubbleLeft , bool &gameRunning);
    void gameOver(bool &gameRunning);
    void removeBubbleOnCount (size_t &bubbleLeft, bool &gameRunning);
    bool isBigBubble (Character &character, vector<string> &maze);
    bool isBubble (Character &character, vector<string> &maze);
    void eatBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft);
    void eatBigBubble (Character &character, vector<string> &maze, size_t &bubbleLeft);
    void bigBubbleDuration(map<string, Character> &mapCharact);
    void changeState(Character &charact);
    void changeEveryoneState(map<string, Character> &mapCharact, bool newValue);

#endif // FUNCTIONS_H
