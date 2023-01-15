#include "mingl/audio/audioengine.h"
#include "constants.h"
#include "param.h"
#include "assertives.h"
#include "general.h"
#include "draw.h"
#include <iostream>

using namespace std;

/**
* @brief Move a character in a specific direction
* @param character the character to move
* @param direction the direction to move the character in ("up", "right", "down", "left")
* @note This function does not check if the move is valid (if the character will collide with a wall for example)
*/
void moveCharacter(Character &character, string direction) {
    if (direction == "up") --character.pos.y;
    else if (direction == "right") ++character.pos.x;
    else if (direction == "down") ++character.pos.y;
    else if (direction == "left") --character.pos.x;
    character.direction = direction;
}

/**
* @brief Move the character through the teleporter
* @param maze The current game maze
* @param character The character to move
* @param param The game parameters
*/
void moveCharacterTeleporter (vector<string> &maze, Character &character, Param& param) {
    if(isTeleporter(maze, character)){
        if(character.pos == (getPosTeleporter(param))[0]){ // check if the player is on the first teleporter to know on wich teleporter the player have to move.
            character.pos = (getPosTeleporter(param))[1]; // change the positionof the player to set it on the linked teleporter.
        }else if(character.pos == (getPosTeleporter(param))[1]){
                character.pos = (getPosTeleporter(param))[0];
        }
    }
}

/**
* @brief This function allows the ghosts to leave the jail
* @param mapCharact a map containing all the characters of the game
* @param jailGhostDuration a variable to keep track of the time the ghost stayed in the jail
* @param param contains all the necessary parameters of the game
*/
void letGhostOut(std::map<std::string, Character> &mapCharact, unsigned &jailGhostDuration, Param &param) {
    if (isThereAGhostInCage(mapCharact, param)) {
        if (jailGhostDuration > 25) jailGhostDuration = 0;
        for (auto it = mapCharact.begin(); it != mapCharact.end(); it++) {
            if (isGhostInCage(it->second.pos, param) && jailGhostDuration == 25) {
                moveCharacter(it->second, "up");
                break;
            }
        }
    }
    ++jailGhostDuration;
}

/**
* @brief Eat a bubble in the current position of the character and increment the score
* @param character : The character that eats the bubble
* @param maze : The maze where the bubble is located
* @param bubbleLeft : The number of bubble left in the maze
* @param score : The score of the player
*/
void eatBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft, unsigned &score){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
    score += 10;
}

/**
 * @brief Eat a big bubble and update the score
 * This function is called when the character is on a big bubble. It removes the bubble from the maze and increments the score by 50.
 * @param character the character that eat the bubble
 * @param maze the current maze
 * @param bubbleLeft the number of bubble left in the maze
 * @param score the current score
 */
void eatBigBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft, unsigned &score){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
    score += 50;
}

/**
* @brief Change the state of a character
* @param charact The character whose state needs to be changed
* This function changes the state of the character passed as a parameter. It inverts the value of the "isDefaultState" attribute of the character.
* If the character is of type "Pacman", it also modifies the character's speed depending on the new state.
*/
void changeState(Character &charact) {
    charact.isDefaultState = !charact.isDefaultState;
    if (charact.isDefaultState) {
        if (charact.type == "Pacman") charact.vitesse += 100;
    } else {
        if (charact.type == "Pacman") charact.vitesse -= 100;
    }
}

/**
* @brief Change the state of every character in the map to the given value.
* @param mapCharact A map containing all the characters in the game.
* @param newValue The new state that will be applied to every character.
* @param defaultMusic The background music that is played when the characters are in their default state.
* @param madMusic The background music that is played when the characters are in their mad state.
*/
void changeEveryoneState(map<string, Character> &mapCharact, bool newValue, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic) {
    for (auto& charact : mapCharact) {
        if (charact.second.isDefaultState != newValue) changeState(charact.second);
    }
    switchMusic(defaultMusic, madMusic, mapCharact["Pacman"].isDefaultState);
}

/**
* @brief This function is used to make pacman eat the ghost and update the score accordingly
* @param param is used to access the position of the cage where the ghost will be sent
* @param ghost is the ghost that is going to be eaten
* @param score is the current score of the game and will be updated
* @param audioEngine is used to play the sound of pacman eating the ghost
*/
void eatGhost(Param &param, Character &ghost, unsigned &score, nsAudio::AudioEngine &audioEngine) {
    audioEngine.playSoundFromFile("../Pacman/audio/pacmanEatingGhost.wav");
    ghost.pos = getPosCage(param);
    score += 500;
}

//void eatFruit(map<string, Character> &mapC, string fruitKey, unsigned &score) {
//    mapC.erase(fruitKey);
//    score += 200;
//}

void checkEating(Param &param, map<string, Character> &mapC, bool &isGameRunning, unsigned &score, nsAudio::AudioEngine &audioEngine) {
    for (auto it = mapC.begin(); it != mapC.end(); it++) {
        if (it->second.type == "Ghost") {
            if (isSamePos(mapC["Pacman"], it->second) || isEncouterGhostPacman(it->second, mapC["Pacman"])) {
                if (it->second.isDefaultState == true) {
                    audioEngine.playSoundFromFile("../Pacman/audio/pacmanDies.wav");
                    gameOver(isGameRunning);
                } else {
                    eatGhost(param, it->second, score, audioEngine);
                }
            }
        }
//        else if (it->second.type == "Fruit") {
//            if (isSamePos(mapC["Pacman"], it->second)) {
//                eatFruit(mapC, it->first, score);
//            }
//        }
    }
}
