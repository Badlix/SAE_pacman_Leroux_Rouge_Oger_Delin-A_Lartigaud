#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/shape/shape.h"
#include "mingl/mingl.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

struct Layer {
    vector<Rectangle> rectangles;
    vector<Triangle> triangles;
    vector<Line> lines;
    vector<Circle> circles;
};

/* a skin has two layer -> avoid that a shape hide an another shape*/
struct Skin {
    Layer backLayer;
    Layer frontLayer;
};

// ---------- Global Values ---------- //

const static Vec2D posBegin = {200,150};

// ---------- Maze Patterns ---------- //

// # : wall
// . : bubble
// o : big bubble
// = : tunnel
// - : ghost cage
// ~ : ghost spawn (considered as a wall except when a ghost get out of the cage)

const vector<string> maze1 = {
    "#######################",
    "#..........o..........#",
    "#.###.#####.#####.#.#.#",
    "#.#o......#.#.....#...#",
    "#.#.##.##.....###.#.#.#",
    "=.#.#.....###.....#...=",
    "#.#.#.###.#o..#~#.#.#.#",
    "#.#.#.# #.###.#-#.#o#.#",
    "#.#...###...#.###.#.#.#",
    "#.###.#o#.###.#o#.#.#.#",
    "#o....................#",
    "#######################"
};

// ---------- Pacman Skins ---------- //

/* a modulo 50 is used for calculating the ending position of transitions
-> coord should be in [0, 49], or else a point at (50,50) will be draw at (0,0)*/

const Skin skinPacman1 = {
    // Back Layer
    {{},{},{},{Circle(Vec2D(24,24), 25, KYellow)}},
    // Front Layer
    {{},{Triangle(Vec2D(24,24), Vec2D(49,13), Vec2D(49,37), KBlack)},{},
     {Circle(Vec2D(18,18), 5, KRed)}
    }
};

const Skin skinPacman2 = {
    // Back Layer
    {{},{},{},{Circle(Vec2D(25,25), 25, KGreen)}},
    // Front Layer
    {{},{Triangle(Vec2D(25,25), Vec2D(49,13), Vec2D(49,37), KBlue)},{},
    {Circle(Vec2D(18,18), 5, KBlue)}}
};

// ---------- Ghost Skins ---------- //

const Skin skinGhost1 = {
    // Back Layer
    {{Rectangle(Vec2D(10,10), Vec2D(40,40), KGreen)},{},{},{}},
    // Front Layer
    {{},{},{},{Circle(Vec2D(20,20), 5, KYellow), Circle(Vec2D(30,20), 5, KYellow)}}
};

const vector<RGBAcolor> skinGhostColor1 = {KGreen, KPurple, KBlack, KNavy};

// ---------- Numbers ---------- //
/* Numbers are vector of yellow rectangles */

const vector<Rectangle> nbZero = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbOne = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(17,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(12,10), nsGraphics::Vec2D(17,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbTwo = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,20), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,20), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbThree = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbFour = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(10,17), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,5), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbFive = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,20), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,20), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbSix = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,20), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbSeven = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbEight = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

const vector<Rectangle> nbNine = {
    nsShape::Rectangle(nsGraphics::Vec2D(5,5), nsGraphics::Vec2D(25,10), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,10), nsGraphics::Vec2D(10,17), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,17), nsGraphics::Vec2D(25,22), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(20,10), nsGraphics::Vec2D(25,30), nsGraphics::KYellow),
    nsShape::Rectangle(nsGraphics::Vec2D(5,35), nsGraphics::Vec2D(25,30), nsGraphics::KYellow)
};

#endif // CONSTANTS_H
