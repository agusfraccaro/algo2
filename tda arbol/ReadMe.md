## TDA ARBOL

En el zip se encuentran los siguientes archivos:  
- abb.h  
- abb.c  
- pruebas_abb.c  
- El enunciado del TDA  

En el archivo **pruebas_abb.c** se encuentran las pruebas proporcionadas por la cátedra modificadas para que 
se vea el correcto funcionamiento del arbol con mayor precisión.

Se intenta borrar sobre un arbol vacío, luego se le insertan elementos y se imprime el árbol para así ver que
todo se insertó correctamente. Se le hacen varias pruebas, entre ellas buscar un nodo que está y otro que no está,
borrar nodos sin hijos, con un hijo y con dos hijos y luego se muestran los recorridos, por último se borran los nodos
que quedan y se chequea que el árbol haya quedado vacío.
Se le vuelven a insertar elementos para luego ver que el árbol se destruye correctamente, sin pérdida de memoria.

---

### LINEAS DE COMPILACIÓN Y EJECUCIÓN

_Compilacion_: 

`gcc abb.c abb.h pruebas_abb.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0`

_Ejecucion_:

`valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb`





