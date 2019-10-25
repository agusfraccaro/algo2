build: cola_ne.c cola_ne.h
	gcc cola_ne.c cola_ne.h pruebas_cola_ne.c  -o cola_ne -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

execute: cola_ne
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./cola_ne