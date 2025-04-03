#include "board.h"
#include "ui.h"
#include <stdio.h>

int main(void) {
  struct Board board;
  struct PlayerMove move;
  enum TokenType winner;

  initialize_board(&board);

  while (current_state(board.state) == UNDECIDED) {
    clear_screen();
    draw_board(&board);

    request_player_move(&board, &move);
    /* Generate a new state from the move and update the board; Free the memory
     * used by previous state too
     */
    free(update_state(&board, make_move(&board, move)));
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

  return 0;
}
