#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <chrono>
#include <map>

#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/transition/transition_engine.h"
#include "mingl/gui/sprite.h"

#include "functions.h"
#include "constants.h"
#include "param.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace nsTransition;

int main()
{
    // Initalization of core elements
    Param param;
    initParam(param);
    loadParam(param);

    map<string, Character> characterMap = initCharacters(param);
    map<string, Skin> skinMap = initSkins(param);
    Skin closedMouthPacman = initSkinMouthPacman(param);
    vector<string> maze = initMaze(param); // 22x11 = max i
    vector<string> characterList;
    for (auto it = characterMap.begin(); it != characterMap.end(); it++) {
        characterList.push_back(it->first);
    }
    bool gameRunning = true;
    size_t nbBubbleLeft = nbBubbleInMaze(maze);

    // Initalization of the graphics system
    MinGL window("Pacman", Vec2D(1550, 900), Vec2D(128, 128), KSilver);
    window.initGlut();
    window.initGraphic();
    TransitionEngine transitionEngine;

    // Graphic initalization of the maze
    vector<Rectangle> vR = {};
    for (size_t i(posBegin.getX()); i <= 1300; i+=50) {
        for (size_t j (posBegin.getY()); j <= 700; j+=50) {
            vR.push_back(Rectangle(Vec2D(i,j), Vec2D(i+50, j+50), KTeal));
            vR[vR.size()-1].setBorderColor(KCyan);
        }
    }
    unsigned i(0);
    bool isTransitionFinished (true);
    chrono::microseconds frameTime = chrono::microseconds::zero();
    while (window.isOpen())
    {
        if (isTransitionFinished) {
            keyboardInput(window, param, characterMap["Pacman"], maze, skinMap["Pacman"], nbBubbleLeft);
            isTransitionFinished = false;
            launchTransitions(transitionEngine, characterMap, isTransitionFinished, skinMap, characterList);
        }

        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        window.clearScreen();
        transitionEngine.update(frameTime);

        if (gameRunning == true){
            for (size_t k (0); k < vR.size(); ++k) { // show Grid -> temporaire
                window << vR[k];
            }
            if (i > 15) {
                switchMouthPacmanOpenClose(skinMap["Pacman"], closedMouthPacman);
                i = 0;
            }
            drawMaze(window, maze);
            drawCharacter(window, characterList, skinMap, characterMap);
            ++i;
            //letGhostsOut();
        } /* else {
            window << sprite de gameover/victoire et avec indication d'une touche rejouer et d'une touche pour quitter
        }*/
        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
        isBubbleLeft(nbBubbleLeft, gameRunning);
    }

    return 0;
}































