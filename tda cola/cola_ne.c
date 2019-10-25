#include "cola_ne.h"
#include <stdio.h>

cola_t* crear_cola(){
	cola_t* cola;

	cola = (cola_t*)malloc(sizeof(cola_t));
	if(cola == NULL){
		return NULL;
	}
	cola->frente = NULL;
	cola->final = NULL;

	return cola;
}

bool vacia(cola_t* cola){
	return ((cola->frente == NULL) && (cola->final == NULL));
}

int destruir_cola(cola_t* cola){
	while(!vacia(cola)){
		if(desencolar(cola) == -1){
			return -1;
		}
	}
	free(cola);
	return 0;
}

void* primero(cola_t* cola){
	if(vacia(cola)){
		return NULL;
	}else{
		return (cola->frente->elemento);
	}
}

int encolar(cola_t* cola, void* elemento){
	nodo_t* nuevo_nodo;

	nuevo_nodo = (nodo_t*)malloc(sizeof(nodo_t));
	if(nuevo_nodo == NULL){
		return -1;
	}
	nuevo_nodo->elemento = elemento;

	if(vacia(cola)){
		cola->frente = nuevo_nodo;
		cola->final = nuevo_nodo;
	}else{
		(cola->final)->siguiente = nuevo_nodo;
		cola->final = nuevo_nodo;
	}

	nuevo_nodo->siguiente = NULL;
	return 0;
}

int desencolar(cola_t* cola){
	nodo_t* nodo_borrar;

	if(vacia(cola)){
		return -1;
	}else if(cola->frente == cola->final){
		nodo_borrar = cola->frente;
		cola->frente = NULL;
		cola->final = NULL;
	}else{
		nodo_borrar = cola->frente;
		cola->frente = nodo_borrar->siguiente;
	}
	free(nodo_borrar);
	return 0;
}