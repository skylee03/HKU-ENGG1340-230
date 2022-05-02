#include "interaction.h"
#include "leaderboard.h"

void init_interface() {
  initscr();
  cbreak();
  noecho();
}

void show_mainmenu() {
  for(;;) {
    clear();
    mvprintw(0, 0 , R"(
  __   __ _______ _______ _______ __   __              +-----------------+
  |  | |  |   _   |       |       |  | |  |            | [1] New Game    |
  |  |_|  |  |_|  |    _  |    _  |  |_|  |            | [2] Leaderboard |
  |       |       |   |_| |   |_| |       |            | [3] Quit        |
  |       |       |    ___|    ___|_     _|            +-----------------+
  |   _   |   _   |   |   |   |     |   |
  |__|_|__|__| |__|___|__ |___|___ _|___|_ _______ _______ ___ __    _ _______ 
  |       |   |   |   |  |_|  |   |  |  | |   _   |       |   |  |  | |       |
  |    ___|   |   |   |       |   |   |_| |  |_|  |_     _|   |   |_| |    ___|
  |   |___|   |   |   |       |   |       |       | |   | |   |       |   | __
  |    ___|   |___|   |       |   |  _    |       | |   | |   |  _    |   ||  |
  |   |___|       |   | ||_|| |   | | |   |   _   | |   | |   | | |   |   |_| |
  |_______|_______|___|_|   |_|___|_|  |__|__| |__| |___| |___|_|  |__|_______|
  )");
    refresh();
    int c = getch();
    while(!('1' <= c && c <= '4')) c = getch();
    if(c == '1') {
      new_game();
    } else if(c == '2') {
      show_leaderboard();
    } else if(c == '3') {
      return;
    }
  }
}

void new_game() {
  clear();
  auto map = new Map;
  mvprintw(19, 0, "[1] Return");
  for(;;) {
    show_map(*map);
    refresh();
    int c = getch();
    while(!('1' <= c && c <= '1')) c = getch();
    if(c == '1') {
      break;
    }
  }
  delete map;
}

void show_map(const Map &map) {
  start_color();
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_RED,   COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE,  COLOR_BLACK);
  init_pair(4, COLOR_CYAN,  COLOR_BLACK);
  for(int i = 0; i < SIZE_H; i++) {
    for(int j = 0; j < SIZE_W; j++) {
      attron(COLOR_PAIR(map.blocks[i][j].type));
      mvaddch(i, j, BLOCK_APPEARANCE[map.blocks[i][j].type]);
      attroff(COLOR_PAIR(map.blocks[i][j].type));
    }
  }
}

void show_leaderboard() {
  auto leaderboard = new Leaderboard(access_leaderboard("rw+"));
  for(;;) {
    clear();
    move(0, 0);
    printw("______________________________________________\n");
    printw("|  #  |         NAME         |     SCORE     |\n");
    printw("+--------------------------------------------+\n");
    int count = 0;
    for(const auto &[name, score]:leaderboard->players) {
      printw("| %3d | %20s | %13d |\n", count++, name.c_str(), score);
    }
    printw("|____________________________________________|\n");
    mvprintw(19, 0, "[1] Return | [2] Reset Leaderboard");
    refresh();
    int c = getch();
    while(!('1' <= c && c <= '2')) c = getch();
    if(c == '1') {
      break;
    } else if(c == '2') {
      leaderboard->reset();
      leaderboard->save();
    }
  }
  delete leaderboard;
}
