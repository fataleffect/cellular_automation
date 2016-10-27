# Variable storing the compiler we want to use
GPP = g++

# The flags we'll be passing to the compiler
CFLAGS = -g -Wall -Wextra -pedantic -std=c++11

# Sets the default build goal to all, running 'make' will run 'make all'.
.DEFAULT_GOAL := all

all: $(wildcard *.cpp)
	$(GPP) $(CFLAGS) one-d-automata.cpp
