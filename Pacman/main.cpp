﻿#define FPS_LIMIT 50
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mingl/mingl.h"
#include "mingl/transition/transition_engine.h"
#include "mingl/audio/audioengine.h"
#include "initialization.h"
#include "general.h"
#include "assertives.h"
#include "game_logic.h"
#include "draw.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace nsTransition;

//int main () {
//    char nb = '1';
//    cout << std::stoul(nb) + 5 << endl;
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

    vector<string> maze = initMaze(param);
    vector<Rectangle> walls = initWalls(maze);

    vector<string> characterList;
    for (auto it = characterMap.begin(); it != characterMap.end(); it++) {
        characterList.push_back(it->first);
    }

    bool isGameRunning (true);
    bool isVictory (false); // value change only if pacman eat all bubbles

    size_t nbBubbleLeft = nbBubbleInMaze(maze);

    // Initalization of the graphics system
    MinGL window("Pacman", Vec2D(1550, 900), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();
    nsTransition::TransitionEngine transitionEngine;
    nsAudio::AudioEngine defaultMusic;
    nsAudio::AudioEngine madMusic;
    nsAudio::AudioEngine gameoverMusic;
    initMusicsEngine(defaultMusic, madMusic, gameoverMusic);

    unsigned score (0);
    bool isTransitionFinished (true);
    unsigned bigBubbleDuration (0);
    unsigned jailGhostDuration (0);
    chrono::microseconds frameTime = chrono::microseconds::zero();
    while (window.isOpen())
    {
        if (isGameRunning){
            if (isTransitionFinished) {
                keyboardInput(window, param, characterMap["Pacman"], maze);
                if (isTeleporter(maze, characterMap["Pacman"])) moveCharacterTeleporter(maze, characterMap["Pacman"], param);
                else if (isBubble(characterMap["Pacman"], maze, score)) eatBubble(characterMap["Pacman"], maze, nbBubbleLeft, score);
                else if (isBigBubble(characterMap["Pacman"], maze, score)) {
                    defaultMusic.playSoundFromFile("../Pacman/audio/pacmanEatingBigBubble.wav");
                    eatBigBubble(characterMap["Pacman"], maze, nbBubbleLeft, score);
                    changeEveryoneState(characterMap, false, defaultMusic, madMusic);
                    bigBubbleDuration = 0;
                }
                checkEating(param, characterMap, isGameRunning, score, defaultMusic);
                tmpMoveGhost(maze, characterMap, param);
                ++bigBubbleDuration;
                if (bigBubbleDuration == 30) {
                    changeEveryoneState(characterMap, true, defaultMusic, madMusic);
                    switchMusic(defaultMusic, madMusic, characterMap["Pacman"].isDefaultState);
                }
                letGhostOut(characterMap, jailGhostDuration, param);
                isTransitionFinished = false;
                launchTransitions(transitionEngine, characterMap, isTransitionFinished, characterList);
            }
        }
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
        window.clearScreen();
        transitionEngine.update(frameTime);
        if (isGameRunning) {
            switchMouthPacmanOpenClose(characterMap["Pacman"], pacmanMouth);
            drawMaze(window, maze, walls, param);
            drawCharacter(window, characterList, characterMap, param);
        }  else {
            if (!gameoverMusic.isMusicPlaying()) {
                defaultMusic.setMusicPlaying(false);
                madMusic.setMusicPlaying(false);
                gameoverMusic.setMusicPlaying(true);
            }
            drawGameOverScreen(window, isVictory, score);
        }
        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
        isBubbleLeft(nbBubbleLeft, isGameRunning, isVictory);
    }
    return 0;
}
