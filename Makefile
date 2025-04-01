CC?=gcc
CFLAGS?=-Wall -Wextra -g
SRC_DIR?=src
OBJS:=\
$(SRC_DIR)/main.o

.PHONY: all clean
.SUFFIXES: .o .c

all: tictactoe

tictactoe: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

clean:
	rm -rf tictactoe */*.d */*.o
