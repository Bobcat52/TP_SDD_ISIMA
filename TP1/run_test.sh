!/usr/bin/sh


clear
echo "Trace 0: Pas assez d'argument

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program
"
./bin/main_program
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 1 : Matrice vide

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program matrix/matrice_vide.txt 1 5
"
./bin/main_program matrix/matrice_vide.txt 1 5
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 2 : Matrice à 1 element

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program matrix/matrice_un_element.txt 1 0
"
./bin/main_program matrix/matrice_un_element.txt 1 0
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 3 : Matrice à 2 element de la même usine

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program matrix/matrice_2.txt 2 0
"
./bin/main_program matrix/matrice_2.txt 2 0
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 4 : Matrice avec K > nombre de données dans la matrice

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program matrix/matrice3.txt 5 0
"
./bin/main_program matrix/matrice3.txt 5 0
read -n 1 -s -r -p "
Press any key to continue ..."
*/

clear
echo "Trace 5 : K negatif ou nulle

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program matrix/matrice3.txt -2 0
"
./bin/main_program matrix/matrice3.txt -2 0
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 6 : Retirer une usine non-existante

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program matrix/matrice3.txt 2 3
"
./bin/main_program matrix/matrice3.txt 2 3
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 7 : Mauvais fichier de matrice

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program matrix/matrice_blabla.txt 2 3
"
./bin/main_program matrix/matrice_blabla.txt 2 3
read -n 1 -s -r -p "
Press any key to continue ..."

clear
echo "Trace 8 : Cas général

[FORMAT] : ./bin/main_program matrix_file K indice_factory

./bin/main_program matrix/matrice1.txt 7 5
"
./bin/main_program matrix/matrice1.txt 7 5
read -n 1 -s -r -p "
Press any key to finish.
"
















