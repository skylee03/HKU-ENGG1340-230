#include "map.h"

Map::Map() {
  score = 0;
  game_status = GAME_GOING;
  cnt_bombs = 0;
  srand(time(nullptr));
  for(int i = 0; i < SIZE_H; i++) {
    for(int j = 0; j < SIZE_W; j++) {
      blocks[i][j].type = rand() % NUM_OF_TYPES;
      blocks[i][j].vis = false;
      if(blocks[i][j].type == BOMB) cnt_bombs++;
    }
  }
}

Map::~Map() {}

void Map::join_path(const Position &p) {
  path.push(p);
  blocks[p.first][p.second].vis = true;
}

bool Map::is_neighbor(const Position &p, const Position &q) const {
  for(int i = 0; i < 8; i++) {
    if(Position(p.first + dx[i], p.second + dy[i]) == q) return true;
  }
  return false;
}

void Map::clear_path() {
  while(!path.empty()) {
    const auto &[x, y] = path.top();
    blocks[x][y].vis = false;
    path.pop();
  }
}

void Map::eliminate() {
  const int tot = path.size();
  if(tot < 3) return;
  bool bombs_eliminated = false;
  while(!path.empty()) {
    const auto &[x, y] = path.top();
    for(int i = 0; i < 8; i++) {
      const int nx = x + dx[i], ny = y + dy[i];
      if(0 <= nx && nx < SIZE_H && 0 <= ny && ny < SIZE_W) {
        if(blocks[nx][ny].type == BOMB) {
          bombs_eliminated = true;
          cnt_bombs--;
          blocks[nx][ny].type = rand() % (NUM_OF_TYPES - 1) + 1;
        }
      }
    }
    blocks[x][y].type = rand() % (NUM_OF_TYPES - 1) + 1;
    blocks[x][y].vis = false;
    path.pop();
  }
  if(cnt_bombs == 0) {
    game_status = GAME_WIN;
  }
  if(!bombs_eliminated) {
    if(cnt_bombs < SIZE_H * SIZE_W) {
      int x, y;
      do {
        x = rand() % SIZE_H;
        y = rand() % SIZE_W;
      } while(blocks[x][y].type == BOMB);
      blocks[x][y].type = BOMB;
      cnt_bombs++;
    } else {
      game_status = GAME_LOSE;
    }
  } else {
    score += tot * lg2(tot);
  }
}
