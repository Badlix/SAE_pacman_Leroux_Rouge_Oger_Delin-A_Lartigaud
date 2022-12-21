#include "functions.h"
#include <iostream>
#include <map>
#include "mingl/mingl.h"

using namespace std;

void keyboardInput(MinGL &window, nsGraphics::Vec2D pos) {
    if(window.isPressed({'z', false})) {
        cout << "up"; //isMovePossible(Pacman, "up")
    } else if(window.isPressed({'d', false})) {
        cout << "right";
    } else if(window.isPressed({'s', false})) {
        cout << "down";
    } else if(window.isPressed({'q', false})) {
        cout << "left";
    }
}

// ---------- Fonctions uses for initialisations

void initCharacters(map<string, Character> &mapC) {
    Character tmp = {1, 1, "right", true};
    mapC["Pacman"] = tmp;
    // nb de fantome dependra des parametres, ne partaient pas du principe qu'il y en a que 4
    // pour l'instant on va coder l'emplacement de la cage des fantomes en dur
    tmp = {15, 7, "up", true};
    for (unsigned i(1); i <= 4; ++i) {
        mapC["Ghost"+to_string(i)] = tmp;
        // on initialise la position de tt les fantomes dans la cage au début de la partie
    }
}

// ---------- Fonctions uses for tests ----------//

void showMap(map<string, Character> &myMap) {
    vector<string> keys;
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        keys.push_back(it->first);
    }
    for (size_t i (0); i < keys.size(); ++i) {
        cout << keys[i] << " -> ";
        cout << " posX : " << myMap[keys[i]].posX;
        cout << "  |  posY : " << myMap[keys[i]].posY;
        cout << "  |  direction : " << myMap[keys[i]].direction;
        cout << "  |  isDefaultState : " << myMap[keys[i]].isDefaultState << endl;
    }
}

void showMaze(const vector<string> & maze) {
    for (string line : maze) {
        for (char c : line) {
            cout << c << ' ';
        }
        cout << endl;
    }
}


















