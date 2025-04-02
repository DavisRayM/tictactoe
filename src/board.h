#ifndef _TICTACTOE_BOARD_H
#define _TICTACTOE_BOARD_H 1

#include <stdint.h>

#define BOARDSIZE 9

/*
 * Board Token Type
 */
enum TokenType {
  EMPTY,
  CIRCLE,
  X,
};

/*
 * State of a TicTacToe Board; A linear array representing all the
 * 9 slots of a tic tac toe board. Index: (x * 3 + y)
 */
typedef enum TokenType *BoardState;

/*
 * Representation of a TicTacToe Board
 */
struct Board {
  BoardState state;
  int gen;
};

/*
 * PlayerMove structure.
 */
struct PlayerMove {
  int x;
  int y;
};

/*
 * Initialize board structure.
 */
void initialize_board(struct Board *board);

/*
 * Free memory allocated for a board.
 */
void free_board(struct Board *board);

/*
 * Creates a player move
 */
struct PlayerMove create_move(int x, int y);

/*
 * Return current player for the current board generation.
 */
enum TokenType current_player(struct Board *board);

/*
 * Returns the current winner of the game if any
 * otherwise returns a TokenType::Empty
 */
enum TokenType is_game_over(struct Board *board);

/*
 * Returns a list of valid player moves for the current generation.
 */
struct PlayerMove *valid_moves(struct Board *board, int *numMoves);

/*
 * Performs the user specified move and returns the new state.
 */
BoardState make_move(struct Board *board, struct PlayerMove move);

/*
 * Updates the current board state to the newest state. Returns the previous
 * state of the board.
 */
BoardState update_state(struct Board *board, BoardState state);

/*
 * Returns printable character for token.
 */
char player_token(enum TokenType token);

#endif
