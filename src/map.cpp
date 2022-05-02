#include "map.h"

Map::Map() {
  srand(time(nullptr));
  for(int i = 0; i < SIZE_H; i++) {
    for(int j = 0; j < SIZE_W; j++) {
      blocks[i][j].type = rand() % NUM_OF_TYPES;
      blocks[i][j].vis = false;
    }
  }
}

Map::~Map() {}
