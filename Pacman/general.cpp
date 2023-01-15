#include "mingl/mingl.h"
#include "param.h"
#include "constants.h"
#include "game_logic.h"
#include "assertives.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

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
void keyboardInput(MinGL &window, Param &param, Character &pacman, vector<string> &maze){
    // called inbetween every transition
    // allows to press many directions simultanuously without causing errors and fluidify the movements and the ergonomy
    if(window.isPressed({param.moveKeys["KeyUp"], false}) && pacman.direction != "up" && (isMovePossible(maze,pacman, "up"))) {
            moveCharacter(pacman, "up");
    }
    else if(window.isPressed({param.moveKeys["KeyRight"], false}) && pacman.direction != "right" && (isMovePossible(maze,pacman, "right"))) {
            moveCharacter(pacman, "right");
    }
    else if(window.isPressed({param.moveKeys["KeyDown"], false}) && pacman.direction != "down" && (isMovePossible(maze,pacman, "down"))) {
            moveCharacter(pacman, "down");
    }
    else if(window.isPressed({param.moveKeys["KeyLeft"], false}) && pacman.direction != "left" && (isMovePossible(maze,pacman, "left"))) {
            moveCharacter(pacman, "left");
    }
    else if (isMovePossible(maze,pacman, pacman.direction)){
            moveCharacter(pacman, pacman.direction);// continue in the same direction
    }
}

/**
 * @fn gameOver
 * @brief A function that sets the game as over by changing the state of the isGameRunning variable.
 * @param isGameRunning : a reference to the boolean variable that holds the state of the game.
 *
 * The function sets the isGameRunning variable to false, indicating that the game is over.
 */
void gameOver(bool &isGameRunning) {
    isGameRunning = false;
}

// ---------- General Functions ---------- //

/**
 * @fn possibleDirections
 * @brief A function that returns a vector of strings representing the directions possible from the current position of a character.
 * @param currentPos : a reference to the Position object representing the current position of a character
 * @param maze : a reference to the vector of strings representing the current maze
 * @return vector<string> : a vector of strings containing the directions possible from the current position.
 *
 * The function checks the elements around the current position in the maze and adds the corresponding direction to the vector if it is free to move.
 */
vector<string> possibleDirections(Position &currentPos, vector<string> &maze){
    vector<string> directions = {};
    if (isFree(maze[currentPos.y-1][currentPos.x])) directions.push_back("up");
    if (isFree(maze[currentPos.y+1][currentPos.x])) directions.push_back("down");
    if (isFree(maze[currentPos.y][currentPos.x-1])) directions.push_back("left");
    if (isFree(maze[currentPos.y][currentPos.x+1])) directions.push_back("right");
    return directions;
}

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
string randomDirection(Position &pos, vector<string> &maze){
    vector<string> directions = possibleDirections(pos, maze);
    return directions[rand()%(directions.size())];
    // rand between [0, directions.size()-1]
}

/**
 * @fn randomCharacter
 * @brief A function that returns a random character from a map of characters.
 * @param characterMap : a reference to the map of characters
 * @return Character : a random character from the map
 *
 * The function uses the rand() function to randomly select an index from the size of the map, and then uses the std::advance function to move an iterator to that index. 
 * It then returns the character at that index in the map.
 */
Character randomCharacter(map<string, Character> &characterMap) {
    auto it = characterMap.begin();
    cout << rand()%characterMap.size() << endl;
    std::advance(it, rand()%characterMap.size());
    return it->second;
}

/**
 * @fn nextMove
 * @brief A function that computes the next position of a character based on its current position and direction.
 * @param direction : a reference to the string representing the current direction of the character
 * @param currentPos : a reference to the Position object representing the current position of the character
 * @return Position : the next position of the character based on its current position and direction
 *
 * The function checks the direction and returns the next position accordingly.
 */
