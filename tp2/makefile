build: venganza_arya.h venganza_arya.c lista_se.h lista_se.c pila_vd.h pila_vd.c juego.c iterador.h iterador.c 
	gcc *.c -g -Wall -Wconversion -Werror -std=c99 -o la_venganza_de_arya

run: la_venganza_de_arya
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./la_venganza_de_arya 