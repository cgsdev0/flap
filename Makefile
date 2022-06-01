CC=g++
CFLAGS=-lncurses

flap: flap.cpp
	$(CC) -o flap flap.cpp $(CFLAGS)
