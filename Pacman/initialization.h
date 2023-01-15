#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "mingl/audio/audioengine.h"
#include "mingl/shape/rectangle.h"
#include "constants.h"
#include "param.h"
#include <iostream>

/**
 * @brief Initialize the game maze
 * @param param A reference to the parameters object
 * @return A vector of strings representing the game maze
 */
std::vector<std::string> initMaze(Param &param);

/**
* @brief Initialize the game walls
* @param maze A reference to the current game maze
* @return A vector of rectangle representing the walls of the maze
*/
std::vector<nsShape::Rectangle> initWalls(std::vector<std::string> &maze);

/**
* @brief Initialize the characters in the game
* @param param A reference to the parameters object
* @return A map of characters in the game, where the key is the character's name and the value is the Character object
*/
std::map<std::string, Character> initCharacters(Param &param);

/**
 * @fn initSkin
 * @brief A function that initializes the skin of a character.
 * @param type : a string that represents the type of the character (Pacman, Ghost, Fruit)
 * @param skinName : a string that represents the name of the skin the user wants to apply
 * @return Skin : the initialized skin
 */
Skin initSkin(std::string type, std::string skinName);

/**
* @brief Initialize the PacmanMouth
* @param param A reference to the parameters object
* @return A PacmanMouth object
*/
PacmanMouth initPacmanmouth(Param &param);

/**
* @brief Count the number of bubbles in the maze
* @param maze A reference to the current game maze
* @return The number of bubbles in the maze
*/
size_t nbBubbleInMaze(std::vector<std::string> &maze);

/**
* @brief Initialize the personality for the characters
* @param characterList A reference to the vector containing the names of the characters in the game
* @param personalities A reference to the map containing the personalities for the characters
* @param difficulty A reference to the difficulty level
*/
void initPersonality (std::vector<std::string> &characterList, std::map<std::string, std::string> personalities, Param &param);

/**
* @brief Initialize the music engine for the game
* @param defaultMusic A reference to the default music engine
* @param madMusic A reference to the music engine played when the player eats a power pellet
* @param gameOverMusic A reference to the music engine played when the player loses
*/
void initMusicsEngine(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, nsAudio::AudioEngine &gameOverMusic);

#endif // INITIALIZATION_H
