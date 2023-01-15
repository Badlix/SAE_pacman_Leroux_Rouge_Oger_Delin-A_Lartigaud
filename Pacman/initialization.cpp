#include "mingl/audio/audioengine.h"
#include "mingl/shape/rectangle.h"
#include "mingl/graphics/vec2d.h"
#include "constants.h"
#include "param.h"
#include "general.h"
#include <iostream>

using namespace std;

vector<string> initMaze(Param &param) {
    if (param.skins["Maze"] == 1) return maze1;
    else return maze2;
}

vector<nsShape::Rectangle> initWalls(vector<string> &maze) {
    vector<nsShape::Rectangle> walls = {};
    bool isIsolate (true);
    nsGraphics::Vec2D firstPos;
    for (size_t i(0); i < maze.size(); ++i) {
        for (size_t j(0); j < maze[i].size(); ++j) {
            isIsolate = true;
            if(maze[i][j] == '#') {
                firstPos = posBegin + nsGraphics::Vec2D{j*50+10,i*50+10};
                if (j != maze[0].size()-1 && maze[i][j+1] == '#') {
                    walls.push_back(nsShape::Rectangle(firstPos, firstPos+nsGraphics::Vec2D(80,30), nsGraphics::RGBAcolor(15,24,202,255)));
                    isIsolate = false;
                }
                if (i != maze.size()-1 && maze[i+1][j] == '#') {
                    walls.push_back(nsShape::Rectangle(firstPos, firstPos+nsGraphics::Vec2D(30,80), nsGraphics::RGBAcolor(15,24,202,255)));
                    isIsolate = false;
                }
                if (j != 0 && maze[i][j-1] == '#') isIsolate = false;
                if (i != 0 && maze[i-1][j] == '#') isIsolate = false;
                if (isIsolate) {
                    walls.push_back(nsShape::Rectangle(firstPos, firstPos+nsGraphics::Vec2D(30,30), nsGraphics::RGBAcolor(15,24,202,255)));
                }
            }

        }
    }
    return walls;
}

Skin initSkin(string type, string skinName) {
    Skin skin;
    string path = "";
    string notDefaultState = "mad";
    if (type == "Ghost") notDefaultState = "feared";
    vector<string> directions = {"up", "down", "left", "right"};
    for (string &direction : directions) {
        path = "../Pacman/skins/" + type + "/" + skinName + "/" + skinName + "_" + direction + ".si2";
        skin.defaultState.insert({direction,nsGui::Sprite(path, nsGraphics::Vec2D(0,0))});
        path = "../Pacman/skins/" + type + "/" + skinName + "/" +notDefaultState + skinName + "_" + direction + ".si2";
        skin.madState.insert({direction, nsGui::Sprite(path, nsGraphics::Vec2D(0,0))});
    }
    return skin;
}

PacmanMouth initPacmanmouth(Param &param) {
    if (param.skins["Pacman"] == 1) return {initSkin("Pacman", "PacmanDefaultClose"), 0};
    else if (param.skins["Pacman"] == 2) return {initSkin("Pacman", "PenguinClose"), 0};
    else if (param.skins["Pacman"] == 3) return {initSkin("Pacman", "CandyClose"), 0};
    else if (param.skins["Pacman"] == 4) return {initSkin("Pacman", "FlowerClose"), 0};
}

