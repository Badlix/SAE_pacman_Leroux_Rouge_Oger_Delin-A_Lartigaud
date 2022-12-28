#include <string>
#include <typeinfo>
#include "param.h"
#include "fstream"
#include "iostream"
#include <map>
#include <algorithm>
#include "param.h"

using namespace std;

void checkParam(Param &param, AutorizedKeys &autorizedKeys,string &key, string &value)
{
    if (find(autorizedKeys.moveKeys.begin(), autorizedKeys.moveKeys.end(), key) != autorizedKeys.moveKeys.end()) {
        if (value.size() == 1) {
            param.moveKeys[key] = value[0];
        } else {
            cerr << "Erreur : Les paramètres des touches doivent être un caractère unique" << endl;
        }
    } else if (key == "Ghost" or key == "Pacman" or key == "Maze") {
        if (stoi(value) == 1 || stoi(value) == 2 || stoi(value) == 3) {
            param.skins[key] = stoi(value);
        } else {
            cerr << "Erreur : Les valeurs des skins sont invalide" << endl;
        }
    } else if (key == "GhostNumber") {
        if (stoi(value) == 1 || stoi(value) == 2 || stoi(value) == 3 || stoi(value) == 4) {
            param.difficulty[key] = stoi(value);
        } else {
            cerr << "Erreur : Les nombre de fantome est invalide" << endl;
        }
    } else {
        cerr << "Erreur : key de paramètre invalide -> " << key << endl;
    }
}

void loadParams (Param &param) {
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
