#define FPS_LIMIT 50

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

#include "ghost.h"
#include "functions.h"
#include "constants.h"
#include "param.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace nsTransition;

//int main() {
//    vector<string> maze = maze1;
//    Position posGhost = {1,1};
//    Position posPacman = {2,1};
//    cout << aStar(maze, posGhost, posPacman) << endl;
//    return 0;
//}

int main()
{
    // Initalization of core elements
    Param param;
    initParam(param);
    loadParam(param);

    map<string, Character> characterMap = initCharacters(param);
    PacmanMouth pacmanMouth = initPacmanmouth(param);

    vector<string> maze = initMaze(param); // 22x11 = max i

    vector<string> characterList;
    for (auto it = characterMap.begin(); it != characterMap.end(); it++) {
        characterList.push_back(it->first);
    }

    bool gameRunning = true;

    size_t nbBubbleLeft = nbBubbleInMaze(maze);

    // Initalization of the graphics system
    MinGL window("Pacman", Vec2D(1550, 900), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();
    TransitionEngine transitionEngine;

    bool isTransitionFinished (true);
    unsigned bigBubbleDuration(0);
    chrono::microseconds frameTime = chrono::microseconds::zero();
    while (window.isOpen())
    {

        if (isTransitionFinished) {
            keyboardInput(window, param, characterMap["Pacman"], maze);
            if (isTeleporter(maze, characterMap["Pacman"])) moveCharacterTeleporter(maze, characterMap["Pacman"], param);
            else if (isBubble(characterMap["Pacman"], maze)) eatBubble(characterMap["Pacman"], maze, nbBubbleLeft);
            else if (isBigBubble(characterMap["Pacman"], maze)) {
                eatBigBubble(characterMap["Pacman"], maze, nbBubbleLeft);
                changeEveryoneState(characterMap, false);
                bigBubbleDuration = 0;
            }
            ++bigBubbleDuration;
            if (bigBubbleDuration == 30) changeEveryoneState(characterMap, true);
            isTransitionFinished = false;
            launchTransitions(transitionEngine, characterMap, isTransitionFinished, characterList);
        }

        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        window.clearScreen();
        transitionEngine.update(frameTime);

        if (gameRunning == true){
            switchMouthPacmanOpenClose(characterMap["Pacman"], pacmanMouth);
            drawMaze(window, maze, param);
            drawCharacter(window, characterList, characterMap);
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































