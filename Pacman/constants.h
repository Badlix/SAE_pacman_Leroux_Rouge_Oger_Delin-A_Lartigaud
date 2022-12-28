#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/mingl.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace nsShape;
using namespace nsGraphics;


struct Skin {
    vector<Rectangle> rectangles;
    vector<Triangle> triangles;
    vector<Line> lines;
    vector<Circle> circles;
};

// ---------- Global Values ---------- //

const Vec2D posBegin = {150,100};

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

// ---------- Wall Skins ---------- //

// ---------- Pacman Skins ---------- //

/* a modulo 50 is used for calculating the ending position of transitions
-> coord should be in [0, 49], or else a point at (50,50) will be draw at (0,0)*/

const Skin skinPacman1 = {
    /* rectangles */ {},
    /* triangles */ {Triangle(Vec2D(24,24), Vec2D(49,13), Vec2D(49,37), KRed)},
    /* lines */{},
    /* circles */{Circle(Vec2D(24,24), 25, KYellow), Circle(Vec2D(18,18), 5, KRed)}
};

const Skin skinPacman2 = {
    /* rectangles */ {},
    /* triangles */ {Triangle(Vec2D(25,25), Vec2D(49,13), Vec2D(49,37), KBlue)},
    /* lines */{},
    /* circles */{Circle(Vec2D(25,25), 25, KGreen), Circle(Vec2D(18,18), 5, KBlue)}
};

// ---------- Ghost Skins ---------- //

const Skin skinGhost1 = {
    /* rectangles */ {Rectangle(Vec2D(10,10), Vec2D(40,40), KGreen)},
    /* triangles */ {},
    /* lines */{},
    /* circles */{Circle(Vec2D(20,20), 25, KYellow), Circle(Vec2D(30,20), 5, KYellow)}
};

// ----------  Other Skins ---------- //


#endif // CONSTANTS_H
