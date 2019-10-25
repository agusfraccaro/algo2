En el zip se encuentra la biblioteca pila_vd.h donde estan las firmas de las funciones que luego son implementadas en el archivo pila_vd.c.
Hay también un archivo llamado pruebas_pila_vd.c donde se encuentran las pruebas brindadas por la cátedra modificadas por mí para poder ver 
mejor el correcto funcionamiento de la pila. En ese programa, se le agregan a la pila 33 elementos y a través de los printf se puede ver cómo
varía el tope y el tamaño de la pila (lo que yo estipulé fue que cuando el tope fuera igual que el tamaño, este ultimo aumentara el doble). También se puede ver (por un printf) que la pila está vacía el momento después de ser creada y también la correcta inicialización del tope en 0 y el tamaño en 2.
Luego se le desapilan los últimos 11 elementos, que son los que se imprimen por pantalla formando la frase "Algo2Mendez", y luego hay dos for más 
que desapilan el resto de los elementos que quedaban, ahí se puede ver también la correcta variación del tope y el tamaño de la pila (lo que yo estipulé fue que cuando el tope fuera 1/4 del tamaño, entonces este último se reduciría a la mitad), y cómo al terminar de desapilar el vector vuelve a tener tamaño 2 (el tamaño con el que se creó).

Línea de compilación: gcc *.c -o pila_vd -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

Línea de ejecución: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pila_vd
