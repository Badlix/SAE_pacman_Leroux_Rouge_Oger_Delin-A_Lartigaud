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

// ---------- Functions used to move ---------- //

void keyboardInput(MinGL &window, Param &param, Character &pacman) {
    // priority of directions change for a better control of the character [pas clair]
    if(window.isPressed({param.moveKeys["KeyUp"], false}) && pacman.direction != "up") {
        //if (isMovePossible(pacman, "up")) pacman.direction == "up";
        moveCharacter(pacman, "up");
    } else if(window.isPressed({param.moveKeys["KeyRight"], false}) && pacman.direction != "right") {
        moveCharacter(pacman, "right");
    } else if(window.isPressed({param.moveKeys["KeyDown"], false}) && pacman.direction != "down") {
        moveCharacter(pacman, "down");
    } else if(window.isPressed({param.moveKeys["KeyLeft"], false}) && pacman.direction != "left") {
        moveCharacter(pacman, "left");
    } else { // continue in the same direction
        moveCharacter(pacman, pacman.direction);
        // if (isMovePossible(pacman, pacman.direction)
    }
}

void moveCharacter(Character &character, string direction) {
    if (direction == "up") --character.posY;
    else if (direction == "right") ++character.posX;
    else if (direction == "down") ++character.posY;
    else if (direction == "left") --character.posX;
    character.direction = direction;
}

Vec2D calcPosTransition(const Vec2D &posBegin, Character &charact, const Vec2D &posNow) {
    return {posBegin.getX() + charact.posX*50 + (posNow.getX() - posBegin.getX())%50,
            posBegin.getY() + charact.posY*50 + (posNow.getY() - posBegin.getY())%50};
}

// ---------- Functions used in initialisation ---------- //

// PAS FINI
void initCharacters(map<string, Character> &mapC, Param &param) {
    Character tmp = {1, 1, "right", true};
    mapC["Pacman"] = tmp;
    // on initialise la position de tt les fantomes dans la cage au début de la partie
    // pour l'instant on va coder l'emplacement de la cage des fantomes en dur
    tmp = {15, 7, "up", true};
    for (unsigned i(1); i <= param.difficulty["GhostNumber"]; ++i) {
        mapC["Ghost"+to_string(i)] = tmp;
        tmp = {15+i, 7, "up", true}; // a changer
    }
}

// PAS FINI
void initSkins(map<string, Skin> &mapSkins, Param &param) {
    if (param.skins["Pacman"] == 1) mapSkins["Pacman"] = skinPacman1;
    //else if (param.skins["Pacman"] == 2) mapSkins["Pacman"] = skinPacman2;
    if (param.skins["Ghost"] == 1) mapSkins["Ghost1"] = skinGhost1;
    for (size_t i(2); i <= param.difficulty["GhostNumber"]; ++i) {
        mapSkins["Ghost"+to_string(i)] = mapSkins["Ghost1"];
        // change the color of the ghost
        for (Circle &circle : mapSkins["Ghost"+to_string(i)].backLayer.circles) circle.setFillColor(skinGhostColor1[i-1]);
        for (Triangle &triangle : mapSkins["Ghost"+to_string(i)].backLayer.triangles) triangle.setFillColor(skinGhostColor1[i-1]);
        for (Rectangle &rectangle : mapSkins["Ghost"+to_string(i)].backLayer.rectangles) rectangle.setFillColor(skinGhostColor1[i-1]);
    }
}

// ---------- Functions used to draw ---------- //


// PAS FINI -> pour l'instant affiche uniquement les murs en dur
void drawMaze(MinGL &window, vector<string> &maze) {
    for (size_t j(0); j < maze.size(); ++j) {
        for (size_t i(0); i < maze[0].size(); ++i) {
            if (maze[j][i] == '#') window << Rectangle(posBegin + Vec2D(50*i, 50*j), posBegin + Vec2D(50*i+50, 50*j+50), KRed);
        }
    }
}

