build: hash.c hash.c pruebas_hash.c
	gcc hash.c hash.h pruebas_hash.c -o hash -g -std=c99 -Wall -Wconversion -Werror -Wtype-limits -pedantic -O0

run: hash
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./hash