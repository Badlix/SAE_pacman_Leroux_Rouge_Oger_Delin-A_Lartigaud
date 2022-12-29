#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <chrono>

#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/transition/transition_engine.h"

#include "functions.h"
#include "constants.h"
#include "param.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace nsTransition;

// main pour les tests console

//int main() {
//    vector<string> maze = maze1;
//    showMaze(maze);
//    map<string, Character> characterMaps;
//    initCharacters(characterMaps);
//    showMap(characterMaps);
//}


// main mingl

int main()
{
    // Initalisation of 'shell' elements
    Param param;
    loadParam(param);

    map<string, Character> characterMap;
    initCharacters(characterMap, param);
    showMap(characterMap);

    map<string, Skin> skinMap;
    initSkins(skinMap, param);

    vector<string> maze = maze1;

    vector<string> characterList;
    for (auto it = characterMap.begin(); it != characterMap.end(); it++) {
        characterList.push_back(it->first);
    }

    // Initialisation of the graphics system
    MinGL window("Pacman", Vec2D(1500, 900), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();
    TransitionEngine transitionEngine;

    // Initialisation graphic of the maze
    vector<Rectangle> vR = {};
    for (int i (150); i < 1350; i+=50) {
        for (int j (100); j < 750; j+=50) {
            vR.push_back(Rectangle(Vec2D(i,j), Vec2D(i+50, j+50), KBlue));
            vR[vR.size()-1].setBorderColor(KCyan);
        }
    }

    bool isTransitionFinished (true);
    chrono::microseconds frameTime = chrono::microseconds::zero();
    while (window.isOpen())
    {
        if (isTransitionFinished) {
            keyboardInput(window, param, characterMap["Pacman"]);
            isTransitionFinished = false;
            launchAllTransition(characterList, skinMap, characterMap, transitionEngine, isTransitionFinished);
        }

        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        window.clearScreen();
        transitionEngine.update(frameTime);

        for (size_t k (0); k < vR.size(); ++k) { // show Grid
            window << vR[k];
        }

        drawCharacter(window, characterList, skinMap);

        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
}
