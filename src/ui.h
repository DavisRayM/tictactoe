#ifndef _TICTACTOE_UI_H
#define _TICTACTOE_UI_H 1

#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Draws the current board state on the screen.
 */
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

/*
 * Clears the terminal screen.
 *
 * NOTE: This only works for terminals that support ANSI escape codes. I don't
 *       want to use curses for now.
 */
void clear_screen() { printf("\e[1;1H\e[2J"); }

/*
 * Requests the user to select a valid move. Returns a non-zero code if function
 * is unable to request user for input; Which currently occurs if no valid move
 * is present in the current board state.
 */
int request_player_move(struct Board *board, struct PlayerMove *move) {
  int numMoves = moves_left(board->state);
  struct PlayerMove *moves = NULL;

  if (numMoves == 0) {
    return 1;
  }

  moves = valid_moves(board->state);

  printf("Valid moves:\n");
  for (int i = 0; i < numMoves; i++) {
    printf("%-2d: Move to %d(X) %d(Y)\n", i + 1, moves[i].x, moves[i].y);
  }

  while (true) {
    int input = -1;
    printf("\n(Player %c) Select a move: ",
           player_token(current_player(board)));
    scanf("%d", &input);

    if (input > 0 && input <= numMoves) {
      *move = moves[--input];
      break;
    }

    printf("Selected move '%d' is not a valid input.\n", input);
  }

  free(moves);

  return 0;
}

#endif
