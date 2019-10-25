#include "venganza_arya.h"
#include <stdio.h>
#include <string.h>

const char INFORMACION = 'I';
const char LISTAR_CIUDADES = 'M';
const char AVANZAR_PROX_CIUDAD = 'A';
const char PROX_PERSONA = 'P';
const char ROSTROS_RECOLECTADOS = 'C';
const char MATAR = 'S';
const char NO_MATAR = 'N';
#define VICTIMAS "victimas.txt"
#define CIUDADES "ciudades.dat"
#define COLOR_AZUL "\x1b[44m"
#define COLOR_RESET "\x1b[0m"
#define COLOR_VERDE "\x1b[42m"
#define COLOR_ROJO  "\x1b[41m"

bool validar_letra_matar(char *letra_matar);
void mensaje_entrada_ciudad(jugador_t* jugador, ciudad_t* ciudad_actual);
void menu(char* letra_ingresada, jugador_t* jugador, ciudad_t* ciudad_actual);
bool validar_letra_ingresada(char* letra_ingresada);
void mensaje_asesinar(char* letra_matar, ciudad_t* ciudad_actual);
bool sigue_jugando(jugador_t* jugador);
void pedir_otra_letra(jugador_t* jugador, char* letra, bool (*validar_letra)(char*));
void mostrar_listas(void (*mostrar)(iterador_t*), iterador_t* iterador);
void mensaje_final(jugador_t* jugador);
void imprimir_informacion(jugador_t* jugador);
int eliminar_ciudad_beneficio(iterador_t* it_ciudades, pila_t* victimas);

int main(){
	jugador_t* jugador;
	lista_t* ciudades;
	iterador_t* it_ciudades;
	iterador_t* it_rostros;
	char letra_ingresada;
	char letra_matar;
	char letra;

	jugador = nuevo_jugador();
	if(jugador == NULL){
		printf("No se pudo crear el jugador\n");
	}
	ciudades = crear_lista();
	if(ciudades == NULL){
		printf("No se pudo crear la lista de ciudades\n");
	}
	if(cargar_victimas(VICTIMAS, jugador->victimas) == -1){
		printf("No se pudo cargar correctamente la lista de victimas\n");
	}
	if(cargar_ciudades(CIUDADES, ciudades) == -1){
		printf("No se pudo cargar correctamente la lista de ciudades\n");
	}
	it_ciudades = crear_iterador(ciudades);
	if(it_ciudades == NULL){
		printf("No se pudo crear el iterador de ciudades \n");
	}
	it_rostros = crear_iterador(jugador->rostros);
	if(it_rostros == NULL){
		printf("No se pudo crear el iterador de rostros\n");
	}

	while(sigue_jugando(jugador)){
		ciudad_t* ciudad_actual = (ciudad_t*)elemento_actual(it_ciudades);	
		printf("\nPresiona cualquier letra para acceder al menu\n");
		scanf(" %c",&letra);
		menu(&letra_ingresada, jugador, ciudad_actual);
		pedir_otra_letra(jugador, &letra_ingresada, validar_letra_ingresada);
		if(letra_ingresada == PROX_PERSONA){
			system("clear");
			printf("*******************************\n");
			mostrar_proxima_victima(jugador->victimas);
			printf("*******************************\n");
		}else if(letra_ingresada == ROSTROS_RECOLECTADOS){
			mostrar_listas(mostrar_rostros_recolectados, it_rostros);
		}else if(letra_ingresada == LISTAR_CIUDADES){
			mostrar_listas(mostrar_mapa, it_ciudades);
		}else if(letra_ingresada == AVANZAR_PROX_CIUDAD){
			if(avanzar_mapa(it_ciudades) == -1){
				printf("No se pudo avanzar a la siguiente ciudad\n");
			}
			system("clear");
		}else if(letra_ingresada == INFORMACION){
			system("clear");
			mensaje_asesinar(&letra_matar, ciudad_actual);
			pedir_otra_letra(jugador, &letra_matar, validar_letra_matar);
			if(letra_matar == MATAR){
				system("clear");
				if(ciudad_actual->posible_victima.culpable == 1 && ciudad_actual->posible_victima.beneficio == 2){
					eliminar_ciudad_beneficio(it_ciudades, jugador->victimas);
				}
				if(actualizar_juego(jugador, ciudad_actual->posible_victima) == -1){
					printf("El juego no se actualizó correctamente\n");
				}
			}else if(letra_matar == NO_MATAR){
				system("clear");
				printf("\n%s\n\n", ciudad_actual->posible_victima.msj_perdon);
			}
		}
	}
	mensaje_final(jugador);
	destruir_juego(jugador, ciudades, it_ciudades, it_rostros);
}

