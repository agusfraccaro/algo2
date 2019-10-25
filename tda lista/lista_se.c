#include "lista_se.h"
#define EXITO 0
#define FALLA -1

lista_t* crear_lista(){
	lista_t* lista;

	lista = (lista_t*)malloc(sizeof(lista_t));
	if(lista == NULL){
		return NULL;
	}

	lista->inicio = NULL;
	lista->cantidad = 0;

	return lista;
}

bool lista_vacia(lista_t* lista){
	if(lista == NULL){
		return true;
	}
	return(lista->inicio == NULL && lista->cantidad == 0);
}

size_t elementos(lista_t* lista){
	if(lista == NULL){
		return 0;
	}
	return (lista->cantidad);
}

int insertar(lista_t* lista, void* elemento){

	nodo_t* nuevo_nodo;
	nodo_t* iterador;

	if(lista == NULL){
		return FALLA;
	}

	if(elemento == NULL){
		return FALLA;
	}

	nuevo_nodo = (nodo_t*)malloc(sizeof(nodo_t));
	if(nuevo_nodo == NULL){
		return FALLA;
	}

	if(lista_vacia(lista)){
		lista->inicio = nuevo_nodo;
	}else{
		iterador = lista->inicio;
		while(iterador->siguiente != NULL){
			iterador = iterador->siguiente;
		}
		iterador->siguiente = nuevo_nodo;
	}
	nuevo_nodo->siguiente = NULL;
	nuevo_nodo->elemento = elemento;
	lista->cantidad++;

	return EXITO;
}

int insertar_en_posicion(lista_t* lista, void* elemento, int indice){
	nodo_t* nuevo_nodo;
	nodo_t* iterador;
	int contador = 0;

	if(lista == NULL){
		return FALLA;
	}

	if(elemento == NULL){
		return FALLA;
	}
	
	if(indice >= lista->cantidad){
		if(insertar(lista, elemento) == FALLA){
			return FALLA;
		}
	}else{
		nuevo_nodo = (nodo_t*)malloc(sizeof(nodo_t));
		if(nuevo_nodo == NULL){
			return FALLA;
		}
		nuevo_nodo->elemento = elemento;

		if(lista_vacia(lista)){
			lista->inicio = nuevo_nodo;
		}else if(indice == 0){
			nuevo_nodo->siguiente = lista->inicio;
			lista->inicio = nuevo_nodo;
		}else{
			iterador = lista->inicio;
			while((contador < indice-1)){
				iterador = iterador->siguiente;
				contador++;
			}
			nuevo_nodo->siguiente = iterador->siguiente;
			iterador->siguiente = nuevo_nodo;
		}
		lista->cantidad++;
	}	
	return EXITO;
}

int borrar(lista_t* lista){

	nodo_t* iterador;
	nodo_t* nodo_borrar;

	if(lista == NULL){
		return FALLA;
	}

	if(lista_vacia(lista)){
		return FALLA;
	}else if(lista->cantidad == 1){
		nodo_borrar = lista->inicio;
		lista->inicio = NULL;
	}else{
		iterador = lista->inicio;
		while((iterador->siguiente)->siguiente != NULL){
			iterador = iterador->siguiente;
		}
		nodo_borrar = iterador->siguiente;
		iterador->siguiente = NULL;
	}
	lista->cantidad--;
	free(nodo_borrar);
	return EXITO;	
}

int borrar_de_posicion(lista_t* lista, int indice){
	nodo_t* nodo_borrar;
	nodo_t* iterador;
	int contador = 0;

	if(lista == NULL){
		return FALLA;
	}

	if(lista_vacia(lista)){
		return FALLA;
	}

	
	if(indice == 0){
		nodo_borrar = lista->inicio;
		lista->inicio = nodo_borrar->siguiente;
	}else{
		iterador = lista->inicio;
		while((contador < indice-1)){
			iterador = iterador->siguiente;
			contador ++;
		}
		nodo_borrar = iterador->siguiente;
		iterador->siguiente = nodo_borrar->siguiente;
	}
	lista->cantidad--;
	free(nodo_borrar);	
	return 	EXITO;
}

void* elemento_en_posicion(lista_t* lista, int indice){
	nodo_t* iterador;
	void* elemento;
	int contador = 0;

	if(lista == NULL){
		return NULL;
	}

	if(indice >= lista->cantidad){
		return NULL;
	}else if(indice == 0){
		elemento = lista->inicio->elemento;
	}else{	
		iterador = lista->inicio;
		while(contador < indice){
			iterador = iterador->siguiente;
			contador++;
		}
		elemento = iterador->elemento;
	}
	return elemento;
}

void* ultimo(lista_t* lista){

	nodo_t* iterador;
	void* elemento;

	if(lista == NULL){
		return NULL;
	}

	if(lista_vacia(lista)){
		return NULL;
	}else{
		iterador = lista->inicio;
		while(iterador->siguiente != NULL){
			iterador = iterador->siguiente;
		}
		elemento = iterador->elemento;
	}
	return elemento;
}

int destruir_lista(lista_t* lista){

	if(lista == NULL){
		return FALLA;
	}

	while(!lista_vacia(lista)){
		if(borrar(lista) == FALLA){
			return FALLA;
		}
	}

	free(lista);
	return EXITO;
}