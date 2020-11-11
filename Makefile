CC=gcc
CFLAGS= -O2 -Wall
BINS=list_of_words.o game_board.o game_move.o pilha.o crossword_solver.o

all: main clean

main: $(BINS) main.c
	$(CC) $(CFLAGS) $^ -o $@

clean: 
	rm *.o