void mostrar_listas(void (*mostrar)(iterador_t*), iterador_t* iterador){
	system("clear");
	printf("*******************************\n");
	mostrar(iterador);
	printf("*******************************\n");
}

void pedir_otra_letra(jugador_t* jugador, char* letra, bool (*validar_letra)(char*)){
	while(!validar_letra(letra) && sigue_jugando(jugador)){
		jugador->vida--;
		printf("Ingresa una letra valida!! Estas muriendo!!\n");	
		scanf(" %c", letra);
	}
}

void menu(char* letra_ingresada, jugador_t* jugador, ciudad_t* ciudad_actual){
	system("clear");
	mensaje_entrada_ciudad(jugador, ciudad_actual);
	imprimir_informacion(jugador);
	printf("\n"COLOR_AZUL "¿Qué desea hacer?" COLOR_RESET"\n");
	printf("Presiona I si queres decidir qué hacer con la persona frente a vos\n");
	printf("Presiona M si deseas ver qué ciudades te faltan recorrer\n");
	printf("Presiona A si deseas avanzar a la próxima ciudad\n");
	printf("Presiona P si deseas saber la próxima persona en tu lista\n");
	printf("Presiona C si deseas ver los rostros que tenes recolectados\n");
	printf("Cuidado!!! Si presionas una letra incorrecta perdes vida\n");
	scanf(" %c", letra_ingresada);
}

bool validar_letra_ingresada(char* letra_ingresada){
	return(*letra_ingresada == INFORMACION || *letra_ingresada == LISTAR_CIUDADES || *letra_ingresada == AVANZAR_PROX_CIUDAD || *letra_ingresada == PROX_PERSONA || *letra_ingresada == ROSTROS_RECOLECTADOS);
}

void mensaje_entrada_ciudad(jugador_t* jugador, ciudad_t* ciudad_actual){
	if(!lista_vacia(jugador->rostros) && strcmp((char*)ultimo(jugador->rostros), ciudad_actual->posible_victima.nombre) == 0){
		printf("Estas en la ciudad de " COLOR_ROJO "%s" COLOR_RESET "\n", ciudad_actual->nombre);
		printf("Ante tus ojos se encuentra el cadáver de "COLOR_VERDE"%s"COLOR_RESET"\n\n", ciudad_actual->posible_victima.nombre);
	}else{
		printf("Estas en la ciudad de "COLOR_ROJO"%s"COLOR_RESET"\n", ciudad_actual->nombre);
		printf("Ante tus ojos se encuentra " COLOR_VERDE"%s" COLOR_RESET"\n\n", ciudad_actual->posible_victima.nombre);

	}
}

void mensaje_asesinar(char* letra_matar, ciudad_t* ciudad_actual){
	printf(COLOR_VERDE"%s:"COLOR_RESET "%s\n", ciudad_actual->posible_victima.nombre, ciudad_actual->posible_victima.descripcion);
	scanf(" %c", letra_matar);
}

bool validar_letra_matar(char* letra_matar){
	return (*letra_matar == MATAR || *letra_matar == NO_MATAR);
}

bool sigue_jugando(jugador_t* jugador){
	return (jugador->vida > 0 && !pila_vacia(jugador->victimas));
}

void mensaje_final(jugador_t* jugador){
	if(pila_vacia(jugador->victimas)){
		printf("Felicitaciones, mataste a todos tus enemigos (y un par más) ");
		printf(" y conseguiste tu tan ansiada venganza.\n\n");
	}else if(jugador->vida == 0){
		printf("Lo lamento, Arya, el invierno ha llegado para vos y has muerto.\n\n");
	}
}

void imprimir_informacion(jugador_t* jugador){
	printf("Vida: %i\n", jugador->vida);
	if(jugador->posee_llave == false){
		printf("No tienes la llave\n");
	}else{
		printf("Tienes la llave\n");
	}
}

int eliminar_ciudad_beneficio(iterador_t* it_ciudades, pila_t* victimas){
	int contador = 0;
	char* victima = (char*)tope(victimas);

	ciudad_t* ciudad = (ciudad_t*)elemento_actual(it_ciudades);
	while(strcmp(ciudad->posible_victima.nombre, victima) != 0){
		if(avanzar(it_ciudades) == -1){
			return -1;
		}
	 	ciudad = (ciudad_t*)elemento_actual(it_ciudades);
		
	}

	free(ciudad);
	borrar_de_posicion(it_ciudades->lista, contador);

	it_ciudades->nodo_actual = it_ciudades->lista->inicio;
	it_ciudades->nodo_anterior = NULL;
	return 0;
}