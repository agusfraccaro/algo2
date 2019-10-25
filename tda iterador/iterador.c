#include "iterador.h"

iterador_t* crear_iterador(lista_t* lista){
	iterador_t* iterador;

	if(lista == NULL){
		return NULL;
	}

	iterador = (iterador_t*)malloc(sizeof(iterador_t));
	if(iterador == NULL){
		return NULL;
	}
	iterador->lista = lista;
	iterador->nodo_actual = lista->inicio;
	iterador->nodo_anterior = NULL;

	return iterador;
}

bool tiene_siguiente(iterador_t* iterador){
	if(iterador == NULL){
		return -1;
	}

	return (iterador->nodo_actual->siguiente != NULL);
}

void* elemento_actual(iterador_t* iterador){
	if(iterador == NULL){
		return NULL;
	}

	return (iterador->nodo_actual->elemento);
}

int avanzar(iterador_t* iterador){

	if((iterador == NULL) || (!tiene_siguiente(iterador))){
		return -1;
	}

	iterador->nodo_anterior = iterador->nodo_actual;
	iterador->nodo_actual = iterador->nodo_actual->siguiente;
	return 0;
}

int destruir_iterador(iterador_t* iterador){
	if(iterador == NULL){
		return -1;
	}

	free(iterador);
	return 0;
}