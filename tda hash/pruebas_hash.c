#include "hash.h"
#include <stdio.h>
#include <string.h>

extern char* strdup(const char*);

void destruir_string(void* elemento){
  if(elemento){
    printf("(Destructor) Libero el vehiculo: %s\n", (char*)elemento);
    free(elemento);
  }
}

void guardar_vehiculo(hash_t* garage, const char* patente, const char* descripcion){
  char* desc = strdup(descripcion);
  int retorno = guardar_elemento(garage, patente, desc);
  printf("Guardando vehiculo patente %s (%s): ", patente, descripcion);
  printf("%s\n", retorno==0?"EXITO":"ERROR");
}

void quitar_vehiculo(hash_t* garage, const char* patente){
  int retorno = quitar_elemento(garage, patente);
  printf("Retirando vehiculo patente %s: ", patente);
  printf("%s\n", retorno==0?"EXITO":"ERROR");
}

void verificar_vehiculo(hash_t* garage, const char* patente, bool deberia_existir){
  printf("Verifico el vehiculo patente %s: ", patente);
  bool retorno = existe_clave(garage, patente);
  printf("%s\n", (retorno==deberia_existir)?"EXITO":"ERROR");
}

int main(){
  hash_t* garage = crear_hash(destruir_string);

  printf("Se intenta borrar una clave que no existe. La función devuelve -1: %s\n", quitar_elemento(garage, "AC123DC") == -1?"EXITO":"ERROR");
  printf("Intento ver si existe un clave que no existe: %s\n", existe_clave(garage, "ABS000") == false? "EXITO":"ERROR");

  printf("\nAgrego autos al garage\n");
  
  guardar_vehiculo(garage, "AC123BD", "Auto de Mariano");
  guardar_vehiculo(garage, "AB223BD", "Auto de Camila");
  guardar_vehiculo(garage, "OPQ976", "Auto de Lucas");
  guardar_vehiculo(garage, "A421ACB", "Moto de Manu");
  guardar_vehiculo(garage, "AA442CD", "Auto de Guido");
  guardar_vehiculo(garage, "AC152AD", "Auto de Agustina");
  guardar_vehiculo(garage, "DZE443", "Auto de Jonathan");
  guardar_vehiculo(garage, "AA436BA", "Auto de Gonzalo");
  guardar_vehiculo(garage, "QDM443", "Auto de Daniela");
  guardar_vehiculo(garage, "BD123AC", "Auto de Pablo");
  guardar_vehiculo(garage, "CD442AA", "Auto de Micaela");
  guardar_vehiculo(garage, "PQO697", "Auto de Juan");
  guardar_vehiculo(garage, "DZE443", "Auto de Jonathan otra vez");

  printf("\nCantidad de autos debería ser 12: %s \n", cantidad(garage) == 12? "EXITO":"ERROR");
  printf("\n");

  verificar_vehiculo(garage, "QDM443", true);
  verificar_vehiculo(garage, "PQO697", true);
  verificar_vehiculo(garage, "DZE443", true);

  printf("\n");

  quitar_vehiculo(garage, "QDM443");
  quitar_vehiculo(garage, "PQO697");

  printf("\n");

  verificar_vehiculo(garage, "QDM443", false);
  verificar_vehiculo(garage, "PQO697", false);
  
  printf("\n");

  hash_iter_t* iter = crear_iterador(garage);
  while(avanzar_iterador(iter)){
    const char* clave = elemento_actual(iter);
    printf("Patente: %s -- Vehiculo: %s\n", clave, (char*)obtener_elemento(garage, clave));
  }

  printf("\n");
  
  printf("Destruyo el iterador: %s \n", hash_iterador_destruir(iter) == 0? "EXITO":"ERROR");
  printf("Destruyo el hash: %s \n", destruir_hash(garage) == 0? "EXITO":"ERROR");
  
  return 0;
}

