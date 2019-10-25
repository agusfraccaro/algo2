#include "abb.h"
#include <stdio.h>

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
	c->clave = clave;
    return c;
}

void destruir_cosa(cosa* c){
    if(c)
	free(c);
}

int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
	return 0;

    if(((cosa*)elemento1)->clave > ((cosa*)elemento2)->clave)
	return 1;
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave)
	return -1;
    return 0;
}

void destructor_de_cosas(void* elemento){
    if(!elemento)
	return;
    destruir_cosa((cosa*)elemento);
}

void dibujar(nodo_t* actual, int nivel){
    int i;
    if(actual->derecha != NULL){
        dibujar(actual->derecha, nivel+1);
    }
    for(i = 1; i<=nivel;i++){
        printf("\t");
    }
    printf("%i\n", *(int*)actual->elemento);
    if(actual->izquierda != NULL){
        dibujar(actual->izquierda, nivel+1);
    }
}


int main(){
    abb_t* arbol = crear_arbol(comparar_cosas, destructor_de_cosas);
    printf("El arbol se crea vacío: %s\n", vacio(arbol)==true? "SI":"NO");

    cosa* c1= crear_cosa(1);
    cosa* c2= crear_cosa(2);
    cosa* c3= crear_cosa(3);
    cosa* c4= crear_cosa(4);
    cosa* c5= crear_cosa(5);
    cosa* c6= crear_cosa(6);
    cosa* c7= crear_cosa(7);
    cosa* auxiliar = crear_cosa(0);
    
    insertar(arbol, c4);
    insertar(arbol, c2);
    insertar(arbol, c6);
    insertar(arbol, c1);
    insertar(arbol, c3);
    insertar(arbol, c5);
    insertar(arbol, c7);

    printf("No se puede insertar algo que ya se encuentra en el arbol: %s\n", insertar(arbol, c7)==-1?"SI":"NO");

    printf("El arbol no debe estar vacío luego de insertar: %s\n", vacio(arbol)==false?"SI":"NO");

    dibujar(arbol->nodo_raiz, 0);

    printf("El nodo raiz deberia ser 4: %s\n", ((cosa*)arbol->nodo_raiz->elemento)->clave==4?"SI":"NO");

    auxiliar->clave = 5;
    printf("Busco el elemento 5: %s\n", ((cosa*)buscar(arbol, auxiliar))->clave==5?"SI":"NO");

    auxiliar->clave = 10;
    if((cosa*)buscar(arbol, auxiliar) == NULL){
        printf("El elemento no se encuentra en el arbol\n");
    }else{
        printf("Busco el elemento 10: %s\n", ((cosa*)buscar(arbol,auxiliar))->clave==10? "SI":"NO");
    }

    auxiliar->clave = 7;
    printf("Borro nodo hoja (7): %s\n", (borrar(arbol, auxiliar))==0?"SI":"NO");

    auxiliar->clave = 6;
    printf("Borro nodo con un hijo (6): %s\n", (borrar(arbol, auxiliar))==0?"SI":"NO");

    auxiliar->clave = 2;
    printf("Borro nodo con dos hijos (2): %s\n", (borrar(arbol, auxiliar))==0?"SI":"NO");

    auxiliar->clave = 4;
    printf("Borro la raiz (4): %s\n", (borrar(arbol, auxiliar))==0?"SI":"NO");

    cosa* elementos[10];

    printf("Recorrido inorden (deberian salir en orden 1 3 5): ");
    int cantidad = recorrer_inorden(arbol, (void**)elementos, 10);
    for(int i=0;i<cantidad;i++)
	printf("%i ", elementos[i]->clave);
    printf("\n");

    printf("Recorrido postorden (deberian salir 1 5 3): ");
    cantidad = recorrer_postorden(arbol, (void**)elementos, 10);
    for(int i = 0; i < cantidad; i++){
        printf("%i ", elementos[i]->clave);
    }
    printf("\n");

    printf("Recorrido preorden (deberian salir 3 1 5): ");
    cantidad = recorrer_preorden(arbol, (void**)elementos, 10);
        for(int i = 0; i < cantidad; i++){
            printf("%i ", elementos[i]->clave);
        }
        printf("\n");

    cosa* auxiliar2 = NULL;
    printf("Intento insertar NULL y no puedo: %s\n", insertar(arbol, auxiliar2)==-1?"SI":"NO");

    auxiliar->clave = 3;
    printf("Borro nodo raiz (3): %s\n", borrar(arbol, auxiliar)==0?"SI":"NO");

    auxiliar->clave = 1;
    printf("Borro nodo raiz (1): %s\n", borrar(arbol, auxiliar)==0?"SI":"NO");

    auxiliar->clave = 3;
    printf("Borro el ultimo nodo que queda (3): %s\n", borrar(arbol, auxiliar)==0?"SI":"NO");

    printf("El arbol debería estar vacío: %s\n", vacio(arbol)==true?"SI":"NO");

    free(auxiliar);
    destruir_arbol(arbol);
    return 0;
}
