CC=gcc
CFLAGS=-g -Wall
BINS=list_of_words.o game_board.o game_move.o pilha.o crossword_solver.o

#list_of_words.o: list_of_words.c list_of_words.h
#	$(CC) $(CFLAGS) -c $^
#
#game_move.o: game_move.c game_move.h
#	$(CC) $(CFLAGS) -c $^
#
#game_board.o: game_board.c game_board.h
#	$(CC) $(CFLAGS) -c $^
#
#crossword_solver.o: crossword_solver.c crossword_solver.h
#	$(CC) $(CFLAGS) -c $^
#
#pilha.o: pilha.c pilha.h
#	$(CC) $(CFLAGS) -c $^

main: $(BINS) main.c
	$(CC) $(CFLAGS) $^ -o $@

clean: 
	rm *.o