Position nextMove(string &direction, Position &currentPos){
    //Give the next Position going from the current Position (&currentPos) by a given direction (&direction).
    if (direction == "up") return Position{currentPos.x, currentPos.y-1};
    else if (direction == "down") return Position{currentPos.x, currentPos.y+1};
    else if (direction == "left") return Position{currentPos.x-1, currentPos.y};
    else if (direction == "right") return Position{currentPos.x+1, currentPos.y};
}

/**
 * @fn getDirection
 * @brief A function that returns the direction of a movement from a starting position to an ending position.
 * @param pos1 : a reference to the starting Position object
 * @param pos2 : a reference to the ending Position object
 * @return string : the direction of the movement (up, down, left, right)
 *
 * The function compares the x and y coordinates of the two positions and returns the corresponding direction of the movement.
 */
string getDirection(Position &pos1, Position &pos2){
    //Give the direction used to go from &pos1 to &pos2
    if ( pos1.x == pos2.x && pos1.y-1 == pos2.y ) return "up";
    else if ( pos1.x == pos2.x && pos1.y+1 == pos2.y ) return "down";
    else if ( pos1.x-1 == pos2.x && pos1.y == pos2.y ) return "left";
    else if ( pos1.x+1 == pos2.x && pos1.y == pos2.y )return "right";
}

/**
 * @fn getPosTeleporter
 * @brief A function that returns the positions of the teleporters in the current maze.
 * @param param : a reference to the Param object containing the information of the current game
 * @return vector<Position> : a vector containing the positions of the teleporters in the current maze
 *
 * The function checks the current maze and returns the positions of the teleporters accordingly.
 */
vector<Position> getPosTeleporter(Param &param) {
    if (param.skins["Maze"] == 1) {
        return {{11,0}, {11,11}};
    } else if (param.skins["Maze"] == 2) {
        return {{0,5},{22,5}}; // take the position of the two teleporter on the first map
    }
    return {{0,0}, {0,0}};
}

/**
 * @fn getPosCage
 * @brief A function that returns the position of the ghost cage in the current maze.
 * @param param : a reference to the Param object containing the information of the current game
 * @return Position : the position of the ghost cage in the current maze
 *
 * The function checks the current maze and returns the position of the ghost cage accordingly.
 */
Position getPosCage(Param &param) {
    if (param.skins["Maze"] == 1) return {20, 3};
    else if (param.skins["Maze"] == 2) return {15, 7};
    return {0,0};
}

// ---------- Functions used for tests ---------- //


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
void tmpMoveGhost(std::vector<std::string> &maze, map<std::string, Character> &characterMap, Param &param) {
    for (auto it (characterMap.begin()) ; it != characterMap.end() ; ++it) {
        if (it->second.type == "Ghost") {
            if (it->second.type == "Ghost" && it->second.pos == getPosCage(param)) continue;
            it->second.direction = randomDirection(it->second.pos, maze);
            moveCharacter(it->second, it->second.direction);
        }
    }
}

/**
 * @fn showMap
 * @brief A function that shows the current state of a map of characters.
 * @param myMap : a reference to the map of characters to be displayed
 *
 * The function iterates through the map and displays the properties of each character in the map such as its name, position, direction, and default state.
 */
void showMap(const std::map<string, Character> &myMap) {
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        cout << it->first << " -> ";
        cout << " pos.x : " << it->second.pos.x;
        cout << "  |  pos.y : " << it->second.pos.y;
        cout << "  |  direction : " << it->second.direction;
        cout << "  |  isDefaultState : " << it->second.isDefaultState << endl;
    }
}

/**
 * @fn showMaze
 * @brief A function that shows the current state of a maze.
 * @param maze : a reference to the vector of strings representing the maze to be displayed
 *
 * The function iterates through the vector of strings and displays the characters of the maze on a line by line basis.
 */
void showMaze(const vector<string> & maze) {
    for (const string &line : maze) {
        for (char c : line) {
            cout << c << ' ';
        }
        cout << endl;
    }
}

