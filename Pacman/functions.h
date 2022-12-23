#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>
#include <map>
#include "mingl/mingl.h"

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

    // init functions

    void initCharacters(map<string, Character> &mapC);


    // functions use for test

    void showMaze(const vector<string> &maze);
    void showMap(map<string, Character> &myMap);

    // Others

#endif // FUNCTIONS_H
