#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/gui/sprite.h"
#include <vector>
#include <iostream>

struct Position {
    unsigned x;
    unsigned y;
    bool operator == (const Position& p) const {
        return x == p.x && y == p.y;
    }
    bool operator != (const Position& p) const {
        return x != p.x || y != p.y;
    }
    bool operator < (const Position& p) const {
        return x < p.x || y < p.y;
    }
};

struct Skin {
    std::map<std::string, nsGui::Sprite> defaultState;
    std::map<std::string, nsGui::Sprite> madState;
};

struct PacmanMouth {
    Skin skins;
    unsigned delay;
};

struct Character {
    std::string type; //Pacman, Ghost, Fruit
    Position pos;
    std::string direction;
    bool isDefaultState;
    unsigned vitesse; // default : 500, mad mod : 300 -> 0 is the fastest
    std::vector<nsGui::Sprite> sprite; // can't init an empty sprite
    Skin skins;
};

// ---------- Global Values ---------- //

const static nsGraphics::Vec2D posBegin = {200,150};

// ---------- Maze Patterns ---------- //

// # : wall
// . : bubble
// o : big bubble
// = : tunnel
// - : ghost cage

const std::vector<std::string> maze1 = {
    "###########=###########",
    "#.........#...##.....o#",
    "#.##.##.#...#.o#.#.---#",
    "#.#...#.#.#.##.#.#.---#",
    "#.#.#.#o.....#...#....#",
    "#..o#.###.##.#.#.#.##.#",
    "#.###......#.#.#.#..#.#",
    "#...#.####.#...#.##...#",
    "#.#.#......#.###...o#.#",
    "#.#.#o#.####.#...####.#",
    "#..............#.....o#",
    "###########=###########"
};

const std::vector<std::string> maze2 = {
    "#######################",
    "#..........o..........#",
    "#.###.#####.#####.#.#.#",
    "#.#o......#.#.....#...#",
    "#.#.##.##.....###.#.#.#",
    "=.#.#.....###.....#...=",
    "#.#.#.###.#o..---.#.#.#",
    "#.#.#.# #.###.---.#o#.#",
    "#.#...###...#.###.#.#.#",
    "#.###.#o#.###.#o#.#.#.#",
    "#o....................#",
    "#######################"
};

// ---------- Pacman Skins ---------- //

const Skin flowerPacman = {
    {{"up", nsGui::Sprite("../Pacman/skins/flowerOpen.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/flowerOpen.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/flowerOpen.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/flowerOpen.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/madFlowerOpen.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/madFlowerOpen.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/madFlowerOpen.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/madFlowerOpen.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin flowerPacmanClose = {
    {{"up", nsGui::Sprite("../Pacman/skins/flowerClose.si2", nsGraphics::Vec2D(0,0))},
    {"down", nsGui::Sprite("../Pacman/skins/flowerClose.si2", nsGraphics::Vec2D(0,0))},
    {"left", nsGui::Sprite("../Pacman/skins/flowerClose.si2", nsGraphics::Vec2D(0,0))},
    {"right", nsGui::Sprite("../Pacman/skins/flowerClose.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/flowerClose.si2", nsGraphics::Vec2D(0,0))},
    {"down", nsGui::Sprite("../Pacman/skins/flowerClose.si2", nsGraphics::Vec2D(0,0))},
    {"left", nsGui::Sprite("../Pacman/skins/flowerClose.si2", nsGraphics::Vec2D(0,0))},
    {"right", nsGui::Sprite("../Pacman/skins/flowerClose.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin penguinPacman = {
    {{"up", nsGui::Sprite("../Pacman/skins/penguinOpen.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/penguinOpen.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/penguinOpen.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/penguinOpen.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/penguinOpen.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/penguinOpen.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/penguinOpen.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/penguinOpen.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin penguinPacmanClose = {
    {{"up", nsGui::Sprite("../Pacman/skins/penguinClose.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/penguinClose.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/penguinClose.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/penguinClose.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/penguinClose.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/penguinClose.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/penguinClose.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/penguinClose.si2", nsGraphics::Vec2D(0,0))}}
};


//const Skin candyPacman = {
//    {{"open", nsGui::Sprite("../Pacman/skins/candyOpen.si2", nsGraphics::Vec2D(0,0))},
//     {"close", nsGui::Sprite("../Pacman/skins/candyClose.si2", nsGraphics::Vec2D(0,0))}},
//    {{"open", nsGui::Sprite("../Pacman/skins/madCandyOpen.si2", nsGraphics::Vec2D(0,0))},
//     {"close", nsGui::Sprite("../Pacman/skins/madCandyClose.si2", nsGraphics::Vec2D(0,0))}}
//};

// ---------- Ghost Skins ---------- //

const Skin butterflyGhost = {
    {{"up", nsGui::Sprite("../Pacman/skins/butterflyUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/butterflyDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/butterflyRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/butterflyLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/fearedButterflyUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/fearedButterflyDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/fearedButterflyRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/fearedButterflyLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin iceCreamGhost = {
    {{"up", nsGui::Sprite("../Pacman/skins/iceCreamUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/iceCreamDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/iceCreamRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/iceCreamLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/fearedIceCreamUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/fearedIceCreamDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/fearedIceCreamRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/fearedIceCreamLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin lolipopGhost = {
    {{"up", nsGui::Sprite("../Pacman/skins/lolipopUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/lolipopDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/lolipopRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/lolipopLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/fearedLolipopUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/fearedLolipopDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/fearedLolipopRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/fearedLolipopLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const std::vector<nsGraphics::RGBAcolor> skinGhostColors = {nsGraphics::RGBAcolor(255,192,203,255), nsGraphics::RGBAcolor(255,238,0,255), nsGraphics::RGBAcolor(105,0,105,255), nsGraphics::RGBAcolor(200,0,0,255)};

// ---------- Numbers ---------- //
/* Numbers are vector of yellow rectangles */

const std::vector<nsShape::Rectangle> nbZero = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbOne = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(17,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(12,10), nsGraphics::Vec2D(17,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbTwo = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,20), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,20), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbThree = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbFour = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(10,17), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,5), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbFive = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,20), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,20), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbSix = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,20), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbSeven = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbEight = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const std::vector<nsShape::Rectangle> nbNine = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,17), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

#endif // CONSTANTS_H
