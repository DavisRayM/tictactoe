#include "board.h"
#include "ui.h"
#include <stdio.h>

int main(void) {
  struct Board board;
  initialize_board(&board);
  draw_board(&board);
  return 0;
}
