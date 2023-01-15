#ifndef PARAM_H
#define PARAM_H
#include <iostream>
#include <map>
#include <vector>

/**
* @brief A struct that holds the parameter of the game
*/
struct Param {
    std::map<std::string, char> moveKeys;
    /**< map of keys used to move the characters */
    std::map<std::string, unsigned> skins;
    /**< map of skins used to display the characters */
    std::map<std::string, unsigned> difficulty;
    /**< map of difficulty level for the game */
};


/**
* @brief A struct that holds the authorized keys, skins and difficulty level for the game
*/
struct AutorizedKeys {
    const std::vector<std::string> moveKeys {"KeyUp", "KeyDown", "KeyRight", "KeyLeft"};
    /**< list of authorized keys for movement */
    const std::vector<std::string> skins {"Maze", "Pacman", "Ghost"};
    /**< list of authorized skins for characters */
    const std::vector<std::string> difficulty {"GhostNumber", "Difficulty"};
    /**< list of authorized difficulty level */
}; 

/**
* @brief Initialize the Param struct with default values.
* @param[in,out] param The struct that holds the parameter's values.
*/
void initParam(Param &param);

/**
* @brief Load the parameters from a file.
* @param[in,out] param The struct that holds the parameter's values.
*/
void loadParam(Param &param);

/**
* @brief Check if the key and value are valid and store them in the param struct
* @param[in,out] param The struct that holds the parameter's values.
* @param[in] autorizedKeys The struct that holds the authorized keys, skins and difficulty level for the game.
* @param[in] key The key of the parameter.
* @param[in] value The value of the parameter.
*/
void checkParam(Param &param, AutorizedKeys &autorizedKeys, std::string &key, std::string &value);


#endif // PARAM_H
