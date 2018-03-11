CC = gcc
LD_FLAGS = -I./include -I./src
CX_FLAGS = -Wall -Wextra -ansi -pedantic -I./include -I./src

all: main

main: main.o matrix.o linkedList.o
	$(CC) ./obj/main.o ./obj/matrix.o ./obj/linkedList.o -o ./bin/main_program $(LD_FLAGS)

main.o: ./src/ZZ_TP1_main.c ./include/ZZ_matrix.h
	$(CC) -c ./src/ZZ_TP1_main.c -o ./obj/main.o $(CX_FLAGS) 

matrix.o: ./src/ZZ_matrix.c ./include/ZZ_matrix.h
	$(CC) -c ./src/ZZ_matrix.c -o ./obj/matrix.o $(CX_FLAGS) 

linkedList.o: ./src/ZZ_linked_list.c ./include/ZZ_linked_list.h
	$(CC) -c ./src/ZZ_linked_list.c -o ./obj/linkedList.o $(CX_FLAGS) 
	
