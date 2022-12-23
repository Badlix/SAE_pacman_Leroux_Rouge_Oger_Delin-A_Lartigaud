#include "functions.h"
#include <iostream>
#include <map>
#include "mingl/mingl.h"

using namespace std;

void keyboardInput(MinGL &window, map<string, Character> &c) {
    // changing the direction instead of changing directly the pos offer a better control of the character
    if(window.isPressed({'z', false}) && c["Pacman"].direction != "up") {
        //isMovePossible(Pacman, "up")
        c["Pacman"].direction = "up";
    } else if(window.isPressed({'d', false}) && c["Pacman"].direction != "right") {
        c["Pacman"].direction = "right";
    } else if(window.isPressed({'s', false}) && c["Pacman"].direction != "down") {
        c["Pacman"].direction = "down";
    } else if(window.isPressed({'q', false}) && c["Pacman"].direction != "left") {
        c["Pacman"].direction = "left";
    }

    // doit être dans la fonction move je crois
    if(c["Pacman"].direction == "up") {
        --c["Pacman"].posY;
    } else if(c["Pacman"].direction == "right") {
        ++c["Pacman"].posX;
    } else if(c["Pacman"].direction == "down") {
        ++c["Pacman"].posY;
    } else if(c["Pacman"].direction == "left") {
        --c["Pacman"].posX;
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


















