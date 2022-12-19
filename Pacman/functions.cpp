#include "functions.h"
#include <iostream>
#include <map>
#include "constants.h"

using namespace std;

void functions::showMaze(const vector<string> & maze) {
    for (string line : maze) {
        for (char c : line) {
            cout << c << ' ';
        }
        cout << endl;
    }
}

pair<unsigned, unsigned> functions::getCagePos() {
    // if terrain selectionné = 1
    // blablabla
    return constants::posCage1; // <x, y>
}

//void functions::initCharacters(map<string, functions::Character> mapC) {
//    mapC.insert(("Pacman", (1,1, true));
////    // le nb de fantome dependra des parametres, ne partaient pas du principe qu'il y en a que 4
////    pair<unsigned, unsigned> cagePos = getCagePos();
////    mapC.insert({"Ghost1", {cagePos.first, cagePos.second, true}});
////    mapC.insert({"Ghost2", {cagePos.first, cagePos.second, true}});
////    mapC.insert({"Ghost3", {cagePos.first, cagePos.second, true}});
////    mapC.insert({"Ghost4", {cagePos.first, cagePos.second, true}});
//}

struct functions::Character {
    unsigned posX;
    unsigned posY;
    bool isDefaultState;
};
