#include "constants.h"
#include <iostream>
#include <vector>

using namespace std;

struct constants::Character {
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

const vector<string> constants::maze1 = {
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
