CC = gcc
LD_FLAGS = -I./include -I./src
CX_FLAGS = -Wall -Wextra -ansi -pedantic -I./include -I./src -g

all: main

main: main.o tree.o stack.o queue.o
	$(CC) ./obj/main.o ./obj/stack.o ./obj/tree.o ./obj/queue.o -o ./bin/main_program $(LD_FLAGS)

main.o: ./src/main.c ./include/ZZ_tree.h
	$(CC) -c ./src/main.c -o ./obj/main.o $(CX_FLAGS) 

tree.o: ./src/ZZ_tree.c ./include/ZZ_base.h
	$(CC) -c ./src/ZZ_tree.c -o ./obj/tree.o $(CX_FLAGS) 

stack.o: ./src/ZZ_stack.c ./include/ZZ_base.h
	$(CC) -c ./src/ZZ_stack.c -o ./obj/stack.o $(CX_FLAGS)

queue.o: ./src/ZZ_queue.c ./include/ZZ_queue.h
	$(CC) -c ./src/ZZ_queue.c -o ./obj/queue.o $(CX_FLAGS) 

