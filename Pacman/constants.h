#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/gui/sprite.h"
#include <vector>
#include <iostream>

/**
* @struct Position
* @brief Struct representing a position in the maze
*
* @var x : the x coordinate of the position
* @var y : the y coordinate of the position
* @fn operator == : Overloaded operator to compare two Position objects
* @fn operator != : Overloaded operator to compare two Position objects
* @fn operator < : Overloaded operator to compare two Position objects
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
* @struct Skin
* @brief Holds the sprites for the default and mad state of a character.
* @var defaultState A map of default state sprites where the key is the character's name and the value is the corresponding nsGui::Sprite.
* @var madState A map of mad state sprites where the key is the character's name and the value is the corresponding nsGui::Sprite.
*/
struct Skin {
    std::map<std::string, nsGui::Sprite> defaultState;
    std::map<std::string, nsGui::Sprite> madState;
};

/**
* @struct PacmanMouth
* @brief struct that contains all the information related to pacman's mouth animation
* @var skins : map of all the skins of the pacman's mouth
* @var delay : delay between each animation frame
*/
struct PacmanMouth {
    Skin skins;
    unsigned delay;
};

/**
 * @struct Character
 * @brief A struct that represents a character in the game.
 * @var type 
 * The type of character. Can be "Pacman", "Ghost", or "Fruit".
 * @var pos
 * The position of the character on the game board.
 * @var direction
 * The direction that the character is moving in.
 * @var isDefaultState 
 * A flag indicating whether the character is in its default state or not.
 * @var vitesse 
 * The speed of the character. Default is 500, but when "mad" it is 300. 0 is the fastest.
 * @var sprite 
 * A vector of sprites that are used to represent the character. Can't be empty.
 * @var skins
 * A Skin object that holds different skins of the character.
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


/**
 * @var posBegin
 * @brief A constant static variable that holds the initial position of an object.
 * @var nsGraphics::Vec2D
 * The position is represented by a Vec2D object from the nsGraphics namespace.
 * The initial position is (200,150)
 */
const static nsGraphics::Vec2D posBegin = {200,150}; // Begin of the area where the game element are draw 


// ---------- Maze Patterns ---------- //

/**
 * @var maze1
 * @brief A constant variable that holds the layout of the first maze in the game.
 * @var std::vector<std::string>
 * The maze is represented by a vector of strings.
 * Each character in the string represents a different element in the maze:
 * "#" : wall
 * "." : bubble
 * "o" : big bubble
 * "=" : tunnel
 * "-" : ghost cage
 *
 * @var maze2
 * @brief A constant variable that holds the layout of the second maze in the game.
 * @var std::vector<std::string>
 * The maze is represented by a vector of strings.
 * Each character in the string represents a different element in the maze:
 * "#" : wall
 * "." : bubble
 * "o" : big bubble
 * "=" : tunnel
 * "-" : ghost cage
 */
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

// ---------- Ghost Color Skins ---------- //

/**
 * @var skinGhostColors
 * @brief A constant variable that holds the colors for the ghost skins in the game.
 * @var std::vector<nsGraphics::RGBAcolor>
 * The colors are represented by RGBAcolor objects from the nsGraphics namespace.
 * The colors in the vector are:
 * pink (255,192,203,255)
 * yellow (255,238,0,255)
 * purple (105,0,105,255)
 * red (200,0,0,255)
 */
const std::vector<nsGraphics::RGBAcolor> skinGhostColors = {nsGraphics::RGBAcolor(255,192,203,255), nsGraphics::RGBAcolor(255,238,0,255), nsGraphics::RGBAcolor(105,0,105,255), nsGraphics::RGBAcolor(200,0,0,255)};


// ---------- Fruits Skins ---------- //

/**
 * @var fruitSkins
 * @brief A constant variable that holds the skins for the fruits in the game.
 * @var std::vector<nsGui::Sprite>
 * The skins are represented by Sprite objects from the nsGui namespace.
 * The sprites in the vector are:
 * Pacman-cherry
 * Pacman-pear
 * Pacman-cake
 */
const std::vector<nsGui::Sprite> fruitSkins = {
    nsGui::Sprite("../Pacman/skins/other/cherry.si2", nsGraphics::Vec2D(0,0)),
    nsGui::Sprite("../Pacman/skins/other/pear.si2", nsGraphics::Vec2D(0,0)),
    nsGui::Sprite("../Pacman/skins/other/cake.si2", nsGraphics::Vec2D(0,0))
};

// ---------- Numbers ---------- //
/* Numbers are vector of yellow rectangles */

/**
 * @var nbZero
 * @brief A constant variable that holds the shapes of number Zero.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbZero = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbOne
 * @brief A constant variable that holds the shapes of number One.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbOne = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(17,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(12,10), nsGraphics::Vec2D(17,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbTwo
 * @brief A constant variable that holds the shapes of number Two.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbTwo = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,20), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,20), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbThree
 * @brief A constant variable that holds the shapes of number Three.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbThree = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbFour
 * @brief A constant variable that holds the shapes of number Four.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbFour = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(10,17), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,5), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbFive
 * @brief A constant variable that holds the shapes of number Five.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbFive = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,20), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,20), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbSix
 * @brief A constant variable that holds the shapes of number Six.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbSix = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,20), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbSeven
 * @brief A constant variable that holds the shapes of number Seven.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbSeven = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbEight
 * @brief A constant variable that holds the shapes of number Eight.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbEight = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

/**
 * @var nbNine
 * @brief A constant variable that holds the shapes of number nine.
 * @var std::vector<nsShape::Rectangle>
 */
const std::vector<nsShape::Rectangle> nbNine = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,17), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};


// ---------- GameOverSentence ---------- //

/**
 * @var loseSentence
 * @brief A constant variable that holds the sentences displayed when the player loses the game.
 * @var std::vector<std::string>
 * The sentences are in the form of strings
 
 * @var winSentence
 * @brief A constant variable that holds the sentences displayed when the player wins the game.
 * @var std::vector<std::string>
 * The sentences are in the form of strings
 */
const std::vector<std::string> loseSentence = {"Error: A fatal exception has occurred. Player's skills has left the game.", "Do you really know how to play this game ?", "Take a little rest before resuming, it shall benefit a bit to your health."};
const std::vector<std::string> winSentence = {"You, who braved so many trials, you have all my admiration for having succeeded.", "Congratulations ! Now that you're done, how about taking a quick shower ?", "You are filled with determination"};

#endif // CONSTANTS_H
