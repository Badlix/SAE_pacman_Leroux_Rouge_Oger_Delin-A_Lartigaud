#ifndef DRAW_H
#define DRAW_H

void drawCage(MinGL &window, Vec2D pos);

void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth);

void drawCharacter(MinGL &window, vector<string> &characterList, map<string, Character> &charactMap);

void drawMaze(MinGL &window, vector<string> &maze, Param &param);

void launchTransitions(nsTransition::TransitionEngine &t, map<string, Character> & characterMap, bool &isTransitionFinished, vector<string> &names);

nsGraphics::Vec2D calcPosTransition(Character &charact);

#endif // DRAW_H
