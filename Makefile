CC = gcc
LDFLAGS = -lgame -L.
CFLAGS = -Wall -std=c99

all : recolor_text

recolor_text : recolor_text.o libgame.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

test_game_lalanoix: test_game_lalanoix.o game.o
test_game_anouamani: test_game_anouamani.o game.o
test_game_ejin: test_game_ejin.o game.o
test_game_zboumedris: test_game_zboumedris.o game.o

test_game_lalanoix.o: test_game_lalanoix.c game.h
test_game_anouamani.o: test_game_anouamani.c game.h
test_game_ejin.o: test_game_ejin.c game.h
test_game_zboumedris.o: test_game_zboumedris.c game.h


recolor_text.o : recolor_text.c game.h
	$(CC) $(CFLAGS) $< -c

test_lalanoix: test_game_lalanoix
	./test_game_lalanoix delete
	./test_game_lalanoix isover
	./test_game_lalanoix restart

test_anouamani: test_game_anouamani
	./test_game_anouamani nbmovescur
	./test_game_anouamani playonemove
	./test_game_anouamani copy

test_ejin: test_game_ejin
	./test_game_ejin new
	./test_game_ejin newempty
	./test_game_ejin setcell

test_zboumedris: test_game_zboumedris
	./test_game_zboumedris setmax
	./test_game_zboumedris nbmovesmax
	./test_game_zboumedris cellcolor


test: test_game_lalanoix test_game_anouamani test_game_ejin test_game_zboumedris
	./test_game_ejin new
	./test_game_ejin newempty
	./test_game_ejin setcell
	./test_game_zboumedris setmax
	./test_game_zboumedris nbmovesmax
	./test_game_zboumedris cellcolor
	./test_game_anouamani nbmovescur
	./test_game_anouamani playonemove
	./test_game_anouamani copy
	./test_game_lalanoix delete
	./test_game_lalanoix isover
	./test_game_lalanoix restart

libgame.a : game.o game_io.o
	ar -cr libgame.a game.o game_io.o

.PHONY: clean test test_lalanoix test_anouamani test_ejin test_zboumedris

clean :
	rm -f libgame.a recolor_text.o recolor_text