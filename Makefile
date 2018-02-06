CC = gcc
LD_FLAGS = -I./include -I./src
CX_FLAGS = -Wall -Wextra -I./include -I./src

all: main

main: matrix.o lchaine.o
	$(CC) ./obj/matrix.o ./obj/lchaine.o -o ./bin/programme $(LD_FLAGS)

matrix.o: ./src/ZZ_matrix.c ./include/ZZ_matrix.h
	$(CC) -c ./src/ZZ_matrix.c -o ./obj/matrix.o $(CX_FLAGS) 

lchaine.o: ZZ_Liste_chainee.c ZZ_Liste_chainee.h
	$(CC) -c ./src/ZZ_Liste_chainee.c -o ./obj/lchaine.o $(CX_FLAGS) 
	
