#include "mingl/audio/audioengine.h"
#include "constants.h"
#include "param.h"
#include "assertives.h"
#include "general.h"
#include "draw.h"
#include "ghost_intelligence.h"
#include <iostream>

using namespace std;

void moveCharacter(Character &character, string direction) {
    if (direction == "up") --character.pos.y;
    else if (direction == "right") ++character.pos.x;
    else if (direction == "down") ++character.pos.y;
    else if (direction == "left") --character.pos.x;
    character.direction = direction;
}

void moveAllGhost(vector<string> &maze, map<string, Character> &characterMap, vector<string> &characterList,  map<string, string> &personnalities, Param &param) {
    for (auto it (characterMap.begin()) ; it != characterMap.end() ; ++it) {
        if (it->second.type == "Ghost") {
            if (it->second.type == "Ghost" && it->second.pos == getPosCage(param)) continue;
            it->second.direction = decideGhostDirection(it->second, personnalities.find(it->first)->second, param.difficulty["Difficulty"], maze, characterMap["Pacman"].pos, characterMap, characterList);
            moveCharacter(it->second, it->second.direction);
        }
    }
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

void eatBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft, unsigned &score){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
    score += 10;
}

void eatBigBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft, unsigned &score){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
    score += 50;
}

void changeState(Character &charact) {
    charact.isDefaultState = !charact.isDefaultState;
    if (charact.isDefaultState) {
        if (charact.type == "Pacman") charact.vitesse += 100;
    } else {
        if (charact.type == "Pacman") charact.vitesse -= 100;
    }
}

void changeEveryoneState(map<string, Character> &mapCharact, bool newValue, nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic) {
    for (auto& charact : mapCharact) {
        if (charact.second.isDefaultState != newValue) changeState(charact.second);
    }
    switchMusic(defaultMusic, madMusic, mapCharact["Pacman"].isDefaultState);
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
