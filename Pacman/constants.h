#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/gui/sprite.h"
#include <vector>
#include <iostream>

/**
 * @brief The Position struct
 */
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

/**
 * @brief The Skin struct
 */
struct Skin {
    std::map<std::string, nsGui::Sprite> defaultState;
    std::map<std::string, nsGui::Sprite> madState;
};

/**
 * @brief The PacmanMouth struct
 */
struct PacmanMouth {
    Skin skins;
    unsigned delay;
};

/**
 * @brief The Character struct
 */
struct Character {
    std::string type; //Pacman, Ghost, Fruit
    Position pos;
    std::string direction;
    bool isDefaultState;
    unsigned vitesse; // default : 500, mad : 300 -> 0 is the fastest
    std::vector<nsGui::Sprite> sprite; // can't init an empty sprite
    Skin skins;
};

// ---------- Global Values ---------- //

/* Begin of the area where the game element are draw */
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

/* default Pacman Skin */

const Skin defaultPacman = {
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanOpenUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanOpenRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanOpenDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanOpenLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanOpenUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanOpenRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanOpenDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanOpenLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin defaultPacmanClose = {
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanCloseUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanCloseRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanCloseDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanCloseLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanCloseUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanCloseRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanCloseDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanDefault/pacmanCloseLeft.si2", nsGraphics::Vec2D(0,0))}}
};

/* Penguin Pacman Skin */

const Skin penguinPacman = {
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanPenguin/penguinOpenUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanPenguin/penguinOpenRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanPenguin/penguinOpenDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanPenguin/penguinOpenLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanPenguin/madPenguinOpenUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanPenguin/madPenguinOpenRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanPenguin/madPenguinOpenDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanPenguin/madPenguinOpenLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin penguinPacmanClose = {
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanPenguin/penguinCloseUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanPenguin/penguinCloseRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanPenguin/penguinCloseDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanPenguin/penguinCloseLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanPenguin/madPenguinCloseUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanPenguin/madPenguinCloseRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanPenguin/madPenguinCloseDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanPenguin/madPenguinCloseLeft.si2", nsGraphics::Vec2D(0,0))}}
};

/* Candy Pacman Skin */

const Skin candyPacman = {
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanCandy/candyOpenUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanCandy/candyOpenRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanCandy/candyOpenDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanCandy/candyOpenLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanCandy/madCandyOpenUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanCandy/madCandyOpenRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanCandy/madCandyOpenDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanCandy/madCandyOpenLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin candyPacmanClose = {
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanCandy/candyCloseUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanCandy/candyCloseRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanCandy/candyCloseDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanCandy/candyCloseLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanCandy/madCandyCloseUp.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanCandy/madCandyCloseRight.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanCandy/madCandyCloseDown.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanCandy/madCandyCloseLeft.si2", nsGraphics::Vec2D(0,0))}}
};

/* Flower Pacman Skin */

const Skin flowerPacman = {
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanFlower/flowerOpenUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanFlower/flowerOpenDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanFlower/flowerOpenRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanFlower/flowerOpenLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanFlower/madFlowerOpenUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/pacmanFlower/madFlowerOpenDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/pacmanFlower/madFlowerOpenRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/pacmanFlower/madFlowerOpenLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin flowerPacmanClose = {
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanFlower/flowerCloseUp.si2", nsGraphics::Vec2D(0,0))},
    {"down", nsGui::Sprite("../Pacman/skins/pacmanFlower/flowerCloseDown.si2", nsGraphics::Vec2D(0,0))},
    {"left", nsGui::Sprite("../Pacman/skins/pacmanFlower/flowerCloseLeft.si2", nsGraphics::Vec2D(0,0))},
    {"right", nsGui::Sprite("../Pacman/skins/pacmanFlower/flowerCloseRight.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/pacmanFlower/madFlowerCloseUp.si2", nsGraphics::Vec2D(0,0))},
    {"down", nsGui::Sprite("../Pacman/skins/pacmanFlower/madFlowerCloseDown.si2", nsGraphics::Vec2D(0,0))},
    {"left", nsGui::Sprite("../Pacman/skins/pacmanFlower/madFlowerCloseLeft.si2", nsGraphics::Vec2D(0,0))},
    {"right", nsGui::Sprite("../Pacman/skins/pacmanFlower/madFlowerCloseRight.si2", nsGraphics::Vec2D(0,0))}}
};

// ---------- Ghost Skins ---------- //

const Skin defaultGhost = {
    {{"up", nsGui::Sprite("../Pacman/skins/ghostDefault/ghostUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/ghostDefault/ghostDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/ghostDefault/ghostRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/ghostDefault/ghostLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/ghostDefault/fearedGhostUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/ghostDefault/fearedGhostDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/ghostDefault/fearedGhostRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/ghostDefault/fearedGhostLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin iceCreamGhost = {
    {{"up", nsGui::Sprite("../Pacman/skins/ghostIceCream/iceCreamUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/ghostIceCream/iceCreamDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/ghostIceCream/iceCreamRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/ghostIceCream/iceCreamLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/ghostIceCream/fearedIceCreamUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/ghostIceCream/fearedIceCreamDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/ghostIceCream/fearedIceCreamRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/ghostIceCream/fearedIceCreamLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin lolipopGhost = {
    {{"up", nsGui::Sprite("../Pacman/skins/ghostLolipop/lolipopUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/ghostLolipop/lolipopDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/ghostLolipop/lolipopRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/ghostLolipop/lolipopLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/ghostLolipop/fearedLolipopUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/ghostLolipop/fearedLolipopDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/ghostLolipop/fearedLolipopRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/ghostLolipop/fearedLolipopLeft.si2", nsGraphics::Vec2D(0,0))}}
};

const Skin butterflyGhost = {
    {{"up", nsGui::Sprite("../Pacman/skins/ghostButterfly/butterflyUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/ghostButterfly/butterflyDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/ghostButterfly/butterflyRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/ghostButterfly/butterflyLeft.si2", nsGraphics::Vec2D(0,0))}},
    {{"up", nsGui::Sprite("../Pacman/skins/ghostButterfly/fearedButterflyUp.si2", nsGraphics::Vec2D(0,0))},
     {"down", nsGui::Sprite("../Pacman/skins/ghostButterfly/fearedButterflyDown.si2", nsGraphics::Vec2D(0,0))},
     {"right", nsGui::Sprite("../Pacman/skins/ghostButterfly/fearedButterflyRight.si2", nsGraphics::Vec2D(0,0))},
     {"left", nsGui::Sprite("../Pacman/skins/ghostButterfly/fearedButterflyLeft.si2", nsGraphics::Vec2D(0,0))}}
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
