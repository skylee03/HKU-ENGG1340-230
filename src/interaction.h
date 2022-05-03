#ifndef INTERACTION_H
#define INTERACTION_H

#include <cstdlib>
#include <ncurses.h>
#include "fileio.h"

// necessary inisialization for ncurses
void init_interface();

// show mainmenu and handle key events
void show_mainmenu();

// start a new game
void new_game();

// show leaderboard and handle key events
void show_leaderboard();

#endif
