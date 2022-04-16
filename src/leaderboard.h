#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

class Leaderboard {
 private:
  FILE *file;
 public:
  struct Player {
    std::string name;
    int score;
    Player();
    Player(const std::string &name, const int &score);
  };
  std::vector<Player> players;
  Leaderboard(FILE *const &f);
  void reset();
  void insert(const std::string &name, const int &score);
  void save() const;
};

#endif
