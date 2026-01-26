CC=g++
CFLAGS=-lncurses -std=c++17

flap: flap.cpp
	$(CC) -o flap flap.cpp $(CFLAGS)
