#ifndef PARAM_H
#define PARAM_H
#include <map>
#include <vector>

using namespace std;

struct Param {
    map<string, char> moveKeys;
    map<string, unsigned> skins;
    map<string, unsigned> difficulty;
};

struct AutorizedKeys {
    const vector<string> moveKeys {"KeyUp", "KeyDown", "KeyRight", "KeyLeft"};
    const vector<string> skins {"Maze", "Pacman", "Ghost"};
    const vector<string> difficulty {"GhostNumber"};
};

void loadParams (Param &param);
void checkParam(Param &param, AutorizedKeys &autorizedKeys, string &key, string &value);

#endif // PARAM_H
