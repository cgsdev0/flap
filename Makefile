CC=g++
CFLAGS=-lncurses -std=c++11

flap: flap.cpp
	$(CC) -o flap flap.cpp $(CFLAGS)
