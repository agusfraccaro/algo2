#ifndef REINO_H
#define REINO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_LEMA 50

typedef struct region {
	char nombre[MAX_NOMBRE];
	char lema[MAX_LEMA];
	int ejercito;
} region_t;

typedef struct reino{
	region_t* regiones;
	int cantidad_regiones_actual;
	int cantidad_max_regiones;
} reino_t;

/*
 * Creará la estructura reino, reservando la memoria necesaria.
 * Recibe el máximo de regiones que pueden ser cargadas,
 * esta cantidad sirve para reservar la memoria necesaria.
 * para el vector de regiones.
 * Devolverá la estructura, con el tope inicializado en 0.
 * En caso de no poder crear el reino, devolverá NULL.
*/
reino_t* crear_reino(size_t maximo_regiones);

/*
 * Destruirá la estructura creada para manipular el reino,
 * liberando la memoria reservada para el y sus regiones.
 * Devolverá 0 si pudo liberar la memoria y 1 si no pudo.
*/
int destruir_reino(reino_t* reino);

/*
 * Agregará una región al vector de regiones del reino
 * Devolverá 0 si pudo agregarla y 1 si no pudo.
*/
int agregar_region(reino_t* reino, region_t region);

/*
 * Ordenará el vector de regiones dentro del reino.
 * La función de comparación de regiones vendrá como parámetro,
 * esto permite ordenar al reino por cualquiera de los campos de la región.
*/
void ordenar_reino(reino_t* reino, int (*comparar_regiones) (region_t, region_t));

/*
 * Listará por pantalla las regiones del reino
*/
void listar_regiones(reino_t* reino);

#endif