#ifndef DRAW_H
#define DRAW_H
#include "mingl/mingl.h"
#include "mingl/audio/audioengine.h"
#include "mingl/transition/transition_engine.h"
#include "constants.h"
#include "param.h"
#include <iostream>

/**
 * @brief switch between default and mad music
 * @param defaultMusic : defaultMusic engine
 * @param madMusic : madMusic engine
 * @param[in] pacmanDefaultState
 * @fn void switchMusic(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, const bool &pacmanDefaultState)
 */
void switchMusic(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, const bool &pacmanDefaultState);

/**
 * @brief draw the cage
 * @param window
 * @param pos : pos of the left-up corner of the cage
 * @fn void drawCage(MinGL &window, const nsGraphics::Vec2D pos)
 */
void drawCage(MinGL &window, const nsGraphics::Vec2D pos);

/**
 * @brief draw the gameOver screen
 * @param window
 * @param[in] isVictory
 * @param[in] score
 * @fn void drawGameOverScreen(MinGL &window, const bool &isVictory, const unsigned &score)
 */
void drawGameOverScreen(MinGL &window, const bool &isVictory, const unsigned &score);

/**
 * @brief make the mouvement of the mouth (open/close)
 * @param pacman
 * @param pacmanMouth
 * @fn void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth)
 */
void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth);

/**
 * @brief draw all characters
 * @param window
 * @param characterList
 * @param charactMap
 * @param param
 * @fn void drawCharacter(MinGL &window, const std::vector<std::string> &characterList, const std::map<std::string, Character> &charactMap, const Param &param)
 */
void drawCharacter(MinGL &window, std::vector<std::string> &characterList, std::map<std::string, Character> &charactMap, Param &param);

/**
 * @brief draw the maze
 * @param window
 * @param[in] maze
 * @param param
 * @fn void drawMaze(MinGL &window, const std::vector<std::string> &maze, Param &param)
 */
void drawMaze(MinGL &window, const std::vector<std::string> &maze, Param &param);

/**
 * @brief launch the movement transition of all characters
 * @param t : the transition engine
 * @param characterMap
 * @param isTransitionFinished
 * @param names : list of characters name
 */
void launchTransitions(nsTransition::TransitionEngine &t, std::map<std::string, Character> & characterMap, bool &isTransitionFinished, std::vector<std::string> &names);

/**
 * @brief calculate the ending position of a transition
 * @param charact
 * @return the coordinate of the ending position
 * @fn nsGraphics::Vec2D calcPosTransition(Position &posCharact)
 */
nsGraphics::Vec2D calcPosTransition(Position &posCharact);

#endif // DRAW_H
