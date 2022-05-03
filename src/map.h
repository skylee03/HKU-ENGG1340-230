#ifndef MAP_H
#define MAP_H

#include <stack>
#include <string>
#include <ctime>
#include <cstdlib>
#include "constants.h"

class Map {
 private:
   static constexpr int dx[] {-1, -1, -1, 0, 0, 1, 1, 1};
   static constexpr int dy[] {-1, 0, 1, -1, 1, -1, 0, 1};
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
  // current position
  Position current;
  // number of bombs
  int cnt_bombs;
  // game status
  int game_status;
  // score
  long long score;
  Map();
  ~Map();
  // insert a new block into the path
  void join_path(const Position &p);
  // check whether two blocks are neighbors
  bool is_neighbor(const Position &p, const Position &q) const;
  // clear the path
  void clear_path();
  // eliminate balloons
  void eliminate();
  // calculate $\lfloor\log_2(n)\rfloor$
  int lg2(const float &x) const {
    return ((unsigned &)x >> 23 & 255) - 127;
  }
};

#endif
