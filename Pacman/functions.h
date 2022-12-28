#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>
#include <map>
#include "mingl/mingl.h"
#include "mingl/transition/transition_engine.h"
#include "constants.h"
#include "param.h"

using namespace std;

    // types

    struct Character {
        unsigned posX;
        unsigned posY;
        string direction;
        bool isDefaultState;
    };

    // move fonctions

    void keyboardInput(MinGL &window, Character &pacman);
    void moveCharacter(Character &c, string direction);
    nsGraphics::Vec2D calcPosTransition(const Vec2D &posBegin, Character &charact, const Vec2D &posNow);

    // init functions

    void initCharacters(map<string, Character> &mapC, Param &param);
    void initSkins(map<string, Skin> &mapSkins, Param &param);

    // functions use to draw

    void launchAllTransition(vector<string> &characterList, map<string,Skin> &skinMap, map<string, Character> &characterMap, nsTransition::TransitionEngine &t, bool &isTransitionFinished);

    // functions use for test

    void showMaze(const vector<string> &maze);
    void showMap(map<string, Character> &myMap);

    // Others

#endif // FUNCTIONS_H
