/**
 * @file   initialization.h
 * @author  Mathieu Leroux, Elliot Lartigaud, Gabriel Rouge, Alexis Delain, Léo Oger
 * @date    Janvier 2023
 * @brief   functions used to initialize values
 **/

#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "mingl/audio/audioengine.h"
#include "mingl/shape/rectangle.h"
#include "constants.h"
#include "param.h"
#include <iostream>

/**
 * @fn initMaze
 * @brief A function that returns the initial state of a maze based on the current selection in the game's parameters.
 * @param param : a reference to the game's parameters
 * @return a vector of strings representing the initial state of the selected maze
 *
 * The function checks the current maze selection in the game's parameters and returns the corresponding maze.
 */
std::vector<std::string> initMaze(Param &param);

/**
 * @fn initWalls
 * @brief A function that returns the walls of a maze in the form of a vector of Rectangle shape
 * @param maze : a reference to the current state of the maze
 * @return a vector of nsShape::Rectangle representing the walls of the maze
 *
 * The function iterates through the characters of the maze and checks for the presence of a wall.
 * If a wall is found, it checks its surroundings to determine whether it is an isolated wall or a part of a larger wall.
 * It then constructs the appropriate Rectangle shape and adds it to the vector of walls.
 */
std::vector<nsShape::Rectangle> initWalls(std::vector<std::string> &maze);

/**
 * @brief Initialize the characters for the game.
 *
 * @param param A reference to the Param struct containing the game's settings.
 * @return A map containing all the characters in the game.
 */
std::map<std::string, Character> initCharacters(Param &param);

/**
* @brief Initialize the skin of a character
* @param type the type of the character (Pacman or Ghost)
* @param skinName the name of the skin to be used
* @return the initialized skin
*/
Skin initSkin(std::string type, std::string skinName);

/**
 * @brief Initialize the Pacman mouth
 * @param param : The parameter of the game used to select the skin
 * @return The PacmanMouth struct with the selected skin and the current mouth state (open or closed)
 */
PacmanMouth initPacmanmouth(Param &param);

/**
* @brief Count the number of bubbles in the maze
* @param[in] maze The current state of the maze
* @return The number of bubbles in the maze
*/
unsigned nbBubbleInMaze(std::vector<std::string> &maze);

/**
* @brief initialize the personnality of each character
* @param characterList list of characters
* @param personalities map containing the personnality of each character
* @param difficulty the difficulty of the game
*
* This function will randomly assign a personality to each character, based on a drop rate defined by the difficulty
* The easy personality has a 100 - 30*difficulty drop rate
* The normal personality has a 30*difficulty - 20 drop rate
* The hard personality has a 20 drop rate
*/
void initPersonality (std::vector<std::string> &characterList, std::map<std::string, std::string> personalities, Param &param);

/**
* @brief Initialize the different musics used in the game.
* @param defaultMusic The music played when the game starts or when pacman is not in mad mode.
* @param madMusic The music played when pacman enters mad mode.
* @param gameOverMusic The music played when pacman loses.
*/
void initMusicsEngine(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, nsAudio::AudioEngine &gameOverMusic);

#endif // INITIALIZATION_H
