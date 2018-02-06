CC = gcc
LD_FLAGS = -I./include -I./src
CX_FLAGS = -Wall -Wextra -I./include -I./src




all: main test_liste_chaine


test_liste_chaine: liste_chaine.o
	$(CC) ./obj/liste_chaine.o -o ./bin/test_liste_chaine $(LD_FLAGS)

liste_chaine.o: ZZ_Liste_chainee.c ZZ_Liste_chainee.h
	$(CC) -c ./src/ZZ_Liste_chainee.c -o ./obj/liste_chaine.o.o $(CX_FLAGS) 
	
main: main.o
	$(CC) ./obj/main.o -o ./bin/programme $(LD_FLAGS)

main.o: ./src/main.c ./include/main.h
	$(CC) -c ./src/main.c -o ./obj/main.o $(CX_FLAGS) 
