#ifndef PARAM_H
#define PARAM_H
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Param {
    std::map<std::string, char> moveKeys;
    std::map<std::string, unsigned> skins;
    std::map<std::string, unsigned> difficulty;
};

struct AutorizedKeys {
    const std::vector<std::string> moveKeys {"KeyUp", "KeyDown", "KeyRight", "KeyLeft"};
    const std::vector<std::string> skins {"Maze", "Pacman", "Ghost"};
    const std::vector<std::string> difficulty {"GhostNumber"};
};

void initParam(Param &param);
void loadParam(Param &param);
void checkParam(Param &param, AutorizedKeys &autorizedKeys, std::string &key, std::string &value);

#endif // PARAM_H
