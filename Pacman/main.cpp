#define FPS_LIMIT 50
#include <iostream>
#include <thread>
#include <chrono>
#include "mingl/mingl.h"
#include "mingl/transition/transition_engine.h"
#include "initialization.h"
#include "general.h"
#include "assertives.h"
#include "game_logic.h"
#include "draw.h"

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
    PacmanMouth pacmanMouth = initPacmanmouth(param);

    vector<string> maze = initMaze(param);

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
    nsTransition::TransitionEngine transitionEngine;

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
            //checkEating(characterMap, gameRunning);
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
        }  else {
            window << nsGui::Sprite("../Pacman/skins/gameover.si2", Vec2D(window.getWindowSize().getX()/3, 100));
        }
        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
        isBubbleLeft(nbBubbleLeft, gameRunning);
    }

    return 0;
}































