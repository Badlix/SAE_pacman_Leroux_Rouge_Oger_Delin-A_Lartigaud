#include "functions.h"
#include "param.h"
#include "constants.h"
#include <iostream>
#include <map>
#include <vector>
#include "mingl/mingl.h"
#include "mingl/transition/transition_engine.h"

using namespace std;
using namespace nsTransition;
using namespace nsGraphics;
using namespace nsShape;

// ---------- Fonctions uses to move ---------- //

void keyboardInput(MinGL &window, Character &pacman) {
    // priority of directions change for a better control of the character
    if(window.isPressed({'z', false}) && pacman.direction != "up") {
        //if (isMovePossible(pacman, "up")) pacman.direction == "up";
        moveCharacter(pacman, "up");
    } else if(window.isPressed({'d', false}) && pacman.direction != "right") {
        moveCharacter(pacman, "right");
    } else if(window.isPressed({'s', false}) && pacman.direction != "down") {
        moveCharacter(pacman, "down");
    } else if(window.isPressed({'q', false}) && pacman.direction != "left") {
        moveCharacter(pacman, "left");
    } else { // continue in the same direction
        moveCharacter(pacman, pacman.direction);
        // if (isMovePossible(pacman, pacman.direction)
    }
}

void moveCharacter(Character &c, string direction) {
    if (direction == "up") --c.posY;
    else if (direction == "right") ++c.posX;
    else if (direction == "down") ++c.posY;
    else if (direction == "left") --c.posX;
    c.direction = direction;
}

Vec2D calcPosTransition(const Vec2D &posBegin, Character &charact, const Vec2D &posNow) {
    return {(float)(posBegin.getX() + charact.posX*50 + (posNow.getX() - posBegin.getX())%50),
                (float)(posBegin.getY() + charact.posY*50 + (posNow.getY() - posBegin.getY())%50)};
}

// ---------- Fonctions uses for initialisations ---------- //

void initCharacters(map<string, Character> &mapC, Param &param) {
    Character tmp = {1, 1, "right", true};
    mapC["Pacman"] = tmp;
    // pour l'instant on va coder l'emplacement de la cage des fantomes en dur
    tmp = {15, 7, "up", true};
    for (unsigned i(1); i <= param.difficulty["GhostNumber"]; ++i) {
        mapC["Ghost"+to_string(i)] = tmp;
        // on initialise la position de tt les fantomes dans la cage au début de la partie
    }
}

void initSkins(map<string, Skin> &mapSkins, Param &param) {
    if (param.skins["Pacman"] == 1) mapSkins["Pacman"] = skinPacman1;
}

// ---------- Fonctions uses to draw ---------- //

void drawCharacter(MinGL &window, vector<string> &characterList ,map<string, Skin> &skinMap) {
    for (string name : characterList) {
        for (Circle circle : skinMap[name].circles) {
            window << circle;
        }
        for (Triangle triangle : skinMap[name].triangles) {
            window << triangle;
        }
    }
}

void launchAllTransition(vector<string> &characterList, map<string,Skin> &skinMap, map<string,Character> &characterMap, TransitionEngine &t, bool &isTransitionFinished) {
    Vec2D posEnd;
    for (string &name : characterList) {
        for (Circle &circle : skinMap[name].circles) {
            posEnd = calcPosTransition(posBegin, characterMap[name], circle.getPosition());
            TransitionContract a(circle, circle.TRANSITION_POSITION, chrono::milliseconds(500),
                               {posEnd.getX(), posEnd.getY()});
            if (name == "Pacman" && circle.getRadius() == 25) {
                a.setDestinationCallback([&] {
                    isTransitionFinished = true;
                });
            }
            t.startContract(a);
        }
        for (Triangle &triangle : skinMap[name].triangles) {
            // First Point
            posEnd = calcPosTransition(posBegin, characterMap[name], triangle.getFirstPosition());
            TransitionContract b(triangle, triangle.TRANSITION_FIRST_POSITION, chrono::milliseconds(500),
            {posEnd.getX(), posEnd.getY()});
            t.startContract(b);
            // Second Point
            posEnd = calcPosTransition(posBegin, characterMap[name], triangle.getSecondPosition());
            TransitionContract c(triangle, triangle.TRANSITION_SECOND_POSITION, chrono::milliseconds(500),
            {posEnd.getX(), posEnd.getY()});
            t.startContract(c);
            // Thirs Point
            posEnd = calcPosTransition(posBegin, characterMap[name], triangle.getThirdPosition());
            TransitionContract d(triangle, triangle.TRANSITION_THIRD_POSITION, chrono::milliseconds(500),
            {posEnd.getX(), posEnd.getY()});
            t.startContract(d);
        }
    }
}

// ---------- Fonctions uses for tests ---------- //

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


















