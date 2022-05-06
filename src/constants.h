#ifndef CONSTANTS_H
#define CONSTANTS_H

// path to leaderboard file
constexpr char        LEADERBOARD_PATH[] ("log/leaderboard.txt");
// size of the board
constexpr int         SIZE_H             (15);
constexpr int         SIZE_W             (60);
// number, values, and appearance of bombs and balloons
constexpr int         NUM_OF_TYPES       (5);
constexpr int         BOMB               (0);
constexpr char        BLOCK_APPEARANCE[] ("@RGBC");
// keyboard events to be handled
constexpr char        GAME_INSTRUCTIOS[] ("QqWwAaSsDd CcEe");
// game status
constexpr int         GAME_GOING         (0);
constexpr int         GAME_WIN           (1);
constexpr int         GAME_LOSE          (2);
constexpr const char *GAME_STATUS[]      {"Going", "Win", "Lose"};     

#endif
