#ifndef MAP_H
#define MAP_H

#include <stack>
#include <string>
#include <ctime>
#include <cstdlib>
#include "constants.h"

class Map {
 private:
 public:
  // the data structure to store the properties of a block
  struct Block {
    // the type of the block,
    // 0: bomb, non-0: color of the balloon
    int type;
    // whether the block is in the selected path
    bool vis;
  };
  // properties of the blocks
  Block blocks[SIZE_H][SIZE_W];
  // the position of a block can be represented by a pair of ints (x, y)
  using Position = std::pair<int, int>;
  // positions of the blocks in the selected path
  std::stack<Position> path;
  Map();
  ~Map();
};

#endif
