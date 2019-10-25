#ifndef __VENGANZA_ARYA_H__
#define __VENGANZA_ARYA_H__

#include <stdbool.h>
#include <stdlib.h>
#include "lista_se.h"
#include "pila_vd.h"
#include "iterador.h"

#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 600
#define MAX_MENSAJE 300


typedef struct persona{
	char nombre[MAX_NOMBRE];
	char descripcion[MAX_DESCRIPCION];
	char msj_muerte[MAX_MENSAJE];
	char msj_perdon[MAX_MENSAJE];
	int en_lista;	// 1 si está, 0 en caso contrario
	int culpable;	// 1 si lo es, 0 en caso contrario
	int danio;		// daño proporcionado por una persona inocente
	int beneficio;	// 1 aumenta vida, 2 elimina víctima, 3 llave del castillo
} persona_t;

typedef struct ciudad{
	char nombre[MAX_NOMBRE];
	persona_t posible_victima;
} ciudad_t;

typedef struct jugador{
	int vida;
	bool posee_llave;
	lista_t* rostros;
	pila_t* victimas;
} jugador_t;

jugador_t* nuevo_jugador();

int cargar_ciudades(char archivo[50], lista_t* ciudades);

int cargar_victimas(char archivo[50], pila_t* victimas);

int actualizar_juego(jugador_t* jugador, persona_t persona);

int avanzar_mapa(iterador_t* it_ciudades);

void mostrar_mapa(iterador_t* it_ciudades);

void mostrar_rostros_recolectados(iterador_t* it_rostros);

int mostrar_proxima_victima(pila_t* victimas);

int destruir_juego(jugador_t* jugador, lista_t* ciudades, iterador_t* it_ciudades, iterador_t* it_rostros);

#endif /*__VENGANZA_ARYA__*/