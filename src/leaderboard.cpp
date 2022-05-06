#include "leaderboard.h"

Leaderboard::Player::Player() {};

Leaderboard::Player::Player(const time_t &time, const int &score) {
  this->time = time;
  this->score = score;
}

Leaderboard::Leaderboard(FILE *const &f) {
  time_t time;
  int score;
  while(~fscanf(f, "%ld%d", &time, &score)) {
    insert(time, score);
  }
  fclose(f);
}

void Leaderboard::reset() {
  players.clear();
}

void Leaderboard::insert(const time_t &time, const int &score) {
  players.emplace_back(time, score);
  std::sort(players.begin(), players.end(),
            [](const auto &p1, const auto &p2) -> bool {
              return p1.score > p2.score
                  || (p1.score == p2.score && p1.time < p2.time);
            }
  );
  if(players.size() > 10) {
    players.resize(10);
  }
}

void Leaderboard::save() const {
  auto f = fopen(LEADERBOARD_PATH, "w+");
  for(const auto &[time, score]:players) {
    fprintf(f, "%ld %d", time, score);
  }
  fclose(f);
}
