#include "board.h"
#include <stdlib.h>

void initialize_board(struct Board *board) {
  board->state = (BoardState)malloc(sizeof(enum TokenType) * BOARDSIZE);
  for (int i = 0; i < BOARDSIZE; i++)
    board->state[i] = EMPTY;
  board->gen = 1;
}

void free_board(struct Board *board) {
  free(board->state);
  board->state = NULL;
  board->gen = 0;
}

struct PlayerMove create_move(int x, int y) {
  struct PlayerMove move;
  move.x = x;
  move.y = y;
  return move;
}

enum TokenType current_player(struct Board *board) {
  switch (board->gen % 2) {
  case 0:
    return CIRCLE;
    break;
  default:
    return X;
  }
}

enum TokenType is_game_over(struct Board *board) { return EMPTY; }

struct PlayerMove *valid_moves(struct Board *board, int *numMoves) {
  *numMoves = 0;
  for (int i = 0; i < BOARDSIZE; i++)
    if (board->state[i] == EMPTY)
      *numMoves += 1;

  if (*numMoves == 0)
      return NULL;

  struct PlayerMove *moves =
      (struct PlayerMove *)malloc(sizeof(struct PlayerMove) * (*numMoves));

  int i = 0;
  int j = 0;
  while (i < *numMoves && j < BOARDSIZE) {
    if (board->state[j] == EMPTY) {
      moves[i++] = create_move(j / 3, j % 3);
    }
    j++;
  }

  return moves;
}

BoardState make_move(struct Board *board, struct PlayerMove move) {
  return board->state;
}

BoardState update_state(struct Board *board, BoardState state) {
  BoardState temp = board->state;
  board->state = state;
  return temp;
}

char player_token(enum TokenType token) {
  switch (token) {
  case CIRCLE:
    return 'O';
    break;
  case X:
    return 'X';
    break;
  default:
    return ' ';
    break;
  }
}
