CC:=gcc
CFLAGS?=-Wall -Wextra -g
TEST_CFLAGS?=-lcunit
SRC_DIR?=src
TEST_DIR?=tests

OBJS:=\
$(SRC_DIR)/main.o\
$(SRC_DIR)/board.o\

TEST_OBJS:=\
$(TEST_DIR)/test.o\
$(SRC_DIR)/board.o\

.PHONY: all clean test
.SUFFIXES: .o .c .h

all: tictactoe

tictactoe: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

.c.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

.h.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

clean:
	rm -rf tictactoe test */*.d */*.o

test: $(TEST_OBJS)
	$(CC) -o $@ $(TEST_OBJS) $(TEST_CFLAGS)
	./$@
