CC = gcc
LD_FLAGS = -I./include -I./src
CX_FLAGS = -Wall -Wextra -I./include -I./src

all: main

main: main.o matrix.o
	$(CC) ./obj/main.o ./obj/matrix.o  -o ./bin/main_program $(LD_FLAGS)

main.o: ./src/ZZ_TP1_main.c ./include/ZZ_matrix.h
	$(CC) -c ./src/ZZ_TP1_main.c -o ./obj/main.o $(CX_FLAGS) 

matrix.o: ./src/ZZ_matrix.c ./include/ZZ_matrix.h
	$(CC) -c ./src/ZZ_matrix.c -o ./obj/matrix.o $(CX_FLAGS) 

lchaine.o: ./src/ZZ_Liste_chainee.c ./include/ZZ_Liste_chainee.h
	$(CC) -c ./src/ZZ_Liste_chainee.c -o ./obj/lchaine.o $(CX_FLAGS) 
	
