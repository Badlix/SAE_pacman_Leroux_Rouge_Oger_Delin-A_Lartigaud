#ifndef GENERAL_H
#define GENERAL_H

// game control

void keyboardInput(MinGL &window, Param &param, Character &pacman, vector<string> &maze);

void gameOver(bool &gameRunning);

// general functions

/**
 * @brief give a random direction to go
 * @param pos : Position
 * @param maze : vector<string>
 * @return a random direction
 * @fn string randomDirection(Position &pos, vector<string> &maze)
 */
string randomDirection(Position &pos, vector<string> &maze);

/**
 * @brief give a random character
 * @param characters : map<string, Character>
 * @param characterList : vector<string>
 * @return a random character
 * @fn Character randomCharacter(map<string, Character> &characters, vector<string> &characterList)
 */
Character randomCharacter(map<string, Character> &characters, vector<string> &characterList);

/**
 * @brief give the position in wich the direction goes
 * @param direction : string
 * @param currentPos : Position
 * @return the Position in wich the direction goes
 * @fn Position nextMove(string &direction, Position &currentPos)
 */
Position nextMove(string &direction, Position &currentPos);

/**
 * @brief give all the possible directions from a given position
 * @param currentPos : Position
 * @param maze : vector<string>
 * @return the list of the possible directions
 * @fn vector<string> possibleDirections(Position &currentPos, vector<string> &maze)
 */
vector<string> possibleDirections(Position &currentPos, vector<string> &maze);

/**
 * @brief give the direction used to go from the first position to the second
 * @param pos1 : Position
 * @param pos2 : Position
 * @return the direction used to go from the first position to the second
 * @fn string getDirection(Position &pos1, Position &pos2)
 */
string getDirection(Position &pos1, Position &pos2);

vector<Position> getPosTeleporter(Param &param);

Position getPosCage(Param &param);

// tests

void showMaze(const vector<string> &maze);

void showMap(map<string, Character> &myMap);

#endif // GENERAL_H
