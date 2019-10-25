#include "venganza_arya.h"
#include <stdio.h>
#include <string.h>

const int MAX_VIDA = 100;
const int BENEFICIO_VIDA = 10;
const int BENEFICIO_UNO = 1;
const int BENEFICIO_DOS = 2;

jugador_t* nuevo_jugador(){
	jugador_t* jugador;
	jugador = (jugador_t*) malloc(sizeof(jugador_t));
	if(jugador == NULL){
		return NULL;
	}

	jugador->vida = MAX_VIDA;
	jugador->posee_llave = false;

	jugador->victimas = crear_pila();
	if(jugador->victimas == NULL){
		return NULL;
	}

	jugador->rostros = crear_lista();
	if(jugador->rostros == NULL){
		return NULL;
	}

	return jugador;
}

int cargar_victimas(char archivo[50], pila_t* victimas){
	char* victima_leida;

	if(victimas == NULL){
		return -1;
	}

	FILE* archivo_victimas = fopen(archivo, "r");
	if(!archivo_victimas){
		return -1;
	}

	victima_leida = (char*)malloc(MAX_NOMBRE*sizeof(char*));
	if(victima_leida == NULL){
		return -1;
	}
	int leidos = fscanf(archivo_victimas, "%[^\n]\n", victima_leida);
	
	while(leidos == 1){
		if(apilar(victimas, victima_leida) == -1){
			return -1;
		}
		victima_leida = (char*)malloc(MAX_NOMBRE*sizeof(char*));
		if(victima_leida == NULL){
			return -1;
		}
		leidos = fscanf(archivo_victimas, "%[^\n]\n", victima_leida);
	} 

	free(victima_leida);
	fclose(archivo_victimas);
	return 0;
}

int cargar_ciudades(char archivo[50], lista_t* ciudades){
	ciudad_t* ciudad_leida;

	if(ciudades == NULL){
		return -1;
	}

	FILE* archivo_ciudades = fopen(archivo, "r");
	if(!archivo_ciudades){
		return -1;
	}

	ciudad_leida = (ciudad_t*)malloc(sizeof(ciudad_t));
	if(ciudad_leida == NULL){
		return -1;
	}
	fread(ciudad_leida, sizeof(ciudad_t), 1, archivo_ciudades);
	
	while(!feof(archivo_ciudades)){
		if(insertar(ciudades, ciudad_leida) == -1){
			return -1;
		}
		ciudad_leida = (ciudad_t*)malloc(sizeof(ciudad_t));
		if(ciudad_leida == NULL){
			return -1;
		}
		fread(ciudad_leida, sizeof(ciudad_t), 1, archivo_ciudades);
	}

	free(ciudad_leida);
	fclose(archivo_ciudades);
	return 0;
}

int actualizar_juego(jugador_t* jugador, persona_t persona){
	char* persona_a_borrar;
	char* nombre_persona;

	if(jugador == NULL){
		return -1;
	}

	if(persona.en_lista == 1){
		if(strcmp(persona.nombre, (char*)tope(jugador->victimas)) == 0){
			if(jugador->victimas->tope == 1 && jugador->posee_llave == false){
				jugador->vida = 0;
			}else if((jugador->victimas->tope > 1) || (jugador->victimas->tope == 1 && jugador->posee_llave == true)){
				persona_a_borrar = (char*)tope(jugador->victimas);
				free(persona_a_borrar);
				if(desapilar(jugador->victimas) == 1){
					return -1;
				}
			}
			printf("\n%s \n\n", persona.msj_muerte);
		}else{
			jugador->vida = 0;
		}
	}else if(persona.culpable == 1){
		if(persona.beneficio == BENEFICIO_UNO){
			jugador->vida += BENEFICIO_VIDA;
		}else if(persona.beneficio == BENEFICIO_DOS){
			if(jugador->victimas->tope != 1){
				persona_a_borrar = (char*)tope(jugador->victimas);
				free(persona_a_borrar);
				if(desapilar(jugador->victimas) == 1){
					return -1;
				}
			}
		}else{
			jugador->posee_llave = true;
		}
		printf("\n%s \n\n", persona.msj_muerte);
	}else if(persona.culpable == 0){
		jugador->vida -= persona.danio;
		printf("\n%s \n\n", persona.msj_muerte);
	}
	nombre_persona = (char*)malloc(50*sizeof(char*));
	strcpy(nombre_persona, persona.nombre);
	if(insertar(jugador->rostros, nombre_persona) == -1){
		return -1;
	}
	return 0;	
}

