.PHONY: all test clean

LIBRARY_PATH = ../library

CC=gcc
CFLAGS=-O3 -g -I$(LIBRARY_PATH)
DEBUG=valgrind --leak-check=full --show-leak-kinds=all


LIBRARY_SRCS = $(wildcard $(LIBRARY_PATH)/*.c)
LIBRARY_OBJS = $(LIBRARY_SRCS:.c=.o)

REALFILE="real.in"
TESTFILE="test.in"

all:	clean part1 part2

test: 	testpart1 testpart2

makepart%: cleanpart% $(LIBRARY_OBJS)
	@$(CC) $(CFLAGS) part$(*).c $(LIBRARY_OBJS) -o part$(*).out

part%:	makepart%
	@echo "Part $(*)"
	@./part$(*).out $(REALFILE) > part$(*).output
	@cat part$(*).output

testpart%: makepart%
	@echo "Testing part $(*)"
	$(DEBUG) ./part$(*).out $(TESTFILE) > part$(*).output
	@cat part$(*).output

$(LIBRARY_PATH)/%.o: $(LIBRARY_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean: cleanpart1 cleanpart2
	@rm -f $(LIBRARY_OBJS)

cleanpart%:
	@echo "Cleaning part $(*)"
	@rm -f part$(*).out
	@rm -f part$(*).output
