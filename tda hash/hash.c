#include "hash.h"
#include <string.h>

#define TAM_HASH 97

/*
* pre: recibe la clave del elemento
* post: devuelve un entero positivo 
*/
size_t hashing(const char* clave){
	size_t posicion = 0;
	for(int i = 0; clave[i] != 0; i++){
		posicion += (size_t)clave[i];
	}
	return posicion;
}

/*
* pre: recibe el hash y el indice actual para buscar el proximo disponible dentro del hash
* post: devuelve la siguiente posición libre dentro del hash, si esta no existe devuelve -1.
*/
int buscar_prox_libre(hash_t* hash, size_t indice_actual){
	int i = (int)indice_actual + 1;
	while(hash->datos[i] != NULL){
		i++;
		if(i == hash->tamanio){
			return -1;
		}
	}
	return i;
}

/*
 * pre: el índice es una posición del hash que existe y está ocupada por un elemento
 * post: el elemento en la posición del índice es liberado y esta posición apuntará a NULL.
*/
void borrar_elemento(hash_t* hash, size_t indice){
	hash->destructor(hash->datos[indice]->elemento);
	free(hash->datos[indice]->clave);
	free(hash->datos[indice]);
	hash->datos[indice] = NULL;
	hash->cantidad--;
}

hash_t* crear_hash(hash_destruir_dato_t destruir_elemento){
	hash_t* hash;

	hash = (hash_t*)malloc(sizeof(hash_t));
	if(hash == NULL){
		return NULL;
	}
	hash->cantidad = 0;
	hash->destructor = destruir_elemento;
	hash->tamanio = TAM_HASH;
	hash->datos = malloc((hash->tamanio)*sizeof(hash_campo_t));
	if(hash->datos == NULL){
		free(hash);
		return NULL;
	}
	for(int i = 0; i < hash->tamanio; i++){
		hash->datos[i] = NULL;
	}
	return hash;	
}

int guardar_elemento(hash_t* hash, const char* clave, void* elemento){
	size_t posicion_alternativa;
	if(hash == NULL){
		return -1;
	}

	size_t posicion = hashing(clave);
	size_t indice = posicion % (hash->tamanio);

	if(hash->datos[indice] != NULL){
		if(strcmp(hash->datos[indice]->clave, clave) == 0){
			hash->destructor(hash->datos[indice]->elemento);
			hash->datos[indice]->elemento = elemento;
			return 0;
		}
	}

	hash_campo_t* dato = (hash_campo_t*)malloc(sizeof(hash_campo_t));
	if(dato == NULL){
		return -1;
	}

	dato->elemento = elemento;
	dato->clave = strdup(clave);
	if(dato->clave == NULL){
		free(dato->elemento);
		free(dato);
		return -1;
	}

	if(hash->datos[indice] == NULL){
		hash->datos[indice] = dato;
	}else{
		posicion_alternativa = (size_t)buscar_prox_libre(hash, indice);
		if(posicion_alternativa == -1){
			return -1;
		}
		hash->datos[posicion_alternativa] = dato;
	}
	hash->cantidad++;
	return 0;
}

int quitar_elemento(hash_t* hash, const char* clave){
	if(hash == NULL){
		return -1;
	}

	size_t indice = hashing(clave) % (hash->tamanio);
	if(hash->datos[indice] == NULL){
		return -1;
	}

	if(strcmp(hash->datos[indice]->clave, clave) == 0){
		borrar_elemento(hash, indice);
		return 0;
	}

	while((indice < hash->tamanio) || (strcmp(hash->datos[indice]->clave, clave) != 0)){
		if(strcmp(hash->datos[indice]->clave, clave) == 0){
			borrar_elemento(hash, indice);
			return 0;
		}
		indice ++;
	}
	return -1;
}

size_t cantidad(const hash_t* hash){
	if(hash == NULL){
		return 0;
	}
	return (hash->cantidad);
}

void* obtener_elemento(const hash_t* hash, const char* clave){
	if(hash == NULL){
		return NULL;
	}

	size_t posicion = hashing(clave);
	size_t indice = posicion % hash->tamanio;

	while((indice < hash->tamanio)){
		if(hash->datos[indice] == NULL){
			indice ++;
		}else if(strcmp(hash->datos[indice]->clave, clave) == 0){
			return hash->datos[indice]->elemento;
		}else{
			indice++;
		}
	}
	return NULL;
}

bool existe_clave(const hash_t* hash, const char* clave){
	if(hash == NULL){
		return false;
	}

	size_t indice = hashing(clave) % (hash->tamanio);
	if(hash->datos[indice] == NULL){
		return false;
	}
	while((indice < hash->tamanio)){
		if(hash->datos[indice] == NULL){
			indice ++;
		}else if(strcmp(hash->datos[indice]->clave, clave) == 0){
			return true;
		}else{
			indice ++;
		}
	}
	return false;
}

int destruir_hash(hash_t* hash){
	if(hash == NULL){
		return -1;
	}

	for(int i = 0; i < hash->tamanio; i++){
		if(hash->datos[i] != NULL){
			hash->destructor(hash->datos[i]->elemento);
			free(hash->datos[i]->clave);
			free(hash->datos[i]);
		}
	}
	free(hash->datos);
	free(hash);
	return 0;
}

hash_iter_t* crear_iterador(const hash_t* hash){
	hash_iter_t* iterador;
	iterador = (hash_iter_t*)malloc(sizeof(hash_iter_t));
	if(iterador == NULL){
		return NULL;
	}

	iterador->hash = hash;
	iterador->posicion = 0;

	return iterador;
}

bool avanzar_iterador(hash_iter_t* iterador){
	if(iterador == NULL || esta_al_final(iterador)){
		return false;
	}

	iterador->posicion++;
	
	while(iterador->posicion < iterador->hash->tamanio && iterador->hash->datos[iterador->posicion] == NULL){
		iterador->posicion++;
	}
	if(iterador->posicion == iterador->hash->tamanio){
		return false;
	}

	return true;
}

bool esta_al_final(const hash_iter_t* iterador){
	if(iterador == NULL){
		return false;
	}
	return (iterador->posicion == (iterador->hash->tamanio)-1);
}

const char* elemento_actual(const hash_iter_t* iterador){
	if(iterador == NULL){
		return NULL;
	}
	return (iterador->hash->datos[iterador->posicion]->clave);
}

int hash_iterador_destruir(hash_iter_t* iterador){
	if(iterador == NULL){
		return -1;
	}

	free(iterador);
	return 0;
}