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

    // init functions

    void initCharacters(map<string, Character> &mapC);


    // functions use for test

    void showMaze(const vector<string> &maze);
    void showMap(map<string, Character> &myMap);

    // Others

    void keyboardInput(MinGL &window, map<string, Character> &c);


#endif // FUNCTIONS_H
