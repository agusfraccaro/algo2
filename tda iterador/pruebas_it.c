#include "iterador.h"
#include "lista_se.h"

int main(){
	lista_t* lista = crear_lista();

	char elemento_1 = 'A';
	char elemento_2 = 'l';
	char elemento_3 = 'g';
	char elemento_4 = 'o';

	for (int i = 0; i < 3; i++) {
		insertar(lista, &elemento_1);
		insertar(lista, &elemento_2);
		insertar(lista, &elemento_3);
		insertar(lista, &elemento_4);
	}

	iterador_t* iterador = crear_iterador(lista);

	char letra = *(char*)elemento_actual(iterador);
	printf(" %c", letra);
	while(avanzar(iterador) == 0){
		char letra = *(char*)elemento_actual(iterador);
		printf(" %c", letra);
	}

	destruir_iterador(iterador);

	return 0;


}