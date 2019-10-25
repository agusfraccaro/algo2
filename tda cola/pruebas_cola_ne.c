#include "cola_ne.h"
#include <stdio.h>

void esta_vacia(cola_t* cola){
	if(vacia(cola)){
		printf("\nLa cola está vacía\n\n");
	}else{
		printf("\nLa cola NO está vacía\n");
	}
}

void desencolar_elementos(cola_t* cola){
	for (int i = 0; i < 11; i++){
		if(desencolar(cola) == -1){
			printf("No se pudo desencolar el elemento\n\n");
		}
	}

}

int main(){
	cola_t* cola = crear_cola();

	esta_vacia(cola);

	if(desencolar(cola) == -1){
		printf("No se pudo desencolar ya que la cola está vacía\n\n");
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

	for (int i = 0; i < 3; i++) {
		encolar(cola, &elemento_1);
		encolar(cola, &elemento_2);
		encolar(cola, &elemento_3);
		encolar(cola, &elemento_4);
		encolar(cola, &elemento_5);
		encolar(cola, &elemento_6);
		encolar(cola, &elemento_7);
		encolar(cola, &elemento_8);
		encolar(cola, &elemento_9);
		encolar(cola, &elemento_10);
		encolar(cola, &elemento_11);
	}

	for (int i = 0; i < 11; i++) {
		printf("%c\n", *(char*)primero(cola));
		if(desencolar(cola) == -1){
			printf("No se pudo desencolar el elemento\n\n");
		}
	}
	esta_vacia(cola);

	desencolar_elementos(cola);
	esta_vacia(cola);

	desencolar_elementos(cola);
	esta_vacia(cola);

	if(destruir_cola(cola) == -1){
		printf("No se pudo destruir la cola\n");
	}

	return 0;
}
