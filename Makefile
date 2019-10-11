CC = gcc
LDFLAGS = -lgame -L.
CFLAGS = -Wall -std=c99

all : recolor_text

recolor_text : recolor_text.o libgame.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

recolor_text.o : recolor_text.c game.h
	$(CC) $(CFLAGS) $< -c

libgame.a : game.o game_io.o
	ar -cr libgame.a game.o game_io.o

.PHONY: clean
clean :
	rm -f libgame.a recolor_text.o recolor_text
