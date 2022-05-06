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
  mvprintw(19, 0, "[Q] Quit | [W/A/S/D] Move | [SPACE] Select | [C] Cancel | [E] Eliminate");
  const std::string ins(GAME_INSTRUCTIOS);
  for(;;) {
    auto &[x, y] = map->current;
    show_map(*map);
    refresh();
    int c = getch();
    while(ins.find(c) == std::string::npos) getch();
    if(c == 'q' || c == 'Q') {
      break;
    } else if(c == 'w' || c == 'W') {
      if(x != 0) x--;
    } else if(c == 'a' || c == 'A') {
      if(y != 0) y--;
    } else if(c == 's' || c == 'S') {
      if(x != SIZE_H - 1) x++;
    } else if(c == 'd' || c == 'D') {
      if(y != SIZE_W - 1) y++;
    } else if(c == ' ') {
      if(map->blocks[x][y].type != 0 && !map->blocks[x][y].vis) {
        const auto p = Map::Position(x, y);
        if(map->path.empty()) {
          map->join_path(p);
        } else {
          const auto &q = map->path.top();
          if(map->is_neighbor(p, q) && map->blocks[x][y].type == map->blocks[q.first][q.second].type) {
            map->join_path(p);
          }
        }
      }
    } else if(c == 'c' || c == 'C') {
      map->clear_path();
    } else if(c == 'e' || c == 'E') {
      map->eliminate();
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
      if(map.current == Map::Position(i, j)) attron(A_BLINK | A_UNDERLINE | A_STANDOUT);
      if(map.blocks[i][j].vis) attron(A_STANDOUT);
      attron(COLOR_PAIR(map.blocks[i][j].type));
      mvaddch(i, j, BLOCK_APPEARANCE[map.blocks[i][j].type]);
      if(map.current == Map::Position(i, j)) attroff(A_BLINK | A_UNDERLINE | A_STANDOUT);
      if(map.blocks[i][j].vis) attroff(A_STANDOUT);
      attroff(COLOR_PAIR(map.blocks[i][j].type));
    }
  }
  attron(A_STANDOUT);
  mvprintw(17, 0, "Status: %6s | Score: %15lld | No. of Bombs: %5d", GAME_STATUS[map.game_status], map.score, map.cnt_bombs);
  attroff(A_STANDOUT);
}

void show_leaderboard() {
  auto leaderboard = new Leaderboard(access_leaderboard("rw+"));
  for(;;) {
    clear();
    move(0, 0);
    printw("______________________________________________\n");
    printw("|  #  |         TIME         |     SCORE     |\n");
    printw("+--------------------------------------------+\n");
    int count = 0;
    for(const auto &[time, score]:leaderboard->players) {
      printw("| %3d | %20s | %13d |\n", count++, ctime(&time), score);
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
