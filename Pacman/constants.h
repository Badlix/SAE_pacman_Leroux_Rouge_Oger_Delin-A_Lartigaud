#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <vector>
#include <iostream>

// file use to store all constants

using namespace std;

// Declaration of the differents maze
// # = wall
// . = bubble
//   = space
// o = big bubble
// = = tunnel
// - = cage of ghosts
// ~ = spawn of ghosts (par là où ils sortent de la cage)

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
// ghosts can only get out of the cage by going up, which means that the spawn of ghost is the position of the cage -1y


#endif // CONSTANTS_H
