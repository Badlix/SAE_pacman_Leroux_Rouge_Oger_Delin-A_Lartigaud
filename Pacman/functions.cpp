#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/transition/transition_engine.h"
#include "functions.h"
#include "param.h"
#include "constants.h"
#include "ghost.h"
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
using namespace nsTransition;
using namespace nsGraphics;
using namespace nsShape;


// ---------- Functions used to move ---------- //

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

void moveCharacter(Character &character, string direction) {
    if (direction == "up") --character.pos.y;
    else if (direction == "right") ++character.pos.x;
    else if (direction == "down") ++character.pos.y;
    else if (direction == "left") --character.pos.x;
    character.direction = direction;
}

void moveCharacterTeleporter (vector<string> &maze, Character &character, Param& param) {
    if(isTeleporter(maze,character)){
        if(character.pos == (getPosTeleporter(param))[0]){ // check if the player is on the first teleporter to know on wich teleporter the player have to move.
            character.pos = (getPosTeleporter(param))[1]; // change the positionof the player to set it on the linked teleporter.
        }else if(character.pos == (getPosTeleporter(param))[1]){
                character.pos = (getPosTeleporter(param))[0];
        }
    }
}

bool isTeleporter(vector<string> &maze, Character & character) {
    //checking if the player is on a teleporter. If yes, it check if the player is taking the teleporter from the right way.
    if ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "up" && isMovePossible(maze, character, "down")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "down" && isMovePossible(maze, character, "up")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "right" && isMovePossible(maze, character, "left")) return true;
    else if  ((maze[character.pos.y][character.pos.x] == '=') && character.direction == "left" && isMovePossible(maze, character, "right")) return true;
    else return false;
}

Vec2D calcPosTransition(Character &charact) {
    return {posBegin.getX() + charact.pos.x*50, posBegin.getY() + charact.pos.y*50};
}

bool isSamePos(Character &c1, Character &c2) {
    if (c1.pos == c2.pos) return true;
    else return false;
}

// ---------- Functions used in initialisation ---------- //

vector<string> initMaze(Param &param) {
    if (param.skins["Maze"] == 1) return maze1;
    else return maze2;
}

PacmanMouth initPacmanmouth(Param &param) {
    if (param.skins["Pacman"] == 1) return {flowerPacmanClose, 0};
}

map<string, Character> initCharacters(Param &param) {
    map<string, Character> mapC;
    /* Set Pacman Skin*/
    Skin skin;
    Skin skinMouthClose;
    if (param.skins["Pacman"] == 1) {skin = flowerPacman; skinMouthClose = flowerPacmanClose;}
    /*else if (param.skins["Pacman"] == 2) {skin = candyPacman; skinMouthClose = flowerPacmanClose;}
    else if (param.skins["Pacman"] == 3) {skin = penguinPacman; skinMouthClose = penguinPacmanClose;}*/

    Character tmp = {
        "Pacman",  // type
        {1, 1}, // position
        "right", // direction
        true, // isDefaultState
        400, // vitesse
        {nsGui::Sprite({RGBAcolor{0,0,0,0}}, 1,  nsGraphics::Vec2D(0,0))}, // sprites
        skin
    };
    mapC["Pacman"] = tmp;

    /* Set Ghost1 Skin*/
    if (param.skins["Ghost"] == 1) skin = butterflyGhost;
//    else if (param.skins["Ghost"] == 2) skin = lolipopGhost;
//    else if (param.skins["Ghost"] == 3) skin = iceCreamGhost;

    tmp = {
        "Ghost",
        getPosCage(param),
        "up",
        true,
        500,
        {nsGui::Sprite({RGBAcolor{0,0,0,0}}, 1,  nsGraphics::Vec2D(0,0))},
        skin
    };
    mapC["Ghost1"] = tmp;
    vector<RGBAcolor> listPixel;
    vector<string> directions = {"up", "down", "right", "left"};
    for (unsigned i(2); i <= param.difficulty["GhostNumber"]; ++i) {
        mapC["Ghost"+to_string(i)] = tmp;
        mapC["Ghost"+to_string(i)].pos = {i,i};
        for (const string &direction : directions) {
            listPixel = mapC["Ghost1"].skins.defaultState.find(direction)->second.getPixelData();
            for (RGBAcolor &pixel : listPixel) {
                if (pixel == skinGhostColors[0]) {
                    pixel = skinGhostColors[i-1];
                }
            }
            mapC["Ghost"+to_string(i)].skins.defaultState.find(direction)->second = nsGui::Sprite(listPixel, 50, nsGraphics::Vec2D(0,0));
        }
    }
    return mapC;
}

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

// ---------- Functions used to draw ---------- //

void drawCage(MinGL &window, Vec2D pos) {
    window << Line(pos, pos + Vec2D(1*50, 0), KSilver, 5.0);
    window << Line(pos + Vec2D(2*50,0), pos + Vec2D{3*50, 0}, KSilver, 5.0);
    window << Line(pos, pos + Vec2D{0, 2*50}, KSilver, 5.0);
    window << Line(pos + Vec2D(3*50,0), pos + Vec2D{3*50, 2*50}, KSilver, 5.0);
    window << Line(pos + Vec2D(0, 2*50), pos + Vec2D(3*50, 2*50), KSilver, 5.0);
    window << Line(pos + Vec2D(1*50, 0), pos + Vec2D(2*50, 0), KSilver, 1.0);
}

