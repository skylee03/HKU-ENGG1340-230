#include <ncurses.h>
#include "interaction.h"

// Main entrance of the game
int main() {
  init_interface();
  show_mainmenu();
  endwin();
}
