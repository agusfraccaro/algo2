build: pila_vd.h pila_vd.c
	gcc pruebas_pila_vd.c pila_vd.h pila_vd.c -o pila_vd -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

execute: pila_vd
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pila_vd