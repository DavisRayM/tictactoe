#include "board.h"
#include <stdbool.h>
#include <stdlib.h>

static void clone_state(BoardState a, BoardState b) {
  for (int i = 0; i < BOARDSIZE; i++)
    b[i] = a[i];
}

static BoardState create_state() {
  BoardState state = (BoardState)malloc(sizeof(enum TokenType) * BOARDSIZE);
  for (int i = 0; i < BOARDSIZE; i++)
    state[i] = EMPTY;
  return state;
}

void initialize_board(struct Board *board) {
  board->state = create_state();
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

enum TokenType game_winner(BoardState state) {
  enum TokenType prev;
  enum TokenType winner = EMPTY;

  /* Check rows for any winner */
  for (int x = 0; x < 3 && winner == EMPTY; x++) {
    prev = state[x * 3 + 0];
    winner = prev;

    for (int y = 1; y < 3; y++) {
      if (prev != state[x * 3 + y]) {
        winner = EMPTY;
        break;
      }
    }
  }

  /* Check columns for any winner */
  for (int y = 0; y < 3 && winner == EMPTY; y++) {
    prev = state[y];
    winner = prev;

    for (int x = 1; x < 3; x++) {
      if (prev != state[x * 3 + y]) {
        winner = EMPTY;
        break;
      }
    }
  }

  /* Check Left-Right Diagonal for any winner */
  if (winner == EMPTY) {
    prev = state[0];
    winner = prev;
    for (int x = 1, y = 1; x < 3 && y < 3; x++, y++) {
      if (prev != state[x * 3 + y]) {
        winner = EMPTY;
        break;
      }
    }
  }

  /* Check Right-Left Diagonal for any winner */
  if (winner == EMPTY) {
    prev = state[2];
    winner = prev;
    for (int x = 2, y = 2; x >= 0 && y >= 0; x--, y--) {
      if (prev != state[x * 3 + y]) {
        winner = EMPTY;
        break;
      }
    }
  }

  return winner;
}

int moves_left(BoardState state) {
  int result = 0;

  for (int i = 0; i < BOARDSIZE; i++)
    if (state[i] == EMPTY)
      result += 1;

  return result;
}

struct PlayerMove *valid_moves(BoardState state) {
  int numMoves = moves_left(state);
  if (numMoves == 0)
    return NULL;

  struct PlayerMove *moves =
      (struct PlayerMove *)malloc(sizeof(struct PlayerMove) * (numMoves));

  int i = 0;
  int j = 0;
  while (i < numMoves && j < BOARDSIZE) {
    if (state[j] == EMPTY) {
      moves[i++] = create_move(j / 3, j % 3);
    }
    j++;
  }

  return moves;
}

BoardState make_move(struct Board *board, struct PlayerMove move) {
  BoardState new_state = create_state();

  clone_state(board->state, new_state);
  new_state[move.x * 3 + move.y] = current_player(board);

  return new_state;
}

BoardState update_state(struct Board *board, BoardState state) {
  BoardState temp = board->state;
  board->state = state;
  board->gen += 1;
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

enum GameState current_state(BoardState state) {
  if (moves_left(state) == 0) {
    switch (game_winner(state)) {
    case EMPTY:
      return DRAW;
      break;
    default:
      return PLAYERWIN;
      break;
    }
  }

  switch (game_winner(state)) {
  case EMPTY:
    return UNDECIDED;
    break;
  default:
    return PLAYERWIN;
    break;
  }
}
