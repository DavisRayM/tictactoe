#ifndef _TICTACTOE_OPPONENT_H
#define _TICTACTOE_OPPONENT_H 1

#include "board.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * Minimax Algorithm for TicTacToe. Minimax is an adversarial search
 * algorithm; It looks to "mini"mize the opponents chance of winning and
 * "max"imize your(The Opponent in this case) chance of winning.
 *
 * This function will return the best possible score for the
 * minimizing/maximizing player depending on the "maximize" boolean. Letting you
 * know what's the best/worst scenario for each "BoardState"
 */
int minimax(struct Board *board, int *depth, bool maximize,
            enum TokenType opponentToken) {
  int bestScore = 0;
  int numMoves = 0;
  struct PlayerMove *moves = NULL;

  switch (current_state(board->state)) {
  case PLAYERWIN:
    return game_winner(board->state) == opponentToken ? 1 : -1;
    break;
  case DRAW:
    return bestScore;
    break;
  default:
    break;
  }

  numMoves = moves_left(board->state);
  moves = valid_moves(board->state);

  if (maximize) {
    bestScore = INT_MIN;
    for (int i = 0; i < numMoves; i++) {
      BoardState new_state = make_move(board, moves[i]);
      BoardState temp = update_state(board, new_state);

      *depth += 1;
      int score = minimax(board, depth, false, opponentToken);

      bestScore = bestScore > score ? bestScore : score;
      free(update_state(board, temp));
    }
  } else {
    bestScore = INT_MAX;

    for (int i = 0; i < numMoves; i++) {
      BoardState new_state = make_move(board, moves[i]);
      BoardState temp = update_state(board, new_state);

      *depth += 1;
      int score = minimax(board, depth, true, opponentToken);

      bestScore = bestScore < score ? bestScore : score;
      free(update_state(board, temp));
    }
  }

  free(moves);
  return bestScore;
}

#endif
