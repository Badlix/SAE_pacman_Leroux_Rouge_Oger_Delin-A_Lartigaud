#ifndef ASSERTIVES_H
#define ASSERTIVES_H

bool isGhostInCage(Character ghost, Param &param);

/**
 * @brief check if a emplacement is free
 * @param pos : char
 * @return true if free, false if not
 * @fn bool isFree(char &pos)
 */
bool isFree(char &pos);

void isBubbleLeft (size_t &bubbleLeft , bool &gameRunning);

bool isBigBubble (Character &character, vector<string> &maze);

bool isBubble (Character &character, vector<string> &maze);

bool isMovePossible(vector<string> &maze,Character &character, string direction);

bool isTeleporter(vector<string> &maze,Character & character);

bool isSamePos(Character &c1, Character &c2);

#endif // ASSERTIVES_H