void drawCharacter(MinGL &window, vector<string> &characterList ,map<string, Skin> &skinMap) {
    for (string &name : characterList) {
        for (Circle &circle : skinMap[name].backLayer.circles) {
            window << circle;
        }
        for (Triangle &triangle : skinMap[name].backLayer.triangles) {
            window << triangle;
        }
        for (Rectangle &rectangle : skinMap[name].backLayer.rectangles) {
            window << rectangle;
        }
        for (Circle &circle : skinMap[name].frontLayer.circles) {
            window << circle;
        }
        for (Triangle &triangle : skinMap[name].frontLayer.triangles) {
            window << triangle;
        }
        for (Rectangle &rectangle : skinMap[name].frontLayer.rectangles) {
            window << rectangle;
        }
    }
}

void launchCircleTransition(TransitionEngine &t, Circle &circle, Character &charact, string &name, bool &isTransitionFinished) {
    Vec2D posEnd;
    posEnd = calcPosTransition(posBegin, charact, circle.getPosition());
    TransitionContract a(circle, circle.TRANSITION_POSITION, chrono::milliseconds(500),{posEnd.getX(), posEnd.getY()});
    if (name == "Pacman" && circle.getRadius() == 25) {
        a.setDestinationCallback([&] {
            isTransitionFinished = true;
        });
    }
    t.startContract(a);
}

template <typename rectOrLineOrTri>
void launchTwoCornerTransition(TransitionEngine &t, rectOrLineOrTri &aShape, Character &charact) {
    Vec2D posEnd;
    // First Corner
    posEnd = calcPosTransition(posBegin, charact, aShape.getFirstPosition());
    TransitionContract b(aShape, aShape.TRANSITION_FIRST_POSITION, chrono::milliseconds(500),{posEnd.getX(), posEnd.getY()});
    t.startContract(b);
    // Second Corner
    posEnd = calcPosTransition(posBegin, charact, aShape.getSecondPosition());
    TransitionContract c(aShape, aShape.TRANSITION_SECOND_POSITION, chrono::milliseconds(500), {posEnd.getX(), posEnd.getY()});
    t.startContract(c);
}

void launchThirdCornerTransition(TransitionEngine &t, Triangle &triangle, Character &charact) {
    Vec2D posEnd;
    // Third Corner
    posEnd = calcPosTransition(posBegin, charact, triangle.getThirdPosition());
    TransitionContract d(triangle, triangle.TRANSITION_THIRD_POSITION, chrono::milliseconds(500),{posEnd.getX(), posEnd.getY()});
    t.startContract(d);
}

void launchAllTransition(vector<string> &characterList, map<string,Skin> &skinMap, map<string,Character> &characterMap, TransitionEngine &t, bool &isTransitionFinished) {
    for (string &name : characterList) {
        // draw back layer
        for (Circle &circle : skinMap[name].backLayer.circles) {
            launchCircleTransition(t, circle, characterMap[name], name, isTransitionFinished);
        }
        for (Triangle &triangle : skinMap[name].backLayer.triangles) {
            launchTwoCornerTransition(t, triangle, characterMap[name]);
            launchThirdCornerTransition(t, triangle, characterMap[name]);
        }
        for (Rectangle &rectangle : skinMap[name].backLayer.rectangles) {
            launchTwoCornerTransition(t, rectangle, characterMap[name]);
        }
        // draw front layer
        for (Circle &circle : skinMap[name].frontLayer.circles) {
            launchCircleTransition(t, circle, characterMap[name], name, isTransitionFinished);
        }
        for (Triangle &triangle : skinMap[name].frontLayer.triangles) {
            launchTwoCornerTransition(t, triangle, characterMap[name]);
            launchThirdCornerTransition(t, triangle, characterMap[name]);
        }
        for (Rectangle &rectangle : skinMap[name].frontLayer.rectangles) {
            launchTwoCornerTransition(t, rectangle, characterMap[name]);
        }
    }
}

// ---------- Functions used for tests ---------- //

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
