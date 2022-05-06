#ifndef INTERACTION_H
#define INTERACTION_H

#include <ctime>
#include <cstdlib>
#include <ncurses.h>
#include "fileio.h"
#include "map.h"
#include "leaderboard.h"

// necessary inisialization for ncurses
void init_interface();

// show mainmenu and handle key events
void show_mainmenu();

// start a new game
void new_game();

// show the map
void show_map(const Map &map);

// show leaderboard and handle key events
void show_leaderboard();

#endif
