#include "lista_se.h"

lista_se_t* crear_lista (){

    lista_se_t* lista;
    lista = (lista_se_t*) malloc (sizeof (lista_se_t));
    if (lista == NULL){
      lista = NULL;
    }

    lista->inicio = NULL;
    lista->cantidad = 0;

    return lista;
}

nodo_t* crear_nodo (){
    nodo_t* nodo;
    nodo = (nodo_t*) malloc (sizeof (nodo_t));
    if (nodo == NULL){
      return NULL;
    }
    nodo->siguiente = NULL;
    nodo->elemento = NULL;
    return nodo;
}

int insertar (lista_se_t* lista, void* elemento){
    nodo_t* nodo_auxiliar = crear_nodo();
    nodo_t* nodo_puntero = NULL;
    nodo_auxiliar->elemento = elemento;
    int inserto = -1;
    if (vacia (lista)){
      lista->inicio = nodo_auxiliar;
      lista->inicio->siguiente = NULL;
      lista->cantidad ++;
      inserto = 0;
    }else if (lista->cantidad == 1){
      lista->inicio->siguiente = nodo_auxiliar;
      nodo_auxiliar->siguiente = NULL;
      lista->cantidad ++;
      inserto = 0;
    }else if (!vacia (lista)){
      nodo_puntero = lista->inicio;
      while (nodo_puntero->siguiente != NULL){
        nodo_puntero = nodo_puntero->siguiente;
      }
      nodo_puntero->siguiente = nodo_auxiliar;
      lista->cantidad++;
      inserto = 0;
    }
    return inserto;
}

int borrar(lista_se_t* lista){
    int borro = -1;
    nodo_t* nodo_puntero = NULL;
    nodo_t* nodo_eliminar = NULL;
    if (vacia (lista)){
      borro = -1;
    }else if (lista->cantidad == 1){
      nodo_eliminar = lista->inicio;
      lista->inicio = NULL;
      lista->cantidad--;
      free (nodo_eliminar);
      borro = 0;
    }else if (!vacia (lista)){
      nodo_puntero = lista->inicio;
      while (nodo_puntero->siguiente->siguiente != NULL){
        nodo_puntero = nodo_puntero->siguiente;
      }
      nodo_eliminar = nodo_puntero->siguiente;
      nodo_puntero->siguiente = NULL;
      lista->cantidad--;
      free (nodo_eliminar);
      borro = 0;
    }
    return borro;
}

int insertar_en_posicion(lista_se_t* lista, void* elemento, int indice){
    int inserto = -1;
    nodo_t* nodo_puntero;
    nodo_t* nodo_auxiliar = crear_nodo ();
    int posicion = 0;
    nodo_puntero = lista->inicio;
    if (!vacia (lista)){
      while (posicion < indice && nodo_puntero->siguiente != NULL){
        nodo_puntero = nodo_puntero->siguiente;
        posicion++;
      }
      nodo_auxiliar->siguiente = nodo_puntero->siguiente;
      nodo_puntero->siguiente = nodo_auxiliar;
      nodo_puntero->elemento = elemento;
      lista->cantidad++;
      inserto = 0;
    }else if (indice > lista->cantidad){
      insertar (lista, elemento);
      lista->cantidad++;
      inserto = 0;
    }
    return inserto;
}

void* elemento_en_posicion(lista_se_t* lista, int indice){
    void* hay_elemento = NULL;
    int posicion = 0;
    nodo_t* nodo_puntero;
    nodo_puntero = lista->inicio;
    if (vacia (lista)){
      hay_elemento = NULL;
    }else if (!vacia (lista)){
      while (posicion < indice && nodo_puntero->siguiente != NULL){
        nodo_puntero = nodo_puntero->siguiente;
        posicion++;
      }
      hay_elemento = nodo_puntero->elemento;
    }else if (indice > lista->cantidad){
      hay_elemento = ultimo (lista);
    }
    return hay_elemento;
}

int borrar_de_posicion(lista_se_t* lista, int indice){
    nodo_t* nodo_puntero;
    nodo_t* nodo_eliminar;
    int posicion = 0;
    int eliminar = -1;
    nodo_puntero = lista->inicio;
    if (!vacia (lista)){
      while (posicion < (indice-1)){
        nodo_puntero = nodo_puntero->siguiente;
        posicion++;
      }
      nodo_eliminar = nodo_puntero->siguiente;
      nodo_puntero->siguiente = nodo_eliminar->siguiente;
      free (nodo_eliminar);
      lista->cantidad--;
      eliminar = 0;
    }else if (indice > lista->cantidad){
      borrar (lista);
      eliminar = 0;
    }
    return eliminar;
}

bool vacia(lista_se_t* lista){
    bool esta_vacia = false;
    if (lista == NULL){
      esta_vacia = false;
    }else if (lista->inicio == NULL && lista->cantidad == 0){
      esta_vacia = true;
    }
    return esta_vacia;
}

size_t elementos(lista_se_t* lista){
    return lista->cantidad;
}

void* ultimo(lista_se_t* lista){
    void* ultimo = NULL;
    if (vacia (lista)){
      ultimo = NULL;
    }
    nodo_t* nodo_puntero;
    if (!vacia (lista)){
      nodo_puntero = lista->inicio;
      while (nodo_puntero->siguiente != NULL){
        nodo_puntero = nodo_puntero->siguiente;
      }
      ultimo = nodo_puntero->elemento;
    }
    return ultimo;
}

int destruir_lista(lista_se_t* lista){
    int destruyo = -1;
    if (lista != NULL){
      while (!vacia (lista)){
        borrar (lista);
      }
      free (lista);
      destruyo = 0;
    }
    return destruyo;
}
