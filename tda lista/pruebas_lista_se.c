#include "lista_se.h"
#include <stdio.h>

void esta_vacia(lista_se_t* lista){
	if(vacia(lista)){
		printf("La lista está vacía\n\n");
	}else{
		printf("La lista no está vacía \n\n");
	}
}

int main(){
	lista_se_t* lista = crear_lista();
	if(lista == NULL){
		perror("No se pudo crear la lista\n\n");
	}

	esta_vacia(lista);

	if(borrar(lista) == -1){
		printf("No se puede borrar\n\n");
	}

	char elemento_1 = 'A';
	char elemento_2 = 'l';
	char elemento_3 = 'g';
	char elemento_4 = 'o';
	char elemento_5 = '2';
	char elemento_6 = 'M';
	char elemento_7 = 'e';
	char elemento_8 = 'n';
	char elemento_9 = 'd';
	char elemento_10 = 'e';
	char elemento_11 = 'z';

	for (int i = 0; i < 1; i++) {

		insertar(lista, &elemento_2);
		insertar(lista, &elemento_3);
		insertar(lista, &elemento_5);
		insertar(lista, &elemento_6);
		insertar(lista, &elemento_8);
		insertar(lista, &elemento_9);
		insertar(lista, &elemento_10);

	}

	printf("Hay %i elementos en la lista\n\n", (char)elementos(lista));

	esta_vacia(lista);

	insertar_en_posicion(lista, &elemento_1, 0);
	insertar_en_posicion(lista, &elemento_4, 3);
	insertar_en_posicion(lista, &elemento_7, 6);
	insertar_en_posicion(lista, &elemento_11, 10);

	printf("Hay %i elementos en la lista\n\n", (char)elementos(lista));


	for (int i = 0; i < 11; i++) {
		printf("%c\n", *(char*)elemento_en_posicion(lista, i));
	}

	for (int i = 0; i < 10; i+=2) {
		if(borrar_de_posicion(lista, i) == -1){
			printf("No se pudo borrar el elemento\n\n");
		}
	}

	if(destruir_lista(lista) == -1){
		printf("No se pudo imprimir la lista\n\n");
	}
	return 0;
}