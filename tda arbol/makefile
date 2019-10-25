build: abb.h abb.c pruebas_abb.c
	gcc abb.c abb.h pruebas_abb.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

run: abb
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb