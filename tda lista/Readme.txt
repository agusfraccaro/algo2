Este tda lista está implementado como nodos simplemente enlazados, donde cada vez que se enlista se crea el nuevo nodo y cuando se borra un elemento se libera ese nodo. Cuando se inserta o se borra de una posición especifica, si esa posición no existe entonces se inserta el ultimo o se borra el ultimo nodo. Si la lista es NULL, entonces el vacía va a devolver TRUE.
En la función que pide la cantidad de elementos de la lista, tomé la decisión de que si la lista es NULL, entonces devuelve 0.
En el archivo pruebas_lista_se.c se encuentran las pruebas dadas por la cátedra modificadas por mí para poder ver mejor el correcto funcionamiento del tda.
Cuando se crea la lista, se chequea que se cree vacía y además se intenta borrar un elemento. 
Cuando se agregan los elementos se chequea que no esté vacía.
Los elementos que se agregan forman LG2MNDE, y luego se insertan en sus respectivas posiciones las letras AOEZ, para completar la palabra ALGO2MENDEZ.
En la inserción en posición se prueba, entre otras posiciones del medio, insertar en la posición 0 y también en una posición que no existe (por lo que se interta al final de la lista) que serían los dos casos bordes y al imprimir se ve que se insertaron bien. Luego de insertar todos los elementos, se imprime cuántos elementos tiene la lista, ese número debería ser 11.

Luego de eliminar algunos elementos de posiciones aleatorias, se destruye la lista que antes de liberarse, libera los nodos que quedaron. Si esto no llega a funcionar, se muestra un mensaje por pantalla avisando.

Línea de compilación: gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

Línea de ejecución: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se
