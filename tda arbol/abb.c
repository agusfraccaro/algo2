#include "abb.h"

void* buscar_recursivo(int (*abb_comparador) (void*, void*), nodo_t* raiz, void* elemento);
void inorden(nodo_t* raiz, void** array, int tamanio_array, int* cantidad);
void preorden(nodo_t* raiz, void** array, int tamanio_array, int* cantidad);
void postorden(nodo_t* raiz, void** array, int tamanio_array, int* cantidad);
void destruir_recursivo(void (*abb_liberar_elemento) (void*), nodo_t* raiz);
int insertar_recu(int (*abb_comparador) (void*, void*), nodo_t* raiz, nodo_t* nuevo_nodo);
void borrar_nodo_con_1_hijo(nodo_t* padre, nodo_t* nodo_a_borrar, abb_t* arbol);
void borrar_nodo_sin_hijos(nodo_t* padre, nodo_t* nodo_a_borrar, abb_t* arbol);
void borrar_nodo_con_2_hijos(nodo_t* padre, nodo_t* nodo_a_borrar, abb_t* arbol);
nodo_t* buscar_padre_e_hijo(nodo_t** padre, nodo_t* nodo_a_borrar, abb_t* arbol, void* elemento);
nodo_t* mayor_de_menores(nodo_t* nodo, nodo_t** padre_del_reemplazo);
void reemplazar(nodo_t* nodo_reemplazo, nodo_t* padre_del_reemplazo);
nodo_t* crear_nodo(void* elemento);


abb_t* crear_arbol(abb_comparador comparador, abb_liberar_elemento destructor){
	abb_t* arbol;
	arbol = (abb_t*)malloc(sizeof(abb_t));
	if(arbol == NULL){
		return NULL;
	}
	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->destructor = destructor;
	return arbol;
}

bool vacio(abb_t* arbol){
	return(arbol == NULL || arbol->nodo_raiz == NULL);
}


int insertar(abb_t* arbol, void* elemento){
	if(arbol == NULL || elemento == NULL){
		return -1;
	}

	if(buscar(arbol, elemento) != NULL){
		return -1;
	}

	nodo_t* nuevo_nodo = crear_nodo(elemento);
	if(nuevo_nodo == NULL){
		return -1;
	}

	if(vacio(arbol)){
		arbol->nodo_raiz = nuevo_nodo;
		return 0;
	}

	if(insertar_recu(arbol->comparador, arbol->nodo_raiz, nuevo_nodo) == 0){
		return 0;
	}else{
		return -1;
	}
}

int insertar_recu(int (*abb_comparador) (void*, void*), nodo_t* raiz, nodo_t* nuevo_nodo){ //o la hago void???
	if(abb_comparador(raiz->elemento, nuevo_nodo->elemento) == 1){
		if(raiz->izquierda == NULL){
			raiz->izquierda = nuevo_nodo;
			return 0;
		}else{
			return insertar_recu(abb_comparador, raiz->izquierda, nuevo_nodo);	
		}
	}
	if(abb_comparador(raiz->elemento, nuevo_nodo->elemento) == -1){
		if(raiz->derecha == NULL){
			raiz->derecha = nuevo_nodo;
			return 0;
		}else{
			return insertar_recu(abb_comparador, raiz->derecha, nuevo_nodo);
		}
	}
	return -1;
}

nodo_t* crear_nodo(void* elemento){
	nodo_t* nuevo_nodo;
	nuevo_nodo = (nodo_t*)malloc(sizeof(nodo_t));
	if(nuevo_nodo == NULL){
		return NULL;
	}
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->derecha = NULL;
	nuevo_nodo->izquierda = NULL;
	return nuevo_nodo;
}

int recorrer_inorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol == NULL){
		return -1;
	}
	int cantidad = 0;
	inorden(arbol->nodo_raiz, array, tamanio_array, &cantidad);
	
	return cantidad;
}

void inorden(nodo_t* raiz, void** array, int tamanio_array, int* cantidad){
	if(raiz == NULL){
		return;
	}

	if(raiz->izquierda != NULL){
		inorden(raiz->izquierda, array, tamanio_array, cantidad);
	}
	if((*cantidad) < tamanio_array){
		array[(*cantidad)] = raiz->elemento;
		(*cantidad)++;
	}else{
		return;
	}
	if(raiz->derecha != NULL){
		inorden(raiz->derecha, array, tamanio_array, cantidad);	
	}

}

