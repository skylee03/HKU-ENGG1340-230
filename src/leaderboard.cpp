#include "leaderboard.h"

Leaderboard::Player::Player() {};

Leaderboard::Player::Player(const std::string &name, const int &score) {
  this->name = name;
  this->score = score;
}

Leaderboard::Leaderboard(FILE *const &f) {
  char name[21];
  int score;
  while(~fscanf(f, "%s%d", name, &score)) {
    insert(name, score);
  }
  fclose(f);
}

void Leaderboard::reset() {
  players.clear();
}

void Leaderboard::insert(const std::string &name, const int &score) {
  players.emplace_back(name, score);
  std::sort(players.begin(), players.end(),
            [](const auto &p1, const auto &p2) -> bool {
              return p1.score > p2.score
                  || (p1.score == p2.score && p1.name < p2.name);
            }
  );
  if(players.size() > 10) {
    players.resize(10);
  }
}

void Leaderboard::save() const {
  auto f = fopen("leaderboard.txt", "w+");
  for(const auto &[name, score]:players) {
    fprintf(f, "%s %d", name.c_str(), score);
  }
  fclose(f);
}
