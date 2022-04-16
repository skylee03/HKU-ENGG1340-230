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
  |  |_|  |  |_|  |    _  |    _  |  |_|  |            | [2] Saved Game  |
  |       |       |   |_| |   |_| |       |            | [3] Leaderboard |
  |       |       |    ___|    ___|_     _|            | [4] Quit        |
  |   _   |   _   |   |   |   |     |   |              +-----------------+
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
      
    } else if(c == '2') {
      
    } else if(c == '3') {
      show_leaderboard();
    } else if(c == '4') {
      return;
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
