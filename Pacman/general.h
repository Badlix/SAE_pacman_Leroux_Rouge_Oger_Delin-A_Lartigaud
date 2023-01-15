#ifndef GENERAL_H
#define GENERAL_H
#include "mingl/mingl.h"
#include "param.h"
#include "constants.h"
#include <iostream>


// ---------- Game Control ---------- //

/**
 * @fn keyboardInput
 * @brief A function that handles the keyboard input for the player's character.
 * @param window : a reference to the MinGL window object
 * @param param : a reference to the Param object that holds the game's parameters
 * @param pacman : a reference to the player's character
 * @param maze : a reference to the vector of strings representing the current maze
 *
 * The function checks the state of the keys and updates the direction of the character accordingly, it also checks if the new position is possible and call the moveCharacter function to update the character position.
 */
void keyboardInput(MinGL &window, Param &param, Character &pacman, std::vector<std::string> &maze);


/**
 * @fn gameOver
 * @brief A function that sets the game as over by changing the state of the isGameRunning variable.
 * @param isGameRunning : a reference to the boolean variable that holds the state of the game.
 *
 * The function sets the isGameRunning variable to false, indicating that the game is over.
 */
void gameOver(bool &isGameRunning);

/**
 * @fn tmpMoveGhost
 * @brief A function that temporarily moves all the ghosts in the current game.
 * @param maze : a reference to the vector of strings representing the current game's maze
 * @param characterMap : a reference to the map of characters in the current game
 * @param param : a reference to the Param object containing the information of the current game
 *
 * The function iterates through the character map, checks if the current character is a ghost and if it's not in the ghost cage,
 * and gives it a random direction to move in. It then calls the moveCharacter function to move the ghost.
 */
void tmpMoveGhost(std::vector<std::string> &maze, std::map<std::string, Character> &characterMap, Param &param);



// ---------- General Functions ---------- //

/**
 * @fn randomDirection
 * @brief A function that returns a random direction that is possible from the current position of a character.
 * @param pos : a reference to the Position object representing the current position of a character
 * @param maze : a reference to the vector of strings representing the current maze
 * @return string : a random direction that is possible from the current position
 *
 * The function calls the possibleDirections function to get the possible directions from the current position,
 * and returns a random direction from this vector using the rand() function.
 */
std::string randomDirection(Position &pos, std::vector<std::string> &maze);

/**
 * @fn randomCharacter
 * @brief A function that returns a random character from a map of characters.
 * @param characterMap : a reference to the map of characters
 * @return Character : a random character from the map
 *
 * The function uses the rand() function to randomly select an index from the size of the map, and then uses the std::advance function to move an iterator to that index.
 * It then returns the character at that index in the map.
 */
Character randomCharacter(std::map<std::string, Character> &characterMap);

/**
 * @fn nextMove
 * @brief A function that computes the next position of a character based on its current position and direction.
 * @param direction : a reference to the string representing the current direction of the character
 * @param currentPos : a reference to the Position object representing the current position of the character
 * @return Position : the next position of the character based on its current position and direction
 *
 * The function checks the direction and returns the next position accordingly.
 */
Position nextMove(std::string &direction, Position &currentPos);

/**
 * @fn possibleDirections
 * @brief A function that returns a vector of strings representing the directions possible from the current position of a character.
 * @param currentPos : a reference to the Position object representing the current position of a character
 * @param maze : a reference to the vector of strings representing the current maze
 * @return vector<string> : a vector of strings containing the directions possible from the current position.
 *
 * The function checks the elements around the current position in the maze and adds the corresponding direction to the vector if it is free to move.
 */
std::vector<std::string> possibleDirections(Position &currentPos, std::vector<std::string> &maze);


// ---------- "Get" Functions ---------- //


/**
 * @fn getDirection
 * @brief A function that returns the direction of a movement from a starting position to an ending position.
 * @param pos1 : a reference to the starting Position object
 * @param pos2 : a reference to the ending Position object
 * @return string : the direction of the movement (up, down, left, right)
 *
 * The function compares the x and y coordinates of the two positions and returns the corresponding direction of the movement.
 */
std::string getDirection(Position &pos1, Position &pos2);

/**
 * @fn getPosTeleporter
 * @brief A function that returns the positions of the teleporters in the current maze.
 * @param param : a reference to the Param object containing the information of the current game
 * @return vector<Position> : a vector containing the positions of the teleporters in the current maze
 *
 * The function checks the current maze and returns the positions of the teleporters accordingly.
 */
std::vector<Position> getPosTeleporter(Param &param);

/**
 * @fn getPosCage
 * @brief A function that returns the position of the ghost cage in the current maze.
 * @param param : a reference to the Param object containing the information of the current game
 * @return Position : the position of the ghost cage in the current maze
 *
 * The function checks the current maze and returns the position of the ghost cage accordingly.
 */
Position getPosCage(Param &param);


// ---------- Functions used for tests ---------- //

/**
 * @fn showMaze
 * @brief A function that shows the current state of a maze.
 * @param maze : a reference to the vector of strings representing the maze to be displayed
 *
 * The function iterates through the vector of strings and displays the characters of the maze on a line by line basis.
 */
void showMaze(const std::vector<std::string> &maze);

/**
 * @fn showMap
 * @brief A function that shows the current state of a map of characters.
 * @param myMap : a reference to the map of characters to be displayed
 *
 * The function iterates through the map and displays the properties of each character in the map such as its name, position, direction, and default state.
 */
void showMap(const std::map<std::string, Character> &myMap);

#endif // GENERAL_H
