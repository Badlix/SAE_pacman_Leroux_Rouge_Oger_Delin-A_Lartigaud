/**
 * @file   game_logic.h
 * @author  Mathieu Leroux, Elliot Lartigaud, Gabriel Rouge, Alexis Delain, Léo Oger
 * @date    Janvier 2023
 * @brief   gameplay functions
 **/

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "mingl/audio/audioengine.h"
#include "constants.h"
#include "param.h"
#include <iostream>

/**
* @brief Move a character in a specific direction
* @param character the character to move
* @param direction the direction to move the character in ("up", "right", "down", "left")
* @note This function does not check if the move is valid (if the character will collide with a wall for example)
*/
void moveCharacter(Character &character, std::string direction);

/**
* @brief Move the character through the teleporter
* @param maze The current game maze
* @param character The character to move
* @param param The game parameters
*/
void moveCharacterTeleporter(std::vector<std::string> &maze, Character &character, Param& param);

/**
* @brief This function allows the ghosts to leave the jail
* @param mapCharact a map containing all the characters of the game
* @param jailGhostDuration a variable to keep track of the time the ghost stayed in the jail
* @param param contains all the necessary parameters of the game
*/
void letGhostOut(std::map<std::string, Character> &characterMap, unsigned &jailGhostDuration, Param &param);

/**
* @brief Eat a bubble in the current position of the character and increment the score
* @param character : The character that eats the bubble
* @param maze : The current game maze
* @param bubbleLeft : The number of bubble left in the maze
* @param score : The score of the player
*/
void eatBubble(const Character &character, std::vector<std::string> &maze, size_t &bubbleLeft, unsigned &score);

/**
* @brief Change the state of a character
* @param charact The character whose state needs to be changed
* This function changes the state of the character passed as a parameter. It inverts the value of the "isDefaultState" attribute of the character.
* If the character is of type "Pacman", it also modifies the character's speed depending on the new state.
*/
void changeState(Character &charact);

/**
* @brief Change the state of every character in the map to the given value.
* @param mapCharact A map containing all the characters in the game.
* @param newValue The new state that will be applied to every character.
* @param defaultMusic The background music that is played when pacman is in his default state.
* @param madMusic The background music that is played when pacman is in his mad state.
*/
void changeEveryoneState(std::map<std::string, Character> &characterMap, bool newValue, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic);

/**
 * @brief pacman eat a fruit
 * @param mapC
 * @param fruitKey : name of fruit which is the key of the fruit in mapC
 * @param score
 * @fn void eatFruit(std::map<std::string, Character> &mapC, std::string fruitKey, unsigned &score)
 */
void eatFruit(std::map<std::string, Character> &mapC, std::string fruitKey, unsigned &score);

/**
 * @brief swpan a fruit
 * @param fruitDuration Value used as a timer in order to when to spawn a fruit
 * @param maze The current game maze
 * @param characterMap A map containing all the characters in the game.
 */
void fruitSpawn(unsigned &fruitDuration, std::vector<std::string> &maze, std::map<std::string, Character> &characterMap);

/**
* @brief This function is used to make pacman eat the ghost and update the score accordingly
* @param param is used to access the position of the cage where the ghost will be sent
* @param ghost is the ghost that is going to be eaten
* @param score is the current score of the game and will be updated
* @param audioEngine is used to play the sound of pacman eating the ghost
*/
void eatGhost(Param &param, Character &ghost, unsigned &score, nsAudio::AudioEngine &audioEngine);

/**
 * @brief check if a character is eating something
 * @param param is used to access the position of the cage where the ghost will be sent
 * @param mapC is used to access the position of the cage where the ghost will be sent
 * @param maze The current game maze
 * @param isGameRunning
 * @param score is the current score of the game and will be updated
 * @param nbBubbleLeft : The number of bubble left in the maze
 * @param bigBubbleDuration a variable to keep track of the time the pacman stayed in mad mode
 * @param audioEngine is used to play differents sounds effect
 * @fn void checkEating(Param &param, std::map<std::string, Character> &mapC, bool &isGameRunning, unsigned &score, nsAudio::AudioEngine &audioEngine)
 */
void checkEating(Param &param, std::map<std::string, Character> &characterMap, std::vector<std::string> &maze, bool &isGameRunning, unsigned &score, unsigned &nbBubbleLeft, unsigned &bigBubbleDuration, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic);

#endif // GAMELOGIC_H
