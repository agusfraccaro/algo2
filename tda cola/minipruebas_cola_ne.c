#include "cola_ne.h"
#include <stdio.h>

int main(){
	cola_t* cola = crear_cola();

	char elemento_1 = 'A';
	char elemento_2 = 'l';
	char elemento_3 = 'g';
	char elemento_4 = 'o';
	char elemento_5 = '2';

	for (int i = 0; i < 3; i++) {
		encolar(cola, &elemento_1);
		encolar(cola, &elemento_2);
		encolar(cola, &elemento_3);
		encolar(cola, &elemento_4);
		encolar(cola, &elemento_5);
	}


	for (int i = 0; i < 5; i++) {
		printf("%c\n", *(char*)primero(cola));
		desencolar(cola);
	}

	destruir_cola(cola);
	return 0;
}