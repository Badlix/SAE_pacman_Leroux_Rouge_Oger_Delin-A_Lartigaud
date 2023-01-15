/**
 * @file   game_logic.cpp
 * @author  Mathieu Leroux, Elliot Lartigaud, Gabriel Rouge, Alexis Delain, Léo Oger
 * @date    Janvier 2023
 * @brief   gameplay functions
 **/

#include "mingl/audio/audioengine.h"
#include "constants.h"
#include "param.h"
#include "assertives.h"
#include "general.h"
#include "draw.h"
#include <iostream>

using namespace std;

void moveCharacter(Character &character, string direction) {
    if (direction == "up") --character.pos.y;
    else if (direction == "right") ++character.pos.x;
    else if (direction == "down") ++character.pos.y;
    else if (direction == "left") --character.pos.x;
    character.direction = direction;
}

void moveCharacterTeleporter (vector<string> &maze, Character &character, Param& param) {
    if(isTeleporter(maze, character)){
        if(character.pos == (getPosTeleporter(param))[0]){ // check if the player is on the first teleporter to know on wich teleporter the player have to move.
            character.pos = (getPosTeleporter(param))[1]; // change the positionof the player to set it on the linked teleporter.
        }else if(character.pos == (getPosTeleporter(param))[1]){
                character.pos = (getPosTeleporter(param))[0];
        }
    }
}

void letGhostOut(std::map<std::string, Character> &characterMap, unsigned &jailGhostDuration, Param &param) {
    if (isThereAGhostInCage(characterMap, param)) {
        if (jailGhostDuration > 15) jailGhostDuration = 0;
        for (auto it = characterMap.begin(); it != characterMap.end(); it++) {
            if (isGhostInCage(it->second.pos, param) && jailGhostDuration == 25) {
                moveCharacter(it->second, "up");
                break;
            }
        }
    }
    ++jailGhostDuration;
}

void eatBubble (const Character &character, vector<string> &maze, unsigned &bubbleLeft, unsigned &score){
    if (isBubble(character.pos, maze)) score += 10;
    if (isBigBubble(character.pos, maze)) score += 50;
    maze[character.pos.y][character.pos.x] = ' ';
    bubbleLeft -= 1;
}

void changeState(Character &charact) {
    charact.isDefaultState = !charact.isDefaultState;
    if (charact.isDefaultState) {
        if (charact.type == "Pacman") charact.vitesse += 100;
    } else {
        if (charact.type == "Pacman") charact.vitesse -= 100;
    }
}

void changeEveryoneState(map<string, Character> &characterMap, bool newValue, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic) {
    for (auto& charact : characterMap) {
        if (charact.second.isDefaultState != newValue) changeState(charact.second);
    }
    switchMusic(defaultMusic, madMusic, characterMap["Pacman"].isDefaultState);
}

void eatGhost(Param &param, Character &ghost, unsigned &score, nsAudio::AudioEngine &audioEngine) {
    audioEngine.playSoundFromFile("../Pacman/audio/pacmanEatingGhost.wav");
    ghost.pos = getPosCage(param);
    score += 500;
}

//void eatFruit(map<string, Character> &mapC, string fruitKey, unsigned &score) {
//    mapC.erase(fruitKey);
//    score += 200;
//}

void checkEating(Param &param, map<string, Character> &characterMap, vector<string> &maze, bool &isGameRunning, unsigned &score, unsigned &nbBubbleLeft, unsigned &bigBubbleDuration, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic) {
    if (isBubble(characterMap["Pacman"].pos, maze)) eatBubble(characterMap["Pacman"], maze, nbBubbleLeft, score);
    if (isBigBubble(characterMap["Pacman"].pos, maze)) {
        eatBubble(characterMap["Pacman"], maze, nbBubbleLeft, score);
        defaultMusic.playSoundFromFile("../Pacman/audio/pacmanEatingBigBubble.wav");
        changeEveryoneState(characterMap, false, defaultMusic, madMusic);
        bigBubbleDuration = 0;
    }
    ++bigBubbleDuration;
    for (auto it = characterMap.begin(); it != characterMap.end(); it++) {
        if (it->second.type == "Ghost") {
            if (isSamePos(characterMap["Pacman"], it->second) || isEncouterGhostPacman(it->second, characterMap["Pacman"])) {
                if (it->second.isDefaultState == true) {
                    defaultMusic.playSoundFromFile("../Pacman/audio/pacmanDies.wav");
                    gameOver(isGameRunning);
                } else {
                    eatGhost(param, it->second, score, defaultMusic);
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
