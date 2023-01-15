/**
 * @file   draw.h
 * @author  Mathieu Leroux, Elliot Lartigaud, Gabriel Rouge, Alexis Delain, Léo Oger
 * @date    Janvier 2023
 * @brief   functions used to draw and played sounds/musics
 **/

#ifndef DRAW_H
#define DRAW_H
#include "mingl/mingl.h"
#include "mingl/audio/audioengine.h"
#include "mingl/transition/transition_engine.h"
#include "constants.h"
#include "param.h"
#include <iostream>

/**
 * @brief switchMusic is a function that switches the music between the default and mad music.
 * @param defaultMusic: the default music.
 * @param madMusic: the mad music.
 * @param pacmanDefaultState: a boolean value that indicates if the pacman is in its default state or not.
 */
void switchMusic(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, const bool &pacmanDefaultState);

/**
 * @brief Draws the cage on the game screen
 * @param window The window where the cage will be drawn
 * @param pos The position of the top-left corner of the cage on the screen
 */
void drawCage(MinGL &window, const nsGraphics::Vec2D pos);

/**
 * @brief Draws the game over screen
 * @param window The MinGL window
 * @param isVictory A boolean indicating if the game ended in a victory or a loss
 * @param score The score of the player
 * @param random An unsigned integer used to select a random sentence to display
 */
void drawGameOverScreen(MinGL &window, const bool &isVictory, const unsigned &score, unsigned &random);

/**
* @brief Function that switch the mouth of the Pacman character between open and closed
* @param pacman The Pacman character object
* @param pacmanMouth The object containing the open and closed state of the Pacman's mouth
*/
void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth);

/**
* @brief This function is used to draw the characters on the screen
* @param window The window where the characters will be drawn
* @param charactMap A map containing the character's information
* @param param An object containing the game's parameters
* This function is used to draw the characters on the screen. It loops through the character map and checks if the character is in its default state or mad state. If it's in the default state, it draws the default sprite of the character based on its current direction. If it's in the mad state, it draws the mad sprite of the character based on its current direction.
*/
void drawCharacter(MinGL &window, std::map<std::string, Character> &charactMap, Param &param);

/**
* @brief This function draws the maze in the window
* @param window The MinGL window where the maze will be drawn
* @param maze The vector of strings representing the maze
* @param walls The vector of Rectangle representing the walls of the maze
* @param param The parameter object that contains the position of the cage
*
* This function draws the maze in the window using the information from the maze vector and the walls vector.
* It also calls the drawCage function if the cage is found in the maze vector.
*/
void drawMaze(MinGL &window, std::vector<std::string> &maze, std::vector<nsShape::Rectangle> &walls, Param &param);

/**
* @brief Launches transitions for specified characters.
* This function uses the TransitionEngine object to calculate the end position of each character based on their current position and speed, and starts a transition contract for each character. If the character is "Pacman", it sets a callback function to set the isTransitionFinished flag to true upon completion of the transition.
* @param t Reference to a TransitionEngine object.
* @param charactMap Reference to a map containing the characters and their information.
* @param isTransitionFinished Reference to a boolean flag indicating whether the transition is finished.
*/
void launchTransitions(nsTransition::TransitionEngine &t, std::map<std::string, Character> & characterMap, bool &isTransitionFinished);

/**
* @brief Calculates the transition position for a character.
* This function takes in a reference to a character position and calculates the transition position using the x and y coordinates of the starting position and the character position.
* @param posCharact Reference to the character's position.
* @return Vec2D The calculated transition position.
*/
nsGraphics::Vec2D calcPosTransition(Position &posCharact);

/**
* @brief Draws the current score in the window.
* This function uses the MinGL object to display the current score using sprites for each digit. The starting position is determined based on the window size and the length of the score.
* @param window Reference to the MinGL object to display the score.
* @param score Reference to the integer containing the current score.
*/
void drawScore(MinGL &window, unsigned &score);

#endif // DRAW_H
