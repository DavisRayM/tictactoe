# Tic-Tac-Toe (Terminal-Based AI Opponent)  
![CI](https://github.com/DavisRayM/tictactoe/actions/workflows/ci.yml/badge.svg?branch=main)

A commandline Tic-Tac-Toe game implemented in C, featuring an AI opponent powered by the [Minimax](https://simple.wikipedia.org/wiki/Minimax) algorithm.  

## Limitations  

- Compatible only with Linux environments.  
- Requires a terminal that supports ANSI escape codes; otherwise, the UI may not display correctly.  

## How to Play  

To build and run the game, use the following commands:  

```sh
make  
./tictactoe  
```  

Enjoy playing against the AI!

### Testing

The game has a few tests implemented; mostly for the board representation. In case you'd like to run the tests use:

```sh
make test
```
