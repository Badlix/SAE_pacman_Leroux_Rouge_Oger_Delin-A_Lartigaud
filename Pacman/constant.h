#ifndef CONST_H
#define CONST_H
#include <vector>
#include <iostream>

// file use to store all constants and struct

using namespace std;

struct Character {
    unsigned posX;
    unsigned posY;
    bool isDefaultState;
};

// Declaration of the differents maze
// # = wall
// . = bubble
//   = space
// o = big bubble
// = = tunnel
// - = number of ghosts in the cage
// ~ = spawn of ghosts

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
const pair<unsigned, unsigned> posCage1 = {15,8}; // <x, y>
// ghosts can only get out of the cage by going up, which means that the spawn of ghost is the position of the cage -1y

#endif // CONST_H
