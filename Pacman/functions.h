#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>
#include <map>
#include "constants.h"

using namespace std;

namespace functions {
    void showMaze(vector<string> & maze);
    void initCharacters(map<string, Character> & mapC);
}

#endif // FUNCTIONS_H
