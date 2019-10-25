#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include <stdbool.h>

extern char* strdup(const char*);
typedef void (*hash_destruir_dato_t)(void*);

typedef struct hash_campo{
	char* clave;
	void* elemento;
} hash_campo_t;

typedef struct hash{
	hash_destruir_dato_t destructor; 
	size_t tamanio;
	size_t cantidad;
	hash_campo_t** datos;
} hash_t;

typedef struct hash_iter{
	const hash_t* hash;
	size_t posicion;
} hash_iter_t;


/*
 * Creará el hash, reservando la memoria necesaria para el.
 * Devolverá el hash creado o NULL en caso de no poder crearlo.
 */
hash_t* crear_hash(hash_destruir_dato_t destruir_elemento);

/*
 * Guardara un elemento reservando la memoria necesaria para este.
 * Devolverá 0 si pudo guardarlo o -1 si no pudo.
 * La función de hasheo queda a criterio del alumno.
 */
int guardar_elemento(hash_t* hash, const char* clave, void* elemento);

/*
 * Eliminará un elemento del hash.
 * Devolverá 0 si pudo eliminar o -1 si no pudo.
 */
int quitar_elemento(hash_t* hash, const char* clave);

/*
 * Devolverá un elemento del hash con la clave pasada por parámetro o NULL si no existe.
 */
void* obtener_elemento(const hash_t* hash, const char* clave);

/*
 * Devolverla true si existe una clave dentro del hash o false si no existe.
 */
bool existe_clave(const hash_t* hash, const char* clave);

/*
 * Devolverá la cantidad de elementos almacenados en el hash.
 */
size_t cantidad(const hash_t* hash);

/*
 * Destruirá el hash liberando la memoria reservada por este.
 * Devolverá 0 si pudo destruirlo o -1 si no pudo.
 */
int destruir_hash(hash_t* hash);

/* Iterador externo para el HASH */
/*
 * Creará el hash reservando la memoria necesaria para el mismo.
 * Devolverá NULL en caso de no poder crearlo o el iterador si pudo.
 */
hash_iter_t* crear_iterador(const hash_t* hash);

/*
 * Avanza un elemento en el hash.
 * Devolverá true si pudo avanzar o false si no pudo.
 */
bool avanzar_iterador(hash_iter_t* iterador);

/*
 * Devolverá el elemento actual en el que esta parado el iterador.
 */
const char* elemento_actual(const hash_iter_t* iterador);

/*
 * Devolverá true si el iterador llegó al final del hash o false en otro caso.
 */
bool esta_al_final(const hash_iter_t* iterador);

/*
 * Destruirá el iterador del hash.
 * Devolverá 0 si pudo destruirlo o -1 si no pudo.
 */
int hash_iterador_destruir(hash_iter_t* iterador);

#endif /* __HASH_H__ */
