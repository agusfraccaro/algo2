## TDA HASH

En el zip se encuentran los siguientes archivos:
- hash.h
- hash.c
- pruebas_hash.c
- Enunciado del TDA

El hash implementado fue de tipo cerrado con resolución de colisiones de forma lineal.
En el archivo **pruebas_hash.c** se encuentran las pruebas proporcionadas por la cátedra modificadas 
para que se vea el correcto funcionamiento del hash con mayor presición. Aclaración: si el hash es NULL, la cantidad de elementos será 0.

Se intenta borrar una clave que no existe dentro del hash también se intenta buscar una clave que no existe dentro del hash, luego se insertan elementos, aseguro que hay colisiones que se resuelven bien y al insertar nuevamente un elemento con la misma clave, este elemento es reemplazado. Se verifican que las claves anteriormente insertadas existan dentro del hash y que la cantidad de elementos en el hash sea igual que la cantidad de elementos ingresados (12 elementos). Luego se eliminan dos elementos y luego se comprueba que esas claves ya no están dentro del hash. Con el iterador se imprimen los elementos que están actualmente en el hash. Por último se destruye el iterador y el hash.	

### LINEAS DE COMPILACIÓN Y EJECUCIÓN

_Compilación_:

`gcc hash.c hash.h pruebas_hash.c -o hash -std=c99 -Wall -Werror -Wconversion -Wtype-limits -pedantic -O0`

_Ejecución_:

`valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./hash`