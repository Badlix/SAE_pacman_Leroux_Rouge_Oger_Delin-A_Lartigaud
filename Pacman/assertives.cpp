#include "constants.h"
#include "param.h"'
#include "general.h"
#include <iostream>

using namespace std;

/**
* @brief A function that checks if a ghost is currently in its cage
* @param posGhost The current position of the ghost
* @param param A struct containing the game's parameters
* @return true if the ghost is in its cage, false otherwise
*/
bool isGhostInCage(const Position &posGhost, Param &param) {
    if (posGhost == getPosCage(param)) {
        return true;
    }
    return false;
}


/**
* @brief A function that checks if the pacman and a ghost have encountered each other
* @param ghost The ghost character
* @param pacman The pacman character
* @return true if the pacman and ghost have encountered each other, false otherwise
*/
bool isEncouterGhostPacman(Character &ghost, Character &pacman) {
    if (ghost.direction == "up" && pacman.direction == "down" && ghost.pos == Position{pacman.pos.x, pacman.pos.y+1}) return true;
    if (ghost.direction == "down" && pacman.direction == "up" && ghost.pos == Position{pacman.pos.x, pacman.pos.y-1}) return true;
    if (ghost.direction == "right" && pacman.direction == "left" && ghost.pos == Position{pacman.pos.x-1, pacman.pos.y}) return true;
    if (ghost.direction == "left" && pacman.direction == "right" && ghost.pos == Position{pacman.pos.x+1, pacman.pos.y}) return true;
    return false;
}


/**
* @brief A function that checks if there is a ghost currently in its cage
* @param mapCharact A map containing all the characters of the game
* @param param A struct containing the game's parameters
* @return true if there is a ghost in its cage, false otherwise
*/
bool isThereAGhostInCage(map<string, Character> &mapCharact, Param &param) {
    for (auto it(mapCharact.begin()) ; it != mapCharact.end() ; ++it) {
        if (isGhostInCage(it->second.pos, param)) return true;
    }
    return false;
}


/**
* @brief A function that checks if a given position is free
* @param pos A character representing the position on the maze
* @return true if the position is free, false otherwise
*/
bool isFree(char &pos){
    if (pos != '#' && pos != '-' && pos != '=') return true;
    else return false;
}

/**
* @brief A function that checks if the pacman is currently on a bubble
* @param character The character object representing Pacman
* @param maze The game's maze
* @param score The current score
* @return true if the pacman is on a bubble, false otherwise
*/
bool isBubble (Character &character, vector<string> &maze, unsigned &score){
    if (character.direction == "up" && (maze[character.pos.y+1][character.pos.x] == '.')) return true;
    else if(character.direction == "down" && (maze[character.pos.y-1][character.pos.x] == '.')) return true;
    else if(character.direction == "left" && (maze[character.pos.y][character.pos.x+1] == '.')) return true;
    else if(character.direction == "right" && (maze[character.pos.y][character.pos.x-1] == '.')) return true;
    else return false;
}



/**
* @brief A function that checks if the pacman is currently on a big bubble
* @param character The character object representing Pacman
* @param maze The game's maze
* @param score The current score
* @return true if the pacman is on a big bubble, false otherwise
*/
bool isBigBubble (Character &character, vector<string> &maze, unsigned &score){
    if (character.direction == "up" && (maze[character.pos.y+1][character.pos.x] == 'o')) return true;
    else if(character.direction == "down" && (maze[character.pos.y-1][character.pos.x] == 'o')) return true;
    else if(character.direction == "left" && (maze[character.pos.y][character.pos.x+1] == 'o')) return true;
    else if(character.direction == "right" && (maze[character.pos.y][character.pos.x-1] == 'o')) return true;
    else return false;
}

/**
* @brief A function that checks if all the bubbles have been eaten and sets the game state accordingly
* @param bubbleLeft The number of bubbles left in the maze
* @param isGameRunning A flag indicating if the game is running
* @param isVictory A flag indicating if the player has won
*/
void isBubbleLeft (size_t &bubbleLeft , bool &isGameRunning, bool &isVictory) {
    if (bubbleLeft == 0){
        gameOver(isGameRunning);
        isVictory = true;
    }
}

/**
* @brief A function that checks if a move is possible
* @param maze The game's maze
* @param character The character object representing Pacman
* @param direction The direction in which the character wants to move
* @return true if the move is possible, false otherwise
*/
bool isMovePossible(vector<string> &maze,Character &character, string direction) {
    // check if the player is going to leave the maze
    if (direction == "up" && character.pos.y <= 0) return false;
    else if (direction == "down" && character.pos.y >= maze.size()-1) return false;
    else if (direction == "left" && character.pos.x <= 0) return false;
    else if (direction == "right" && character.pos.x >= maze[0].size()-1) return false;

    // check if the next position is a wall
    else if ((direction == "up") && (maze[character.pos.y-1][character.pos.x] != '#' && (maze[character.pos.y-1][character.pos.x] != '-' ))) return true;
    else if ((direction == "down") && (maze[character.pos.y+1][character.pos.x] != '#' && (maze[character.pos.y+1][character.pos.x] != '-' ))) return true;
    else if ((direction == "left") && (maze[character.pos.y][character.pos.x-1] != '#' && (maze[character.pos.y][character.pos.x-1] != '-' ))) return true;
    else if ((direction == "right") && (maze[character.pos.y][character.pos.x+1] != '#' && (maze[character.pos.y][character.pos.x+1] != '-' ))) return true;
    else return false;
}



/**
* @brief A function that checks if a character is on a teleporter
* @param maze The game's maze
* @param character The character object representing Pacman
* @return true if the character is on a teleporter and is moving towards it, false otherwise
*/
bool isTeleporter(vector<string> &maze, Character & character) {
    //checking if the player is on a teleporter. If yes, it check if the player is taking the teleporter from the right way.
    if ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "up" && isMovePossible(maze, character, "down")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "down" && isMovePossible(maze, character, "up")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "right" && isMovePossible(maze, character, "left")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "left" && isMovePossible(maze, character, "right")) return true;
    else return false;
}

/**
* @brief A function that checks if two characters have the same position
* @param character1 The first character object 
* @param character2 The second character object
* @return true if the two characters have the same position, false otherwise
*/
bool isSamePos(Character &character1, Character &character2) {
    if (character1.pos == character2.pos) return true;
    else return false;
}
