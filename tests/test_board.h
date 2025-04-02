#ifndef _TICTACTOE_TEST_BOARD_H
#define _TICTACTOE_TEST_BOARD_H 1
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

void test_board_init(void) {
  struct Board board;
  initialize_board(&board);

  for (int i = 0; i < BOARDSIZE; i++)
    CU_ASSERT(EMPTY == board.state[i]);

  free_board(&board);
}

void test_board_currentplayer(void) {
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

void test_board_valid_moves(void) {
  struct Board board;
  struct PlayerMove *moves = NULL;
  int numMoves = 0;
  initialize_board(&board);

  moves = valid_moves(board.state, &numMoves);

  CU_ASSERT(numMoves == BOARDSIZE);
  CU_ASSERT(moves != NULL);

  int i = 0;
  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 3; y++)
      CU_ASSERT_TRUE(playermove_equal(moves[i++], create_move(x, y)));

  board.state[1] = CIRCLE;
  free(moves);

  moves = NULL;
  moves = valid_moves(board.state, &numMoves);

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
  moves = valid_moves(board.state, &numMoves);

  CU_ASSERT(numMoves == 0);
  CU_ASSERT(moves == NULL);

  free_board(&board);
}

int register_boardtests(CU_pSuite suite) {
  if ((NULL == CU_add_test(suite, "test of board initialize_board()",
                           test_board_init)) ||
      (NULL == CU_add_test(suite, "test of board current_player()",
                           test_board_currentplayer)) ||
      (NULL ==
       CU_add_test(suite, "test of board player_token()", test_player_token)) ||
      (NULL == CU_add_test(suite, "test of board valid_moves()",
                           test_board_valid_moves))) {
    return -1;
  }
  return 0;
}

#endif
