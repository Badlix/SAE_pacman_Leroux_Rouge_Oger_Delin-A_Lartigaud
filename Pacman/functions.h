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
        int posX;
        int posY;
        string direction;
        bool isDefaultState;
    };

    // move fonctions

    void keyboardInput(MinGL &window, Param &param, Character &pacman);
    void moveCharacter(Character &c, string direction);
    nsGraphics::Vec2D calcPosTransition(const Vec2D &posBegin, Character &charact, const Vec2D &posNow);

    // initialization functions

    void initCharacters(map<string, Character> &mapC, Param &param);
    void initSkins(map<string, Skin> &mapSkins, Param &param);

    // functions used to draw

    template <typename rectOrLineOrTri>
    void launchCircleTransition(nsTransition::TransitionEngine &t, Circle &circle, Character &charact, string &name, bool &isTransitionFinished);
    void launchTwoCornerTransition(nsTransition::TransitionEngine &t, rectOrLineOrTri &aShape, Character &charact);
    void launchThirdCornerTransition(nsTransition::TransitionEngine &t, Triangle &triangle, Character &charact);
    void launchAllTransition(vector<string> &characterList, map<string,Skin> &skinMap, map<string, Character> &characterMap, nsTransition::TransitionEngine &t, bool &isTransitionFinished);
    void drawCharacter(MinGL &window, vector<string> &characterList ,map<string, Skin> &skinMap);

    // functions used for tests

    void showMaze(const vector<string> &maze);
    void showMap(map<string, Character> &myMap);

    // Others

#endif // FUNCTIONS_H
