#ifndef _TICTACTOE_test_H
#define _TICTACTOE_test_H 1
#include "../src/board.h"
#include <CUnit/CUnit.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static FILE *temp_file = NULL;

static bool playermove_equal(struct PlayerMove a, struct PlayerMove b) {
  return a.x == b.x && a.y == b.y;
}

int init_boardsuite(void) {
  if (NULL == (temp_file = fopen("board_test.txt", "w+")))
    return -1;
  else
    return 0;
}

int clean_boardsuite(void) {
  if (0 != fclose(temp_file)) {
    return -1;
  } else {
    temp_file = NULL;
    return 0;
  }
}

void test_init(void) {
  struct Board board;
  initialize_board(&board);

  for (int i = 0; i < BOARDSIZE; i++)
    CU_ASSERT(EMPTY == board.state[i]);

  CU_ASSERT(board.state != NULL);
  CU_ASSERT(board.gen == 1);

  free_board(&board);

  CU_ASSERT(board.state == NULL);
  CU_ASSERT(board.gen == 0);
}

void test_currentplayer(void) {
  struct Board board;
  initialize_board(&board);

  for (int i = 0; i < 5; i++) {
    CU_ASSERT(X == current_player(&board));
    board.gen += 1;
    CU_ASSERT(CIRCLE == current_player(&board));
    board.gen += 1;
  }

  free_board(&board);
}

void test_player_token(void) {
  CU_ASSERT(' ' == player_token(EMPTY));
  CU_ASSERT('O' == player_token(CIRCLE));
  CU_ASSERT('X' == player_token(X));
}

void test_valid_moves(void) {
  struct Board board;
  struct PlayerMove *moves = NULL;
  int numMoves;

  initialize_board(&board);

  numMoves = moves_left(board.state);
  moves = valid_moves(board.state);

  CU_ASSERT(numMoves == BOARDSIZE);
  CU_ASSERT(moves != NULL);

  int i = 0;
  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 3; y++)
      CU_ASSERT_TRUE(playermove_equal(moves[i++], create_move(x, y)));

  board.state[1] = CIRCLE;
  free(moves);

  moves = NULL;
  numMoves = moves_left(board.state);
  moves = valid_moves(board.state);

  CU_ASSERT(numMoves == BOARDSIZE - 1);
  CU_ASSERT(moves != NULL);

  i = 0;
  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 3; y++) {
      if (i == 1)
        y += 1;
      CU_ASSERT_TRUE(playermove_equal(moves[i++], create_move(x, y)));
    }

  free(moves);
  for (int i = 0; i < BOARDSIZE; i++)
    board.state[i] = CIRCLE;

  moves = NULL;
  numMoves = moves_left(board.state);
  moves = valid_moves(board.state);

  CU_ASSERT(numMoves == 0);
  CU_ASSERT(moves == NULL);

  free_board(&board);
}

void test_game_winner() {
  struct Board board;
  enum TokenType row_winner[] = {
      EMPTY, X, EMPTY, CIRCLE, CIRCLE, CIRCLE, X, X, EMPTY,
  };
  enum TokenType col_winner[] = {X, CIRCLE, X, X, X, X, CIRCLE, CIRCLE, X};
  enum TokenType diagonal_winner1[] = {
      EMPTY, X, X, CIRCLE, X, CIRCLE, X, X, EMPTY,
  };
  enum TokenType diagonal_winner2[] = {
      CIRCLE, X, CIRCLE, CIRCLE, CIRCLE, X, X, X, CIRCLE,
  };
  enum TokenType no_winner[] = {
      CIRCLE, X, CIRCLE, CIRCLE, X, X, X, CIRCLE, CIRCLE,
  };

  initialize_board(&board);

  CU_ASSERT(EMPTY == game_winner(board.state));

  free(update_state(&board, row_winner));
  CU_ASSERT(CIRCLE == game_winner(board.state));

  update_state(&board, col_winner);
  CU_ASSERT(X == game_winner(board.state));

  update_state(&board, diagonal_winner1);
  CU_ASSERT(X == game_winner(board.state));

  update_state(&board, diagonal_winner2);
  CU_ASSERT(CIRCLE == game_winner(board.state));

  update_state(&board, no_winner);
  CU_ASSERT(EMPTY == game_winner(board.state));
}

void test_make_move() {
  struct Board board;
  struct PlayerMove *moves = NULL;
  BoardState new_state = NULL;
  enum TokenType player = EMPTY;
  int numMoves;
  int idx = 0;

  initialize_board(&board);
  numMoves = moves_left(board.state);
  moves = valid_moves(board.state);

  CU_ASSERT(numMoves != 0);

  new_state = make_move(&board, moves[0]);
  player = current_player(&board);
  idx = moves[0].x * 3 + moves[0].y;

  CU_ASSERT(player != board.state[idx]);
  CU_ASSERT(player == new_state[idx]);

  free(moves);
  free(new_state);
  free_board(&board);
}

void test_update_state() {
  struct Board board;
  enum TokenType new_state[] = {
      CIRCLE, CIRCLE, CIRCLE, CIRCLE, CIRCLE, CIRCLE, CIRCLE, CIRCLE, CIRCLE,
  };
  initialize_board(&board);

  CU_ASSERT(board.gen == 1);
  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 3; y++)
      CU_ASSERT(board.state[x * 3 + y] != new_state[x * 3 + y]);

  free(update_state(&board, new_state));
  CU_ASSERT(board.gen == 2);
  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 3; y++)
      CU_ASSERT(board.state[x * 3 + y] == new_state[x * 3 + y]);
}

void test_current_state() {
  enum TokenType ongoing[] = {
      CIRCLE, X, CIRCLE, CIRCLE, EMPTY, X, X, CIRCLE, CIRCLE,
  };
  enum TokenType draw[] = {
      CIRCLE, X, CIRCLE, CIRCLE, X, X, X, CIRCLE, CIRCLE,
  };
  enum TokenType playerwin[] = {
      CIRCLE, X, CIRCLE, CIRCLE, CIRCLE, X, X, X, CIRCLE,
  };

  CU_ASSERT(current_state(ongoing) == UNDECIDED);
  CU_ASSERT(current_state(draw) == DRAW);
  CU_ASSERT(current_state(playerwin) == PLAYERWIN);
}

int register_boardtests(CU_pSuite suite) {
  if ((NULL ==
       CU_add_test(suite, "test of board initialize_board()", test_init)) ||
      (NULL == CU_add_test(suite, "test of board current_player()",
                           test_currentplayer)) ||
      (NULL ==
       CU_add_test(suite, "test of board player_token()", test_player_token)) ||
      (NULL ==
       CU_add_test(suite, "test of board valid_moves()", test_valid_moves)) ||
      (NULL ==
       CU_add_test(suite, "test of board game_winner()", test_game_winner)) ||
      (NULL ==
       CU_add_test(suite, "test of board make_move()", test_make_move)) ||
      (NULL ==
       CU_add_test(suite, "test of board update_state()", test_update_state)) ||
      (NULL == CU_add_test(suite, "test of board current_state()",
                           test_current_state))) {
    return -1;
  }
  return 0;
}

#endif
