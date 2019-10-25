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


iterador_t* crear_iterador(lista_t* lista);

int avanzar(iterador_t* iterador);

bool tiene_siguiente(iterador_t* iterador);

void* elemento_actual(iterador_t* iterador);

int destruir_iterador(iterador_t* iterador);

#endif /*__ITERADOR__*/
