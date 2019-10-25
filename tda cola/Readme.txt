Este TDA cola está implementado con nodos enlazados, donde cada vez que se encola se crea el nodo nuevo (luego del utimo nodo)donde se va a guardar la información
y cuando se desencola (eliminar el primer nodo de la cola), se libera la memoria ocupada por ese nodo. Para poder liberar la cola, se necesita que todos los nodos 
hayan sido liberados antes.
En el archivo pruebas_cola_ne.c están las pruebas otorgadas por la cátedra modificadas por mí para poder ver mejor el buen funcionamiento de la cola.
Luego de que se crea, se puede ver que ésta se crea vacía y que al intentar desencolar, no te deja ya que justamente no hay nada para desencolar todavía.
Luego se encolan 33 elementos (se forma 3 veces la palabra Algo2Mendez) y el primer for desencola los primeros 11 elementos, imprimiéndolos antes de desencolarlos. Luego se vuelve a chequear que la cola esté vacía y se puede ver que no lo está.
Lo mismo sucede con los otros dos for, ambos desencolan 11 elementos (esta vez sin imprimirlos) y luego de desencolar se chequea si la cola está vacía.
Después del tercer for puede verse que sí, al cola queda vacía lo cual es correcto.

Línea de compilación: gcc *.c  -o cola_ne -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

o gcc cola_ne.c cola_ne.h pruebas_cola_ne.c  -o cola_ne -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 
en caso de que en la misma carpeta tengas los dos archivos de pruebas (Minipruebas y pruebas) 
ya que el compilador te va a decir que hay multiple definición del main.

Línea de ejecución: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./cola_ne
