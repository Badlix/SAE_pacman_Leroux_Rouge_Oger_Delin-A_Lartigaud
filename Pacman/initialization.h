#ifndef INITIALIZATION_H
#define INITIALIZATION_H

vector<string> initMaze(Param &param);

map<string, Character> initCharacters(Param &param);

PacmanMouth initPacmanmouth(Param &param);

size_t nbBubbleInMaze(vector<string> &maze);

void initPersonality (vector<string> &characterList, map<string, string> personalities, unsigned &difficulty);

#endif // INITIALIZATION_H