void drawMaze(MinGL &window, vector<string> &maze, Param &param) {
    for (size_t i(0); i < maze.size(); ++i) {
        for (size_t j(0); j < maze[0].size(); ++j) {
            switch (maze[i][j]) {
            case '#':
                window << Rectangle(posBegin + Vec2D(j*50,i*50), posBegin + Vec2D(j*50+50, i*50+50), KBlue);
                break;
            case '.':
                window << Circle(posBegin + Vec2D(j*50+25, i*50+25), 3, KYellow);
                break;
            case 'o':
                window << Circle(posBegin + Vec2D(j*50+25, i*50+25), 8, KYellow);
                break;
            case '-':
                if (getPosCage(param).x-1 == j && getPosCage(param).y-1 == i) {
                    drawCage(window, posBegin+Vec2D(j*50, i*50));
                }
            }
        }
    }
}

void drawCharacter(MinGL &window, vector<string> &characterList, map<string, Character> &charactMap) {
    for (string &name : characterList) {
        if (charactMap[name].isDefaultState) {
            charactMap[name].skins.defaultState.find(charactMap[name].direction)->second.setPosition(charactMap[name].sprite[0].getPosition());
            window << charactMap[name].skins.defaultState.find(charactMap[name].direction)->second;
        } else {
            charactMap[name].skins.madState.find(charactMap[name].direction)->second.setPosition(charactMap[name].sprite[0].getPosition());
            window << charactMap[name].skins.madState.find(charactMap[name].direction)->second;
        }
    }
}

void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth) {
    if (pacmanMouth.delay > 15) {
        swap(pacman.skins, pacmanMouth.skins);
        pacmanMouth.delay = 0;
    }
    ++pacmanMouth.delay;
}

void launchTransitions(TransitionEngine &t, map<string, Character> &charactMap, bool &isTransitionFinished, vector<string> &names) {
    Vec2D posEnd;
    for (const string &name : names) {
        posEnd = calcPosTransition(charactMap[name]);
        TransitionContract a(charactMap[name].sprite[0],
                             charactMap[name].sprite[0].TRANSITION_POSITION, chrono::milliseconds(charactMap[name].vitesse),{(float)(posEnd.getX()), (float)(posEnd.getY())});
        if (name == "Pacman") {
            a.setDestinationCallback([&] {
                isTransitionFinished = true;
            });}
        t.startContract(a);
    }
}

// ---------- Other Functions ---------- //

bool isBubble (Character &character, vector<string> &maze){
    if (character.direction == "up" && (maze[character.pos.y+1][character.pos.x] == '.')) return true;
    else if(character.direction == "down" && (maze[character.pos.y-1][character.pos.x] == '.')) return true;
    else if(character.direction == "left" && (maze[character.pos.y][character.pos.x+1] == '.')) return true;
    else if(character.direction == "right" && (maze[character.pos.y][character.pos.x-1] == '.')) return true;
    else return false;
}

void eatBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
}


bool isBigBubble (Character &character, vector<string> &maze){
    if (character.direction == "up" && (maze[character.pos.y+1][character.pos.x] == 'o')) return true;
    else if(character.direction == "down" && (maze[character.pos.y-1][character.pos.x] == 'o')) return true;
    else if(character.direction == "left" && (maze[character.pos.y][character.pos.x+1] == 'o')) return true;
    else if(character.direction == "right" && (maze[character.pos.y][character.pos.x-1] == 'o')) return true;
    else return false;
}

void eatBigBubble (Character &character, vector<string> &maze, size_t &bubbleLeft){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
}

void isBubbleLeft (size_t &bubbleLeft , bool &gameRunning) {
    if (bubbleLeft == 0){
        gameOver(gameRunning);
    }
}

void gameOver(bool &gameRunning) {
    gameRunning = false;
}

void changeState(Character &charact) {
    charact.isDefaultState = !charact.isDefaultState;
    if (charact.isDefaultState) {
//        charact.sprite[0].setPixelData(charact.skins.defaultState.find(charact.direction)->second);
        if (charact.type == "Pacman") charact.vitesse = 500;
    } else {
//        charact.sprite[0].setPixelData(charact.skins.madState.find(charact.direction)->second);
        if (charact.type == "Pacman") charact.vitesse = 300;
    }
}

void changeEveryoneState(map<string, Character> &mapCharact, bool newValue) {
    for (auto& charact : mapCharact) {
        if (charact.second.isDefaultState != newValue) changeState(charact.second);
    }
}

void bigBubbleDuration(map<string, Character> &mapCharact) {
    this_thread::sleep_for(chrono::seconds(5));
    changeEveryoneState(mapCharact, true);
}

// ---------- Functions used to get values ---------- //

vector<Position> getPosTeleporter(Param &param) {
    if (param.skins["Maze"] == 1) {
        return {{11,0}, {11,11}};
    } else if (param.skins["Maze"] == 2) {
        return {{0,5},{22,5}}; // take the position of the two teleporter on the first map
    }
    return {{0,0}, {0,0}};
}

// ---------- Functions used for tests ---------- //

void showMap(map<string, Character> &myMap) {
    vector<string> keys;
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        keys.push_back(it->first);
    }
    for (size_t i (0); i < keys.size(); ++i) {
        cout << keys[i] << " -> ";
        cout << " pos.x : " << myMap[keys[i]].pos.x;
        cout << "  |  pos.y : " << myMap[keys[i]].pos.y;
        cout << "  |  direction : " << myMap[keys[i]].direction;
        cout << "  |  isDefaultState : " << myMap[keys[i]].isDefaultState << endl;
    }
}

void showMaze(const vector<string> & maze) {
    for (const string &line : maze) {
        for (char c : line) {
            cout << c << ' ';
        }
        cout << endl;
    }
}