map<string, Character> initCharacters(Param &param) {
    map<string, Character> mapC;
    Skin skin;

    /* Set Pacman Skin*/
    if (param.skins["Pacman"] == 1) skin = initSkin("Pacman", "PacmanDefaultOpen");
    else if (param.skins["Pacman"] == 2) skin = initSkin("Pacman", "PenguinOpen");
    else if (param.skins["Pacman"] == 3) skin = initSkin("Pacman", "CandyOpen");
    else if (param.skins["Pacman"] == 4) skin = initSkin("Pacman", "FlowerOpen");

    Character tmp = {
        "Pacman",  // type
        {20, 10}, // position
        "right", // direction
        true, // isDefaultState
        400, // vitesse
        {nsGui::Sprite({nsGraphics::RGBAcolor{0,0,0,0}}, 1,  nsGraphics::Vec2D(0,0))}, // sprites
        skin
    };
    mapC["Pacman"] = tmp;

    /* Set Ghost1 Skin*/
    if (param.skins["Ghost"] == 1) skin = initSkin("Ghost", "GhostDefault");
    else if (param.skins["Ghost"] == 2) skin = initSkin("Ghost", "IceCream");
    else if (param.skins["Ghost"] == 3) skin = initSkin("Ghost", "Lolipop");
    else if (param.skins["Ghost"] == 4) skin = initSkin("Ghost", "Butterfly");

    tmp = {
        "Ghost",
        Position{getPosCage(param).x, getPosCage(param).y-2},
        "up",
        true,
        350,
        {nsGui::Sprite({nsGraphics::RGBAcolor{0,0,0,0}}, 1,  nsGraphics::Vec2D(0,0))},
        skin
    };
    mapC["Ghost1"] = tmp;
    tmp.pos = getPosCage(param);
    vector<nsGraphics::RGBAcolor> listPixel;
    vector<string> directions = {"up", "down", "right", "left"};

    for (unsigned i(2); i <= param.difficulty["GhostNumber"]; ++i) {
        mapC["Ghost"+to_string(i)] = tmp;
        for (const string &direction : directions) {
            /* change the body color of the ghost */
            listPixel = mapC["Ghost1"].skins.defaultState.find(direction)->second.getPixelData();
            for (nsGraphics::RGBAcolor &pixel : listPixel) {
                if (pixel == skinGhostColors[0] || pixel == nsGraphics::RGBAcolor(255,163,177,255)) {
                    pixel = skinGhostColors[i-1];
                }
            }
            mapC["Ghost"+to_string(i)].skins.defaultState.find(direction)->second = nsGui::Sprite(listPixel, 50, nsGraphics::Vec2D(0,0));
        }
    }
    return mapC;
}

unsigned nbBubbleInMaze(vector<string> &maze){
    unsigned bubbleLeft = 0;
    for (size_t i(0); i < maze.size(); ++i){
        for (size_t j=0; j<maze[i].size(); ++j){
            if (maze[i][j] == '.' || maze[i][j] == 'o'){
                ++bubbleLeft;
            }
        }
    }
    return bubbleLeft;
}

void initPersonality (vector<string> &characterList, map<string, string> personalities, Param &param) {
    //Each personnality has a level of difficulty.
    //The chances of it to drop are in percentage.

    //Initialization of the personalities
    vector<string> easyPersonality {"dumb"};
    vector<string> normalPersonality {"confused"};
    vector<string> hardPersonality {"hardcore"};

    //Initialization of the droprate of each level of difficulty :
    unsigned easy = 100 - 30*param.difficulty["Difficulty"];
    unsigned hard = 30 * param.difficulty["Difficulty"] - 20;
    unsigned normal = 100 - easy - hard ;

    //Application of a random personality to each characters
    unsigned random;
    string personality;
    for (size_t i = 0 ; i < characterList.size() ; ++i) {
        random = rand()%100; // [0,99]
        if (random <= easy) {
            personality = easyPersonality[(rand()%easyPersonality.size())];
            personalities.insert({characterList[i], personality});
        }
        else if (random <= easy+normal){
            personality = normalPersonality[(rand()%normalPersonality.size())];
            personalities.insert({characterList[i], personality});
        }
        else {
            personality = hardPersonality[(rand()%hardPersonality.size())];
            personalities.insert({characterList[i], personality});
        }
    }
}

void initMusicsEngine(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, nsAudio::AudioEngine &gameOverMusic) {
    /* Set the different musics */
    defaultMusic.setMusic("../Pacman/audio/musicDefault.wav");
    madMusic.setMusic("../Pacman/audio/musicMad.wav");
    gameOverMusic.setMusic("../Pacman/audio/musicGameOver.wav");

    /* start all the music */
    defaultMusic.startMusicFromBeginning();
    madMusic.startMusicFromBeginning();
    gameOverMusic.startMusicFromBeginning();

    /* Pause the non necessary music */
    gameOverMusic.setMusicPlaying(false);
    madMusic.setMusicPlaying(false);
}
