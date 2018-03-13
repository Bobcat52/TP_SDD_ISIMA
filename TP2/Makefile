CC = gcc
LD_FLAGS = -I./include -I./src
CX_FLAGS = -Wall -Wextra -ansi -pedantic -I./include -I./src

all: main

main: main.o stack.o queue.o
	$(CC) ./obj/main.o ./obj/queue.o ./obj/stack.o -o ./bin/main_program $(LD_FLAGS)

main.o: ./src/main.c ./include/ZZ_queue.h ./include/ZZ_stack.h
	$(CC) -c ./src/main.c -o ./obj/main.o $(CX_FLAGS) 

stack.o: ./src/ZZ_stack.c ./include/ZZ_stack.h
	$(CC) -c ./src/ZZ_stack.c -o ./obj/stack.o $(CX_FLAGS) 

queue.o: ./src/ZZ_queue.c ./include/ZZ_queue.h
	$(CC) -c ./src/ZZ_queue.c -o ./obj/queue.o $(CX_FLAGS) 
	
