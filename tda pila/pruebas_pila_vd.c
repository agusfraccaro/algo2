#include "pila_vd.h"
#include <stdio.h>

#define CANTIDAD_ELEMENTOS 11
#define CANTIDAD_ITERACIONES 3

int main(){
	int pudo_desapilar;
	int pudo_destruir;

	char elemento_1 = 'z';
	char elemento_2 = 'e';
	char elemento_3 = 'd';
	char elemento_4 = 'n';
	char elemento_5 = 'e';
	char elemento_6 = 'M';
	char elemento_7 = '2';
	char elemento_8 = 'o';
	char elemento_9 = 'g';
	char elemento_10 = 'l';
	char elemento_11 = 'A';

	pila_t* pila = crear_pila();

	if(vacia(pila)){
		printf("\nLa pila esta vacía\n");
	}

	printf("\nLa pila tiene tamanio %i y tope %i cuando es creada\n\n", pila->tamanio, pila->tope);

	
	for (int i = 0; i < CANTIDAD_ITERACIONES; i++) {
		apilar(pila,&elemento_1);
		apilar(pila,&elemento_2);
		apilar(pila,&elemento_3);
		apilar(pila,&elemento_4);
		apilar(pila,&elemento_5);
		apilar(pila,&elemento_6);
		apilar(pila,&elemento_7);
		apilar(pila, &elemento_8);
		apilar(pila, &elemento_9);
		apilar(pila, &elemento_10);
		apilar(pila, &elemento_11);
		printf("Tope pila al apilar: %i\n", pila->tope);
		printf("Tamanio pila al apilar: %i\n\n", pila->tamanio);
	}
	
	for (int i = 0; i < CANTIDAD_ELEMENTOS; i++) {
		printf("%c\n", *(char*)tope(pila));		
		pudo_desapilar = desapilar(pila);
		if(pudo_desapilar == 1){
			printf("No se pudo desapilar el elemento");
		}

	}
	printf("\nTope al desapilar por primera vez: %i\n", pila->tope);
	printf("Tamanio al desapilar por primera vez: %i\n\n", pila->tamanio);
	printf("-----------------------------\n\n");
	
	for (int i = 0; i < CANTIDAD_ELEMENTOS; i++){
		pudo_desapilar = desapilar(pila);
		if(pudo_desapilar == 1){
			printf("No se pudo desapilar el elemento");
		}

	}
	printf("Tope al desapilar por segunda vez: %i\n",pila->tope);
	printf("Tamanio al desapilar por segunda vez: %i\n\n", pila->tamanio);
	printf("-----------------------------\n\n");

	for(int i = 0; i < CANTIDAD_ELEMENTOS; i++){
		pudo_desapilar = desapilar(pila);
		if(pudo_desapilar == 1){
			printf("No se pudo desapilar el elemento");
		}
	}
	printf("Tope al desapilar por tercera vez: %i\n",pila->tope);
	printf("Tamanio al desapilar al tercera vez: %i\n", pila->tamanio);
	printf("-----------------------------\n\n");

	if(vacia(pila)){
		printf("La pila está vacía\n\n");
	}
	
	pudo_destruir = destruir_pila(pila);
	if(pudo_destruir == 1){
		printf("No se pudo destruir la pila");
		return -1;
	}

	return 0;
}
