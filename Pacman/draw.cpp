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
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace nsGraphics;
using namespace nsShape;

/**
 * @brief switchMusic is a function that switches the music between the default and mad music.
 * @param defaultMusic: the default music.
 * @param madMusic: the mad music.
 * @param pacmanDefaultState: a boolean value that indicates if the pacman is in its default state or not.
 */
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

/**
 * @brief Draws the game over screen
 * @param window The MinGL window
 * @param isVictory A boolean indicating if the game ended in a victory or a loss
 * @param score The score of the player
 * @param random An unsigned integer used to select a random sentence to display
 */
void drawGameOverScreen(MinGL &window, const bool &isVictory, const unsigned &score, unsigned &random) {
    cout << random << endl;
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
}

/**
 * @brief Draws the cage on the game screen
 * 
 * @param window The window where the cage will be drawn
 * @param pos The position of the top-left corner of the cage on the screen
 */
void drawCage(MinGL &window, const Vec2D pos) {
    window << Line(pos, pos + Vec2D(1*50, 0), KSilver, 5.0);
    window << Line(pos + Vec2D(2*50,0), pos + Vec2D{3*50, 0}, KSilver, 5.0);
    window << Line(pos, pos + Vec2D{0, 2*50}, KSilver, 5.0);
    window << Line(pos + Vec2D(3*50,0), pos + Vec2D{3*50, 2*50}, KSilver, 5.0);
    window << Line(pos + Vec2D(0, 2*50), pos + Vec2D(3*50, 2*50), KSilver, 5.0);
    window << Line(pos + Vec2D(1*50, 0), pos + Vec2D(2*50, 0), KSilver, 1.0);
}


/**
 * @brief Get the number of consecutive horizontal walls in a row
 *
 * This function takes a vector of strings representing a maze and an integer representing the current horizontal layer being checked.
 * The function returns the number of consecutive horizontal walls in the current layer.
 *
 * @param maze A vector of strings representing the maze
 * @param horizontalLayer The current horizontal layer being checked
 * @return The number of consecutive horizontal walls in the current layer
 */
size_t getNbrOfHorizontalWallInARow (vector<string> &maze, size_t &horizontalLayer) {
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



/**
* @brief This function draws the maze in the window
* @param window The MinGL window where the maze will be drawn
* @param maze The vector of strings representing the maze
* @param walls The vector of Rectangle representing the walls of the maze
* @param param The parameter object that contains the position of the cage
* 
* This function draws the maze in the window using the information from the maze vector and the walls vector.
* It also calls the drawCage function if the cage is found in the maze vector.
*/
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

/**
* @brief This function is used to draw the characters on the screen
* @param window The window where the characters will be drawn
* @param characterList The list of characters that will be drawn
* @param charactMap A map containing the character's information
* @param param An object containing the game's parameters
* This function is used to draw the characters on the screen. It loops through the character map and checks if the character is in its default state or mad state. If it's in the default state, it draws the default sprite of the character based on its current direction. If it's in the mad state, it draws the mad sprite of the character based on its current direction.
*/
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

/**
* @brief Function that switch the mouth of the Pacman character between open and closed
* @param pacman The Pacman character object
* @param pacmanMouth The object containing the open and closed state of the Pacman's mouth
*/
void switchMouthPacmanOpenClose(Character &pacman, PacmanMouth &pacmanMouth) {
    if (pacmanMouth.delay > 10) {
        swap(pacman.skins, pacmanMouth.skins);
        pacmanMouth.delay = 0;
    }
    ++pacmanMouth.delay;
}

/**
* @brief Calculates the transition position for a character.
* This function takes in a reference to a character position and calculates the transition position using the x and y coordinates of the starting position and the character position.
* @param posCharact Reference to the character's position.
* @return Vec2D The calculated transition position.
*/
Vec2D calcPosTransition(Position &posCharact) {
    return {posBegin.getX() + posCharact.x*50, posBegin.getY() + posCharact.y*50};
}

/**
* @brief Launches transitions for specified characters.
* This function uses the TransitionEngine object to calculate the end position of each character based on their current position and speed, and starts a transition contract for each character. If the character is "Pacman", it sets a callback function to set the isTransitionFinished flag to true upon completion of the transition.
* @param t Reference to a TransitionEngine object.
* @param charactMap Reference to a map containing the characters and their information.
* @param isTransitionFinished Reference to a boolean flag indicating whether the transition is finished.
* @param names Vector of strings containing the names of the characters to launch transitions for.
*/
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

/**
* @brief Draws the current score in the window.
* This function uses the MinGL object to display the current score using sprites for each digit. The starting position is determined based on the window size and the length of the score.
* @param window Reference to the MinGL object to display the score.
* @param score Reference to the integer containing the current score.
*/
void drawScore(MinGL &window, unsigned &score){
    string scoreStr = to_string(score);
    Vec2D pos = {window.getWindowSize().getX()-50*scoreStr.size(), 20};
    for (unsigned i(0) ; i < scoreStr.size(); ++i){
        window << nsGui::Sprite("../Pacman/skins/other/" + string(1, scoreStr[i]) + ".si2", pos);
        pos += nsGraphics::Vec2D{50, 0};
    }
}
