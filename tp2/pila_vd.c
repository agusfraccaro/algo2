#include "pila_vd.h"

#include <stdio.h>

#define TAMANIO_INICIAL_PILA 2

bool agrandar_pila(pila_t* pila, size_t nuevo_tamanio);
bool reducir_pila(pila_t* pila, size_t nuevo_tamanio);

pila_t* crear_pila(){
	pila_t* pila;

	pila = (pila_t*)malloc(sizeof(pila_t));
	if(pila == NULL){
		return NULL;
	}

	pila->tope = 0;
	pila->tamanio = TAMANIO_INICIAL_PILA;
	
	pila->elementos = malloc((size_t)(pila->tamanio)*(sizeof(void*)));
	if(pila->elementos == NULL){
		free(pila);
		return NULL;
	}

	return pila;
}

bool pila_vacia(pila_t* pila){
	return (pila->tope == 0);
}

void* tope(pila_t* pila){
	if(pila->tope == 0){
		return NULL;
	}
	return pila->elementos[(pila->tope)-1];
}

int destruir_pila(pila_t* pila){
	int pudo_destruir;

	if(pila == NULL || pila->elementos == NULL){
		pudo_destruir = 1;
	}else{
		free(pila->elementos);
		free(pila);
		pudo_destruir = 0;
	}
	return pudo_destruir;
}

int apilar(pila_t* pila, void* elemento){
	int pudo_apilar = 0;

	if(pila->tope == pila->tamanio){
		int nuevo_tamanio = (pila->tamanio)*2;

		if(!agrandar_pila(pila, (size_t)nuevo_tamanio)){
			pudo_apilar = 1;
		}
	}

	pila->elementos[pila->tope] = elemento;
	pila->tope++;

	return pudo_apilar;
}

int desapilar(pila_t* pila){
	int pudo_desapilar = 1;

	if(!pila_vacia(pila)){
		pila->tope--;
		pudo_desapilar = 0;	
	}

	if((pila->tope)*4 < (pila->tamanio) && pila->tamanio > 2){
		int nuevo_tamanio = (pila->tamanio)/2;
		if(!reducir_pila(pila, (size_t)nuevo_tamanio)){
			printf("No se pudo reducir la pila\n");
		}		
	}
	return pudo_desapilar;
}

bool agrandar_pila(pila_t* pila, size_t nuevo_tamanio){
	void** elementos_auxiliar = realloc(pila->elementos, nuevo_tamanio*sizeof(void*));
	if(elementos_auxiliar == NULL){
		printf("No se pudo agrandar la pila\n");
		return false;
	}
	pila->elementos = elementos_auxiliar;
	pila->tamanio = (int)nuevo_tamanio;
	return true;
}

bool reducir_pila(pila_t* pila, size_t nuevo_tamanio){
	void** elementos_auxiliar = realloc(pila->elementos, nuevo_tamanio*sizeof(void*));
	if(elementos_auxiliar == NULL){
		return false;
	}

	pila->elementos = elementos_auxiliar;
	pila->tamanio = (int)nuevo_tamanio;
	return true;
}