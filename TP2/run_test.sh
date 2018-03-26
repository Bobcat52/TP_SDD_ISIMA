!/usr/bin/sh

make

clear
echo "Trace 0: Pas assez d'argument

[FORMAT] : ./bin/main_program fileNameStack

./bin/main_program
"
./bin/main_program
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 1: Nom de fichier invalide

[FORMAT] : ./bin/main_program fileNameStack

./bin/main_program Stack/hello_world.txt
"
./bin/main_program Stack/hello_world.txt
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 2 : Stack vide

[FORMAT] : ./bin/main_program fileNameStack

./bin/main_program Stack/stack0.txt
"
./bin/main_program Stack/stack0.txt
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 3 : Stack 1 élément

[FORMAT] : ./bin/main_program fileNameStack

./bin/main_program Stack/stack1.txt
"
./bin/main_program Stack/stack1.txt
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 4 : Stack pleine

[FORMAT] : ./bin/main_program fileNameStack

./bin/main_program Stack/stack_full.txt
"
./bin/main_program Stack/stack_full.txt
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 5 : Stack à moitié vide/pleine

[FORMAT] : ./bin/main_program fileNameStack

./bin/main_program Stack/stack_semi_full.txt
"
./bin/main_program Stack/stack_semi_full.txt
read -n 1 -s -r -p "
Press any key to continue ...
"








