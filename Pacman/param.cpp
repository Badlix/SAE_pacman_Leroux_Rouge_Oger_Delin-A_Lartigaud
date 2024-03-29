/**
 * @file   param.cpp
 * @author  Mathieu Leroux, Elliot Lartigaud, Gabriel Rouge, Alexis Delain, Léo Oger
 * @date    Janvier 2023
 * @brief   functions used to load and init settings
 **/

#include "param.h"
#include <typeinfo>
#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void initParam(Param &param) {
    param.moveKeys["KeyUp"] = 'z';
    param.moveKeys["KeyDown"] = 's';
    param.moveKeys["KeyRight"] = 'd';
    param.moveKeys["KeyLeft"] = 'q';
    param.skins["Pacman"] = 1;
    param.skins["Ghost"] = 1;
    param.skins["Maze"] = 1;
    param.difficulty["GhostNumber"] = 4;
    param.difficulty["Difficulty"] = 2;
}

void randomKeys(Param &param, AutorizedKeys &autorizedKeys) {
    srand((unsigned)time(0));
    unsigned random (0);
    vector<char> moveKeys = {'z','q', 's', 'd'};
    vector<char> usedKeys = {};
    while (usedKeys.size() != 4) {
        random = rand()%moveKeys.size();
        if (find(usedKeys.begin(), usedKeys.end(), moveKeys[random]) == usedKeys.end()) {
            cout << moveKeys[random] << endl;
            usedKeys.push_back(moveKeys[random]);
            param.moveKeys[autorizedKeys.moveKeys[usedKeys.size()-1]] = moveKeys[random];
        }
    }
}

void randomSkin(Param &param) {
    param.skins["Pacman"] = rand()%4+1;
    param.skins["Ghost"] = rand()%4+1;
    param.skins["Maze"] = rand()%2+1;
}

/**
 * @brief Check if the key and value from the settings file are authorized 
 * @param param A reference to the parameters object 
 * @param autorizedKeys A reference to the struct that contains the authorized keys, skins and difficulty
 * @param key The key from the settings file
 * @param value The value from the settings file 
 */
void checkParam(Param &param, AutorizedKeys &autorizedKeys, string &key, string &value)
{
    /* check if key is a move keys*/
    if (find(autorizedKeys.moveKeys.begin(), autorizedKeys.moveKeys.end(), key) != autorizedKeys.moveKeys.end()) {
        /* check if move key is a char */
        if (value.size() == 1) {
            param.moveKeys[key] = value[0];
        } else {
            cerr << "Settings Error : '" << key << "' should be a single letter" << endl;
        }

    /* check if key is a skin number */
    } else if (find(autorizedKeys.skins.begin(), autorizedKeys.skins.end(), key) != autorizedKeys.skins.end()) {
        /* check if value is a valid skin number */
        if (value == "1" || value == "2" || value == "3" || value == "4") {
            param.skins[key] = stoi(value);
        } else {
            cerr << "Settings Error : '" << key << "' has an invalid value" << endl;
        }

    /* check if key is the number of ghosts */
    } else if (find(autorizedKeys.difficulty.begin(), autorizedKeys.difficulty.end(), key) != autorizedKeys.difficulty.end()) {
        /* check if value is a valid number of ghosts */
        if (value == "1" || value == "2" || value == "3" || value == "4") {
            param.difficulty[key] = stoi(value);
        } else if ((value == "3" || value == "4") && key != "Difficulty") {
            param.difficulty[key] = stoi(value);
        } else {
            cerr << "Settings Error : '" << key << "' has an invalid value" << endl;
        }
    } else if (key == "RandomKeys") {
        if (value == "true") randomKeys(param, autorizedKeys);
    } else if (key == "RandomSkins") {
        if (value == "true") randomSkin(param);
    } else {
        cerr << "Settings Error : '" << key << "' is an invalid key name" << endl;
    }
}

/**
 * @brief Load the game parameters from the settings file
 * @param param A reference to the parameters object to be loaded
 */
void loadParam(Param &param) {
    ifstream file("../Pacman/settings.yaml");
    string line;
    string key;
    string value;
    size_t index; // index of ":"
    AutorizedKeys autorizedKeys;
    while(true) {
        getline(file, line);
        if(file.eof()) break;
        if (line[0] != '#' && line.size() != 0) {
            index = line.find(":");
            key = line.substr(0, index-1);
            value = line.substr(index+2);
            checkParam(param, autorizedKeys, key, value);
        }
    }
}
