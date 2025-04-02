#ifndef _TICTACTOE_TEST_BOARD_H
#define _TICTACTOE_TEST_BOARD_H 1
#include <CUnit/CUnit.h>
#include <stdio.h>
#include "../src/board.h"

static FILE *temp_file = NULL;

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
}

int register_boardtests(CU_pSuite suite) {
    if (NULL == CU_add_test(suite, "test of board initializer", test_board_init)) {
        return -1;
    }
    return 0;
}

#endif
