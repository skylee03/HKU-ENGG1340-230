#include <ncurses.h>
#include "interaction.h"

int main() {
  init_interface();
  show_mainmenu();
  endwin();
}
