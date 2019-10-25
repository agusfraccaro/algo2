#ifndef __ITERADOR__
#define __ITERADOR__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lista_se.h"

typedef struct iterador{
    nodo_t* nodo_actual;
    nodo_t* nodo_anterior;
    lista_t* lista;
} iterador_t;

/*
 * Crea la estructura del iterador, inicializando los campos.
 * Devuelve NULL si no se pudo crear.
 */
iterador_t* crear_iterador(lista_t* lista);

/*
 * Mueve las referencias al siguiente nodo de la lista.
 * Devuelve 0 si pudo avanzar, -1 si no.
 */
int avanzar(iterador_t* iterador);

/*
 * Devuelve true si el nodo que apunta el actual tiene un nodo siguiente,
 * false si no tiene.
 */
bool tiene_siguiente(iterador_t* iterador);

/*  
 * Devuelve el elemento en la posición del actual.
 * Devuelve NULL si algo falla.
 */
void* elemento_actual(iterador_t* iterador);

/*
 * Libera la memoria reservada por el iterador
 */
int destruir_iterador(iterador_t* iterador);

#endif /*__ITERADOR__*/