int recorrer_preorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol == NULL){
		return -1;
	}
	int cantidad = 0;
	preorden(arbol->nodo_raiz, array, tamanio_array, &cantidad);
	return cantidad;
}

void preorden(nodo_t* raiz, void** array, int tamanio_array, int* cantidad){
	if(raiz == NULL){
		return;
	}
	if((*cantidad) < tamanio_array){
		array[(*cantidad)] = raiz->elemento;
		(*cantidad)++;
	}else{
		return;
	}

	if(raiz->izquierda != NULL){
		preorden(raiz->izquierda, array, tamanio_array, cantidad);
	}

	if(raiz->derecha != NULL){
		preorden(raiz->derecha, array, tamanio_array, cantidad);
	}
}

int recorrer_postorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol == NULL){
		return -1;
	}
	int cantidad = 0;
	postorden(arbol->nodo_raiz, array, tamanio_array, &cantidad);
	return cantidad;
}

void postorden(nodo_t* raiz, void** array, int tamanio_array, int* cantidad){
	if(raiz == NULL){
		return;
	}

	if(raiz->izquierda != NULL){
		postorden(raiz->izquierda, array, tamanio_array, cantidad);
	}

	if(raiz->derecha != NULL){
		postorden(raiz->derecha, array, tamanio_array, cantidad);
	}
	if((*cantidad) < tamanio_array){
		array[(*cantidad)] = raiz->elemento;
		(*cantidad)++;
	}else{
		return;
	}
}

void* buscar(abb_t* arbol, void* elemento){
	if(arbol == NULL || elemento == NULL){
		return NULL;
	}

	if(arbol->nodo_raiz == NULL){
		return NULL;
	}

	return buscar_recursivo(arbol->comparador, arbol->nodo_raiz, elemento);
}

void* buscar_recursivo(int (*abb_comparador) (void*, void*), nodo_t* raiz, void* elemento){
	if(raiz == NULL){
		return NULL;
	}
	if(abb_comparador(raiz->elemento, elemento) == 0){
		return raiz->elemento;
	}

	if(abb_comparador(raiz->elemento, elemento) == 1){
		return buscar_recursivo(abb_comparador, raiz->izquierda, elemento);
	}else if(abb_comparador(raiz->elemento, elemento) == -1){
		return buscar_recursivo(abb_comparador, raiz->derecha, elemento);
	}
	return NULL;
}

int borrar(abb_t* arbol, void* elemento){
	if(arbol == NULL || elemento == NULL){
		return -1;
	}

	if(buscar(arbol, elemento) == NULL || vacio(arbol)){
		return -1;
	}

	nodo_t* padre = NULL;
	nodo_t* nodo_a_borrar = arbol->nodo_raiz;
	nodo_a_borrar = buscar_padre_e_hijo(&padre, nodo_a_borrar, arbol, elemento);

	if(nodo_a_borrar->izquierda == NULL && nodo_a_borrar->derecha == NULL){
		borrar_nodo_sin_hijos(padre, nodo_a_borrar, arbol);
	}else if(nodo_a_borrar->derecha == NULL || nodo_a_borrar->izquierda == NULL){
		borrar_nodo_con_1_hijo(padre, nodo_a_borrar, arbol);
	}else if(nodo_a_borrar->derecha != NULL && nodo_a_borrar->izquierda != NULL){
		borrar_nodo_con_2_hijos(padre, nodo_a_borrar, arbol);
	}
	return 0;
}

nodo_t* buscar_padre_e_hijo(nodo_t** padre, nodo_t* nodo_a_borrar, abb_t* arbol, void* elemento){
	if(arbol->comparador(nodo_a_borrar->elemento, elemento) == 0){
		return nodo_a_borrar;
	}

	if(arbol->comparador(nodo_a_borrar->elemento, elemento) == 1){
		*padre = nodo_a_borrar;
		return buscar_padre_e_hijo(padre, nodo_a_borrar->izquierda, arbol, elemento);
	}else if(arbol->comparador(nodo_a_borrar->elemento, elemento) == -1){
		*padre = nodo_a_borrar;
		return buscar_padre_e_hijo(padre, nodo_a_borrar->derecha, arbol, elemento);
	}
	return NULL;
}

void borrar_nodo_sin_hijos(nodo_t* padre, nodo_t* nodo_a_borrar, abb_t* arbol){
	if(padre == NULL){
		arbol->nodo_raiz = NULL;
	}else if(padre->izquierda == nodo_a_borrar){
		padre->izquierda = NULL;
	}else if(padre->derecha == nodo_a_borrar){
		padre->derecha = NULL;
	}

	arbol->destructor(nodo_a_borrar->elemento);
	free(nodo_a_borrar);
}

