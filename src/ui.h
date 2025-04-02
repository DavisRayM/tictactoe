#ifndef _TICTACTOE_UI_H
#define _TICTACTOE_UI_H 1

#include "board.h"
#include <stdio.h>

void draw_board(struct Board *board) {
  printf("     0   1   2  \n");
  printf("   -------------\n");

  for (int x = 0; x < 3; x++) {
    printf("%-3d|", x);
    for (int y = 0; y < 3; y++) {
      printf(" %c |", player_token(board->state[x * 3 + y]));
    }
    printf("\n   -------------\n");
  }
}

#endif