int mostrar_proxima_victima(pila_t* victimas){
	if(victimas == NULL){
		return -1;
	}
	char* prox_victima = (char*)tope(victimas);
	printf("Tu proxima victima es %s \n", prox_victima);
	
	return 0;
}

int avanzar_mapa(iterador_t* it_ciudades){
	ciudad_t* ciudad_a_borrar;

	if(it_ciudades == NULL){
		return -1;
	}
	ciudad_a_borrar = (ciudad_t*)elemento_actual(it_ciudades);
	if(avanzar(it_ciudades) == -1){
		return -1;
	}

	free(ciudad_a_borrar);
	borrar_de_posicion(it_ciudades->lista, 0);
	it_ciudades->nodo_anterior = NULL;

	return 0;
}

void mostrar_mapa(iterador_t* it_ciudades){
	ciudad_t* ciudad_a_imprimir;

	ciudad_a_imprimir = (ciudad_t*)elemento_actual(it_ciudades);
	printf("\nCiudad actual: %s\n", ciudad_a_imprimir->nombre);
	printf("Ciudades por recorrer:\n");

	while(avanzar(it_ciudades) == 0){
		ciudad_a_imprimir = (ciudad_t*)elemento_actual(it_ciudades);
		printf("\t %s\n", ciudad_a_imprimir->nombre);
	}

	it_ciudades->nodo_actual = it_ciudades->lista->inicio;
	it_ciudades->nodo_anterior = NULL;
}

void mostrar_rostros_recolectados(iterador_t* it_rostros){
	char nombre_a_imprimir[MAX_NOMBRE];
	if(it_rostros == NULL){
		return;
	}

	it_rostros->nodo_actual = it_rostros->lista->inicio;
	it_rostros->nodo_anterior = NULL;

	strcpy(nombre_a_imprimir, (char*)elemento_actual(it_rostros));
	printf("Rostros recolectados: \n");
	printf("%s \n", nombre_a_imprimir);
	while(avanzar(it_rostros) == 0){
		strcpy(nombre_a_imprimir, (char*)elemento_actual(it_rostros));
		printf("%s \n", nombre_a_imprimir);
	}
}

int destruir_juego(jugador_t* jugador, lista_t* ciudades, iterador_t* it_ciudades, iterador_t* it_rostros){
	char* persona_a_borrar;
	ciudad_t* ciudad_a_borrar;
	char* rostro_a_borrar;

	while(!pila_vacia(jugador->victimas)){
		persona_a_borrar = (char*)tope(jugador->victimas);
		free(persona_a_borrar);
		desapilar(jugador->victimas);
	}

	if(destruir_pila(jugador->victimas) == 1){
		return -1;
	}

	if(destruir_iterador(it_ciudades) == -1){
		return -1;
	}

	if(destruir_iterador(it_rostros) == -1){
		return -1;
	}

	while(!lista_vacia(ciudades)){
		ciudad_a_borrar = (ciudad_t*)ultimo(ciudades);
		free(ciudad_a_borrar);
		borrar(ciudades);
	}

	if(destruir_lista(ciudades) == -1){
		return -1;
	}

	while(!lista_vacia(jugador->rostros)){
		rostro_a_borrar = (char*)ultimo(jugador->rostros);
		free(rostro_a_borrar);
		borrar(jugador->rostros);
	}

	if(destruir_lista(jugador->rostros) == -1){
		return -1;
	}

	free(jugador);
	return 0;
}