#include "mingl/audio/audioengine.h"
#include "mingl/shape/rectangle.h"
#include "mingl/graphics/vec2d.h"
#include "constants.h"
#include "param.h"
#include "general.h"
#include <iostream>

using namespace std;

/**
 * @fn initMaze
 * @brief A function that returns the initial state of a maze based on the current selection in the game's parameters.
 * @param param : a reference to the game's parameters
 * @return a vector of strings representing the initial state of the selected maze
 *
 * The function checks the current maze selection in the game's parameters and returns the corresponding maze.
 */
vector<string> initMaze(Param &param) {
    if (param.skins["Maze"] == 1) return maze1;
    else return maze2;
}

/**
 * @fn initWalls
 * @brief A function that returns the walls of a maze in the form of a vector of Rectangle shape
 * @param maze : a reference to the current state of the maze
 * @return a vector of nsShape::Rectangle representing the walls of the maze
 *
 * The function iterates through the characters of the maze and checks for the presence of a wall.
 * If a wall is found, it checks its surroundings to determine whether it is an isolated wall or a part of a larger wall.
 * It then constructs the appropriate Rectangle shape and adds it to the vector of walls.
 */
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

/**
* @brief Initialize the skin of a character
* @param type the type of the character (Pacman or Ghost)
* @param skinName the name of the skin to be used
* @return the initialized skin
*/
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

/**
 * @brief Initialize the Pacman mouth
 * @param param : The parameter of the game used to select the skin
 * @return The PacmanMouth struct with the selected skin and the current mouth state (open or closed)
 */
PacmanMouth initPacmanmouth(Param &param) {
    if (param.skins["Pacman"] == 1) return {initSkin("Pacman", "PacmanDefaultClose"), 0};
    else if (param.skins["Pacman"] == 2) return {initSkin("Pacman", "PenguinClose"), 0};
    else if (param.skins["Pacman"] == 3) return {initSkin("Pacman", "CandyClose"), 0};
    else if (param.skins["Pacman"] == 4) return {initSkin("Pacman", "FlowerClose"), 0};
}

/**
 * @brief Initialize the characters for the game.
 *
 * @param param A reference to the Param struct containing the game's settings.
 * @return A map containing all the characters in the game.
 */
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

/**
* @brief Count the number of bubbles in the maze
* @param[in] maze The current state of the maze
* @return The number of bubbles in the maze
*/

size_t nbBubbleInMaze(vector<string> &maze){
    size_t bubbleLeft = 0;
    for (size_t i(0); i < maze.size(); ++i){
        for (size_t j=0; j<maze[i].size(); ++j){
            if (maze[i][j] == '.' || maze[i][j] == 'o'){
                ++bubbleLeft;
            }
        }
    }
    return bubbleLeft;
}

/**
* @brief initialize the personnality of each character
* @param characterList list of characters
* @param personalities map containing the personnality of each character
* @param difficulty the difficulty of the game
*
* This function will randomly assign a personality to each character, based on a drop rate defined by the difficulty
* The easy personality has a 100 - 30*difficulty drop rate
* The normal personality has a 30*difficulty - 20 drop rate
* The hard personality has a 20 drop rate
*/
void initPersonality (vector<string> &characterList, map<string, string> personalities, unsigned &difficulty) {
    //Each personnality has a level of difficulty.
    //The chances of it to drop are in percentage.

    //Initialization of the personalities
    vector<string> easyPersonality {"dumb"};
    vector<string> normalPersonality {"confused"};
    vector<string> hardPersonality {"hardcore"};

    //Initialization of the droprate of each level of difficulty :
    unsigned easy = 100 - 30*difficulty;
    unsigned hard = 30 * difficulty - 20;
    unsigned normal = 100 - easy - hard ;

    //Application of a random personality to each characters
    unsigned random;
    string personality;
    for (size_t i = 0 ; i < characterList.size() ; ++i) {
        random = rand()%100;
        if (random <= easy) {
            personality = easyPersonality[(rand()%easyPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
        else if (random <= easy+normal){
            personality = normalPersonality[(rand()%normalPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
        else {
            personality = hardPersonality[(rand()%hardPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
    }
}


/**
* @brief Initialize the different musics used in the game.
* @param defaultMusic The music played when the game starts or when pacman is not in mad mode.
* @param madMusic The music played when pacman enters mad mode.
* @param gameOverMusic The music played when pacman loses.
*/
void initMusicsEngine(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, nsAudio::AudioEngine &gameOverMusic) {
    /* Set the different musics */
    defaultMusic.setMusic("../Pacman/audio/musicDefault.wav");
    madMusic.setMusic("../Pacman/audio/musicMad.wav");
    gameOverMusic.setMusic("../Pacman/audio/musicGameOver.wav");

    /* start all the music */
    defaultMusic.startMusicFromBeginning();
    madMusic.startMusicFromBeginning();
    gameOverMusic.startMusicFromBeginning();

    /* Pause the non necessary music*/
    gameOverMusic.setMusicPlaying(false);
    madMusic.setMusicPlaying(false);
}
