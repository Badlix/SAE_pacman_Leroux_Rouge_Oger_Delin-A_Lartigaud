#include "mingl/mingl.h"
#include "mingl/shape/line.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/transition/transition_engine.h"
#include "mingl/audio/audioengine.h"
#include "mingl/gui/text.h"
#include "mingl/gui/glut_font.h"
#include "constants.h"
#include "param.h"
#include "general.h"
#include "assertives.h"
#include <iostream>

using namespace std;
using namespace nsGraphics;
using namespace nsShape;

void switchMusic(nsAudio::AudioEngine &defaultMusic, nsAudio::AudioEngine &madMusic, const bool &pacmanDefaultState) {
    if (!pacmanDefaultState) {
        if (!madMusic.isMusicPlaying()) {
            defaultMusic.setMusicPlaying(false);
            madMusic.setMusicPlaying(true);
        }
    } else {
        madMusic.setMusicPlaying(false);
        defaultMusic.setMusicPlaying(true);
    }
}

void drawGameOverScreen(MinGL &window, const bool &isVictory, const unsigned &score) {
    nsGui::Sprite gameOver("../Pacman/skins/other/gameover.si2", Vec2D(0, 0));
    gameOver.setPosition(Vec2D(window.getWindowSize().getX()/2-gameOver.getRowSize()/2, 200));
    window << gameOver;
    if (isVictory) {
        nsGui::Sprite youWin("../Pacman/skins/other/youWin.si2", Vec2D(0,0));
        youWin.setPosition(Vec2D(window.getWindowSize().getX()/2-youWin.getRowSize()/2, 380));
        window << youWin;
    } else {
        nsGui::Sprite youLose("../Pacman/skins/other/youLose.si2", Vec2D(0,0));
        youLose.setPosition(Vec2D(window.getWindowSize().getX()/2-youLose.getRowSize()/2, 380));
        window << youLose;
    }
    nsGui::Text textScore(Vec2D(0,0), "Score : " + to_string(score), KYellow, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
    textScore.setPosition(Vec2D(window.getWindowSize().getX()/2-textScore.computeWidth()/2, 520));
    window << textScore;
}

void drawCage(MinGL &window, const Vec2D pos) {
    window << Line(pos, pos + Vec2D(1*50, 0), KSilver, 5.0);
    window << Line(pos + Vec2D(2*50,0), pos + Vec2D{3*50, 0}, KSilver, 5.0);
    window << Line(pos, pos + Vec2D{0, 2*50}, KSilver, 5.0);
    window << Line(pos + Vec2D(3*50,0), pos + Vec2D{3*50, 2*50}, KSilver, 5.0);
    window << Line(pos + Vec2D(0, 2*50), pos + Vec2D(3*50, 2*50), KSilver, 5.0);
    window << Line(pos + Vec2D(1*50, 0), pos + Vec2D(2*50, 0), KSilver, 1.0);
}

size_t getNbrOfHorizontalWallInARow (vector<string> &maze, size_t &horizontalLayer){
    size_t numOfWallInARow = 0;
    for(size_t j=0;j<maze.size();++j){
        if (maze[horizontalLayer][j] == '#')
            numOfWallInARow += 1 ;
        else {
            return numOfWallInARow;
            numOfWallInARow = 0;
        }
        return numOfWallInARow;
    }
}

void drawMaze(MinGL &window, std::vector<string> &maze, std::vector<Rectangle> &walls, Param &param) {
    for (Rectangle &wall : walls) {
        window << wall;
    }
    for (size_t i(0); i < maze.size(); ++i) {
        for (size_t j(0); j < maze[0].size(); ++j) {
            switch (maze[i][j]) {
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

void drawCharacter(MinGL &window, std::vector<string> &characterList, std::map<string, Character> &charactMap, Param &param) {
    for (auto it(charactMap.begin()) ; it != charactMap.end() ; ++it) {
        if (it->first == "Pacman" && (it->second.pos == getPosTeleporter(param)[0] || it->second.pos == getPosTeleporter(param)[1])) continue;
        if (it->second.isDefaultState) {
            it->second.skins.defaultState.find(it->second.direction)->second.setPosition(it->second.sprite[0].getPosition());
            window << it->second.skins.defaultState.find(it->second.direction)->second;
        } else {
            it->second.skins.madState.find(it->second.direction)->second.setPosition(it->second.sprite[0].getPosition());
            window << it->second.skins.madState.find(it->second.direction)->second;
        }
    }
}

void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth) {
    if (pacmanMouth.delay > 10) {
        swap(pacman.skins, pacmanMouth.skins);
        pacmanMouth.delay = 0;
    }
    ++pacmanMouth.delay;
}

Vec2D calcPosTransition(Position &posCharact) {
    return {posBegin.getX() + posCharact.x*50, posBegin.getY() + posCharact.y*50};
}

void launchTransitions(nsTransition::TransitionEngine &t, map<string, Character> &charactMap, bool &isTransitionFinished, vector<string> &names) {
    Vec2D posEnd;
    for (const string &name : names) {
        posEnd = calcPosTransition(charactMap[name].pos);
        nsTransition::TransitionContract a(charactMap[name].sprite[0],
                             charactMap[name].sprite[0].TRANSITION_POSITION, chrono::milliseconds(charactMap[name].vitesse),{(float)(posEnd.getX()), (float)(posEnd.getY())});
        if (name == "Pacman") {
            a.setDestinationCallback([&] {
                isTransitionFinished = true;
            });}
        t.startContract(a);
    }
}
