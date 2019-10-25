#include "reino.h"

#define COLOR_RESET "\033[0m"
#define COLOR_AMARILLO "\x1b[33m"

reino_t* crear_reino(size_t maximo_regiones){

	reino_t* reino;
	reino = (reino_t*)malloc(sizeof(reino_t));
	if(reino == NULL){
		fprintf(stderr, "ocurrio un error");
		return NULL;
	}

	reino->regiones = (region_t*)malloc(maximo_regiones*sizeof(region_t));
	if(reino->regiones == NULL){
		free(reino);
		fprintf(stderr, "ocurrio un error");
		return NULL;
	}

	reino->cantidad_regiones_actual = 0;
	reino->cantidad_max_regiones = (int)maximo_regiones;

	return reino;
}

int destruir_reino(reino_t* reino){

	int destruir;

	if(reino == NULL || reino->regiones == NULL){
		destruir = 1;
	}else{
		free(reino->regiones);
		free(reino);
		destruir = 0;
	}
	return destruir;
}

int agregar_region(reino_t* reino, region_t region){

	int agregar;

	if(reino->cantidad_regiones_actual < reino->cantidad_max_regiones || reino != NULL || reino->regiones != NULL){
		strcpy(reino->regiones[reino->cantidad_regiones_actual].lema, region.lema);
		strcpy(reino->regiones[reino->cantidad_regiones_actual].nombre, region.nombre);
		reino->regiones[reino->cantidad_regiones_actual].ejercito = region.ejercito;
		reino->cantidad_regiones_actual++;
		agregar = 0;
	}else{
		agregar = 1;
	}

	return agregar;
}

void ordenar_reino(reino_t* reino, int (*comparar_regiones) (region_t, region_t)){
	region_t auxiliar;

	for(int i = 0; i < (reino->cantidad_regiones_actual); i++){
		for(int j = 0; j < (reino->cantidad_regiones_actual)-i-1; j++){
			if((*comparar_regiones)(reino->regiones[j], reino->regiones[j+1]) == 1){
				auxiliar = reino->regiones[j];
				reino->regiones[j] = reino->regiones[j+1];
				reino->regiones[j+1] = auxiliar;
			}
		}
	}
}

void listar_regiones(reino_t* reino){

	for(int i = 0; i < (reino->cantidad_regiones_actual); i++){
		printf("-----------------------------------------------------------\n\n");
		printf(COLOR_AMARILLO"Nombre de la región: %s\n "COLOR_RESET, reino->regiones[i].nombre);
		printf(COLOR_AMARILLO"\tLema: %s\n"COLOR_RESET, reino->regiones[i].lema);
		printf(COLOR_AMARILLO"\t\tEjercito: %i\n\n"COLOR_RESET, reino->regiones[i].ejercito);
	}
}

