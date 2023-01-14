#ifndef DRAW_H
#define DRAW_H
#include "mingl/mingl.h"
#include "mingl/audio/audioengine.h"
#include "mingl/transition/transition_engine.h"
#include "constants.h"
#include "param.h"
#include <iostream>

void switchMusic(nsAudio::AudioEngine &defaultMusicEngine, nsAudio::AudioEngine &madMusicEngine, bool &pacmanDefaultState);

void drawCage(MinGL &window, nsGraphics::Vec2D pos);

void drawGameOverScreen(MinGL &window, bool &isVictory, unsigned &score);

void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth);

void drawCharacter(MinGL &window, std::vector<std::string> &characterList, std::map<std::string, Character> &charactMap, Param &param);

void drawMaze(MinGL &window, std::vector<std::string> &maze, Param &param);

void launchTransitions(nsTransition::TransitionEngine &t, std::map<std::string, Character> & characterMap, bool &isTransitionFinished, std::vector<std::string> &names);

nsGraphics::Vec2D calcPosTransition(Character &charact);

#endif // DRAW_H