void borrar_nodo_con_1_hijo(nodo_t* padre, nodo_t* nodo_a_borrar, abb_t* arbol){
	if(padre == NULL){
		if(nodo_a_borrar->izquierda != NULL){
			arbol->nodo_raiz = nodo_a_borrar->izquierda;
		}else if(nodo_a_borrar->derecha != NULL){
			arbol->nodo_raiz = nodo_a_borrar->derecha;
		}
	}else if(padre->izquierda == nodo_a_borrar){
		if(nodo_a_borrar->izquierda != NULL){
			padre->izquierda = nodo_a_borrar->izquierda;
		}else if(nodo_a_borrar->derecha != NULL){
			padre->izquierda = nodo_a_borrar->derecha;
		}
	}else if(padre->derecha == nodo_a_borrar){
		if(nodo_a_borrar->izquierda != NULL){
			padre->derecha = nodo_a_borrar->izquierda;
		}else if(nodo_a_borrar->derecha != NULL){
			padre->derecha = nodo_a_borrar->derecha;
		}
	}
	arbol->destructor(nodo_a_borrar->elemento);
	free(nodo_a_borrar);
}


void borrar_nodo_con_2_hijos(nodo_t* padre, nodo_t* nodo_a_borrar, abb_t* arbol){
	nodo_t* padre_del_reemplazo = nodo_a_borrar;
	nodo_t* nodo_reemplazo = mayor_de_menores(nodo_a_borrar->izquierda, &padre_del_reemplazo);
	if(padre == NULL){
		reemplazar(nodo_reemplazo, padre_del_reemplazo);
		arbol->nodo_raiz = nodo_reemplazo;
		nodo_reemplazo->izquierda = nodo_a_borrar->izquierda;
		nodo_reemplazo->derecha = nodo_a_borrar->derecha;
	}else if(padre->derecha == nodo_a_borrar){
		reemplazar(nodo_reemplazo, padre_del_reemplazo);
		nodo_reemplazo->derecha = nodo_a_borrar->derecha;
		nodo_reemplazo->izquierda = nodo_a_borrar->izquierda;
		padre->derecha = nodo_reemplazo;
	}else if(padre->izquierda == nodo_a_borrar){
		reemplazar(nodo_reemplazo, padre_del_reemplazo);
		nodo_reemplazo->derecha = nodo_a_borrar->derecha;
		nodo_reemplazo->izquierda = nodo_a_borrar->izquierda;
		padre->izquierda = nodo_reemplazo;
	}
	arbol->destructor(nodo_a_borrar->elemento);
	free(nodo_a_borrar);
}


nodo_t* mayor_de_menores(nodo_t* nodo, nodo_t** padre_del_reemplazo){
	if(nodo->derecha == NULL){
		return nodo;
	}

	*padre_del_reemplazo = nodo;
	return mayor_de_menores(nodo->derecha, padre_del_reemplazo);
}

void reemplazar(nodo_t* nodo_reemplazo, nodo_t* padre_del_reemplazo){
	if(nodo_reemplazo->izquierda != NULL){
		if(padre_del_reemplazo->izquierda == nodo_reemplazo){
			padre_del_reemplazo->izquierda = nodo_reemplazo->izquierda;
		}else if(padre_del_reemplazo->derecha == nodo_reemplazo){
				padre_del_reemplazo->derecha = nodo_reemplazo->izquierda;
		}
	}else if(nodo_reemplazo->izquierda == NULL){
		if(padre_del_reemplazo->izquierda == nodo_reemplazo){
			padre_del_reemplazo->izquierda = NULL;
		}else if(padre_del_reemplazo->derecha == nodo_reemplazo){
			padre_del_reemplazo->derecha = NULL;
		}
	}
}

int destruir_arbol(abb_t* arbol){
	if(arbol == NULL){
		return -1;
	}
	destruir_recursivo(arbol->destructor, arbol->nodo_raiz);
	free(arbol);
	return 0;
}

void destruir_recursivo(void (*abb_liberar_elemento) (void*), nodo_t* raiz){
	if(raiz == NULL){
		return;
	}
	destruir_recursivo(abb_liberar_elemento, raiz->izquierda);
	destruir_recursivo(abb_liberar_elemento, raiz->derecha);
	abb_liberar_elemento(raiz->elemento);
	free(raiz);
}