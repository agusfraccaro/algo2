build: lista_se.h lista_se.c
	gcc lista_se.h lista_se.c pruebas_lista_se.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

run: lista_se
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se