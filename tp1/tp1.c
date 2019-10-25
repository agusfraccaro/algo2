#include "reino.h"

const int IGUALES=1;
const int UNO_MAYOR=1;
const int DOS_MAYOR=-1;

#define REGIONES "regiones.txt"
#define FORMATO_LECTURA "%[^;];%[^;];%i\n"


int comparar_por_ejercito(region_t region_1, region_t region_2){
	if(region_1.ejercito == region_2.ejercito){
		return IGUALES;
	}else if(region_1.ejercito > region_2.ejercito){
		return UNO_MAYOR;
	}else{
		return DOS_MAYOR;
	}
}

int comparar_por_nombre(region_t region_1, region_t region_2){
	int comparacion = strcmp(region_1.nombre, region_2.nombre);
	if(comparacion == 0){
		return IGUALES;
	}else if(comparacion > 0){
		return UNO_MAYOR;
	}else{
		return DOS_MAYOR;
	}
}


int main(){

	FILE* regiones = fopen(REGIONES, "r");
	if(!regiones){
		perror("No se pudo abrir el archivo");
		return -1;
	}

	size_t cantidad_regiones = 0;

	fscanf(regiones, "%lu\n", &cantidad_regiones);

	reino_t* reino = crear_reino(cantidad_regiones);

	region_t region_leida;

	fscanf(regiones, FORMATO_LECTURA, region_leida.nombre, region_leida.lema, &region_leida.ejercito);

	while(reino->cantidad_regiones_actual < reino->cantidad_max_regiones){
		agregar_region(reino, region_leida);		
		fscanf(regiones, FORMATO_LECTURA, region_leida.nombre, region_leida.lema, &region_leida.ejercito);
	}

	int (*comparar_regiones) (region_t, region_t);
	comparar_regiones = comparar_por_ejercito;

	ordenar_reino(reino, comparar_regiones);
	printf("Listado por ejército:\n\n");
	listar_regiones(reino);

	comparar_regiones = comparar_por_nombre;

	ordenar_reino(reino, comparar_regiones);
	printf("Listado por nombre:\n\n" );
	listar_regiones(reino);

	destruir_reino(reino);
	fclose(reinos);

	return 0;
}