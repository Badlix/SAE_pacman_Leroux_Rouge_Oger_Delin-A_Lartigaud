#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>
#include <map>
#include "constants.h"

using namespace std;

namespace functions {
    struct Character;
    void showMaze(const vector<string> &maze);
    void initCharacters(map<string, Character> mapC);
    pair<unsigned, unsigned> getCagePos();
}

#endif // FUNCTIONS_H
