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
/**
 * @file   draw.cpp
 * @author  Mathieu Leroux, Elliot Lartigaud, Gabriel Rouge, Alexis Delain, Léo Oger
 * @date    Janvier 2023
 * @brief   functions used to draw and played sounds/musics
 **/

#include "general.h"
#include "assertives.h"
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
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

void drawGameOverScreen(MinGL &window, const bool &isVictory, const unsigned &score, unsigned &random) {
    nsGui::Sprite gameOver("../Pacman/skins/other/gameover.si2", Vec2D(0, 0));
    gameOver.setPosition(Vec2D(window.getWindowSize().getX()/2-gameOver.getRowSize()/2, 200));
    window << gameOver;

    if (isVictory) {

        nsGui::Sprite youWin("../Pacman/skins/other/youWin.si2", Vec2D(0,0));
        youWin.setPosition(Vec2D(window.getWindowSize().getX()/2-youWin.getRowSize()/2, 380));
        window << youWin;
        nsGui::Text textWin(Vec2D(0,0), winSentence[random], KYellow, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
        textWin.setPosition(Vec2D(window.getWindowSize().getX()/2-textWin.computeWidth()/2, 700));
        window << textWin;

    } else {

        nsGui::Sprite youLose("../Pacman/skins/other/youLose.si2", Vec2D(0,0));
        youLose.setPosition(Vec2D(window.getWindowSize().getX()/2-youLose.getRowSize()/2, 380));
        window << youLose;
        nsGui::Text textLose(Vec2D(0,0), loseSentence[random], KYellow, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
        textLose.setPosition(Vec2D(window.getWindowSize().getX()/2-textLose.computeWidth()/2,700));
        window << textLose;
    }

    nsGui::Text textScore(Vec2D(0,0), "Score : " + to_string(score), KYellow, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
    textScore.setPosition(Vec2D(window.getWindowSize().getX()/2-textScore.computeWidth()/2, 520));
    window << textScore;
    window << nsGui::Text(Vec2D(100, 50), "REPLAY [R]", KYellow, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
    window << nsGui::Text(Vec2D(window.getWindowSize().getX()-200, 50), "QUIT [A]", KYellow, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
}

void drawCage(MinGL &window, const Vec2D pos) {
    window << Line(pos, pos + Vec2D(1*50, 0), KSilver, 5.0);
    window << Line(pos + Vec2D(2*50,0), pos + Vec2D{3*50, 0}, KSilver, 5.0);
    window << Line(pos, pos + Vec2D{0, 2*50}, KSilver, 5.0);
    window << Line(pos + Vec2D(3*50,0), pos + Vec2D{3*50, 2*50}, KSilver, 5.0);
    window << Line(pos + Vec2D(0, 2*50), pos + Vec2D(3*50, 2*50), KSilver, 5.0);
    window << Line(pos + Vec2D(1*50, 0), pos + Vec2D(2*50, 0), KSilver, 1.0);
}

void drawMaze(MinGL &window, std::vector<string> &maze, std::vector<Rectangle> &walls, Param &param) {
    window << Rectangle(posBegin, posBegin+Vec2D{maze[0].size()*50, maze.size()*50}, nsGraphics::RGBAcolor(30,30,50,255));
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

void drawCharacter(MinGL &window, std::map<string, Character> &charactMap, Param &param) {
    for (auto it(charactMap.begin()) ; it != charactMap.end() ; ++it) {
        if (it->first == "Pacman" && (it->second.pos == getPosTeleporter(param)[0] || it->second.pos == getPosTeleporter(param)[1])) continue;
        //it->second.sprite[0].setPosition(posBegin + Vec2D(it->second.pos.x*50, it->second.pos.y*50));
        if (it->second.isDefaultState) {
            it->second.skins.defaultState.find(it->second.direction)->second.setPosition(it->second.sprite[0].getPosition());
            //it->second.skins.defaultState.find(it->second.direction)->second.setPosition(posBegin + Vec2D(it->second.pos.x*50, it->second.pos.y*50));
            window << it->second.skins.defaultState.find(it->second.direction)->second;
        } else {
            it->second.skins.madState.find(it->second.direction)->second.setPosition(it->second.sprite[0].getPosition());
            //it->second.skins.madState.find(it->second.direction)->second.setPosition(posBegin + Vec2D(it->second.pos.x*50, it->second.pos.y*50));
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

void launchTransitions(nsTransition::TransitionEngine &t, map<string, Character> &charactMap, bool &isTransitionFinished) {
    Vec2D posEnd;
    for (auto it(charactMap.begin()) ; it != charactMap.end() ; ++it) {
        posEnd = calcPosTransition(it->second.pos);
        nsTransition::TransitionContract a(it->second.sprite[0],
                             it->second.sprite[0].TRANSITION_POSITION, chrono::milliseconds(it->second.vitesse),{(float)(posEnd.getX()), (float)(posEnd.getY())});
        if (it->first == "Pacman") {
            a.setDestinationCallback([&] {
                isTransitionFinished = true;
            });}
        t.startContract(a);
    }
}

void drawScore(MinGL &window, unsigned &score){
    string scoreStr = to_string(score);
    Vec2D pos = {window.getWindowSize().getX()-50*scoreStr.size(), 20};
    for (unsigned i(0) ; i < scoreStr.size(); ++i){
        window << nsGui::Sprite("../Pacman/skins/other/" + string(1, scoreStr[i]) + ".si2", pos);
        pos += nsGraphics::Vec2D{50, 0};
    }
}
