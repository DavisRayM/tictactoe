CC?=gcc
CFLAGS?=
SRC_DIR?=src

OBJS:=\
$(SRC_DIR)/main.o\
$(SRC_DIR)/ui.o\
$(SRC_DIR)/board.o\

.PHONY: all clean
.SUFFIXES: .o .c .h

all: tictactoe

tictactoe: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(SRC_DIR)/main.o $(SRC_DIR)/board.o

.c.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

.h.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

clean:
	rm -rf tictactoe */*.d */*.o
