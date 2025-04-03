#ifndef _TICTACTOE_UI_H
#define _TICTACTOE_UI_H 1

#include "board.h"
#include "opponent.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

static void apply_move(struct Board *board, struct PlayerMove move) {
  free(update_state(board, make_move(board, move)));
  clear_screen();
  draw_board(board);
}

/*
 * Requests the user to select a valid move. Returns a non-zero code if function
 * is unable to request user for input; Which currently occurs if no valid move
 * is present in the current board state.
 */
int request_player_move(struct Board *board) {
  if (current_state(board->state) != UNDECIDED) {
    return 1;
  }

  struct PlayerMove move;
  int numMoves = moves_left(board->state);
  struct PlayerMove *moves = valid_moves(board->state);

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
      move = moves[--input];
      break;
    }

    printf("Selected move '%d' is not a valid input.\n", input);
  }

  free(moves);
  apply_move(board, move);
  return 0;
}

/*
 * Requests the AI opponent to make a move; This function may take a while...
 */
int request_opponent_move(struct Board *board) {
  if (current_state(board->state) != UNDECIDED) {
    return 1;
  }

  int score;
  struct PlayerMove move;
  int bestScore = INT_MIN;
  int depth = 0;
  int numMoves = moves_left(board->state);
  enum TokenType opponentToken = current_player(board);
  struct PlayerMove *moves = valid_moves(board->state);

  printf("Computer is thinking...\n");

  for (int i = 0; i < numMoves; i++) {
    BoardState old_state = update_state(board, make_move(board, moves[i]));
    score = minimax(board, &depth, false, opponentToken);
    if (score > bestScore) {
      bestScore = score;
      move = moves[i];
    }
    free(update_state(board, old_state));
  }

  free(moves);
  printf("Searched %d steps ahead... Making a move now.\n", depth);
  sleep(2);
  apply_move(board, move);
  return 0;
}

#endif
