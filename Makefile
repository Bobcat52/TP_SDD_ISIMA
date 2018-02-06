CC = gcc
LD_FLAGS = -I./include -I./src
CX_FLAGS = -Wall -Wextra -I./include -I./src
SRC = main.c

all: main

main: main.o
	$(CC) main.o -o ./bin/programme $(LD_FLAGS)

main.o: ./src/main.c ./include/main.h
	$(CC) -c ./src/main.c -o main.o $(CX_FLAGS) 
