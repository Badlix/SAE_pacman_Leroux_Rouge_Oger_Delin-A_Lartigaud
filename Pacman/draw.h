#ifndef DRAW_H
#define DRAW_H
#include "mingl/mingl.h"
#include "constants.h"
#include <iostream>

void drawCage(MinGL &window, nsGraphics::Vec2D pos);

void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth);

void drawCharacter(MinGL &window, std::vector<std::string> &characterList, std::map<std::string, Character> &charactMap);

void drawMaze(MinGL &window, std::vector<std::string> &maze, Param &param);

void launchTransitions(nsTransition::TransitionEngine &t, std::map<std::string, Character> & characterMap, bool &isTransitionFinished, std::vector<std::string> &names);

nsGraphics::Vec2D calcPosTransition(Character &charact);

#endif // DRAW_H
