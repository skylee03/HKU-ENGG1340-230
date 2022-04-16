#include "fileio.h"

FILE *access_leaderboard(const char mode[]) {
  return fopen("leaderboard.txt", mode);
}
