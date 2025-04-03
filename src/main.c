#include "board.h"
#include "ui.h"
#include <stdbool.h>
#include <stdio.h>

int player_turn(struct Board *board, bool isPlayer) {
  clear_screen();
  draw_board(board);

  if (isPlayer)
    return request_player_move(board);
  else
    return request_opponent_move(board);
}

int main(void) {
  struct Board board;
  enum TokenType winner;
  bool playerTurn = true;

  initialize_board(&board);

  while (current_state(board.state) == UNDECIDED) {
    player_turn(&board, playerTurn);
    playerTurn = !playerTurn;
  }

  clear_screen();
  draw_board(&board);
  switch ((winner = game_winner(board.state))) {
  case EMPTY:
    printf("The game has ended in a tie!\n");
    break;
  default:
    printf("The '%c' player has won!\n", player_token(winner));
    break;
  }

  free_board(&board);
  return 0;
}
