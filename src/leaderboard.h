#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include "constants.h"

class Leaderboard {
 private:
  FILE *file;
 public:
  struct Player {
    time_t time;
    long long score;
    Player();
    Player(const time_t &time, const long long &score);
  };
  std::vector<Player> players;
  Leaderboard(FILE *const &f);
  void reset();
  void insert(const time_t &time, const long long &score);
  void save() const;
};

#endif
