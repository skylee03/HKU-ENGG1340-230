#include "fileio.h"

FILE *access_leaderboard(const char mode[]) {
  return fopen(LEADERBOARD_PATH, mode);
}
