# Proyecto Final. Algoritmo de búsqueda A*

## Ejemplo ejecución

* Compilar mediante comando:

> g++ -std=c++11 ASearch.cpp Cell.cpp Plot.cpp Program.cpp test.cpp -o test -lcairo $(pkg-config xext x11 cairo-xlib-xrender --cflags --libs)

* Ejecutar programa

> ./test

## Resultado

* Ventana con visualización del tablero, nodo inicial (predador), nodo final (oveja) y etiquetas con el camino más
  corto encontrado.

* En consola, se imprime la lista de coordenadas de las celdas que conforman el camino más corto encontrado.
  Se imprime cada vez que se mueve la oveja.

## Controles

* Movimiento de oveja sobre tablero:

  - Tecla up : movimiento una celda arriba, si es válida.
  - Tecla down : movimiento una celda abajo, si es válida.
  - Tecla left : movimiento una celda a la izquierda, si es válida.
  - Tecla right : movimiento una celda a la derecha, si es válida.
  - Tecla q : movimiento una celda en diagonal izquierda-arriba, si es válida.
  - Tecla w : movimiento una celda en diagonal derecha-arriba, si es válida.
  - Tecla a : movimiento una celda en diagonal izquierda-abajo, si es válida.
  - Tecla s : movimiento una celda en diagonal derecha-abajo, si es válida.

## Compilado con

* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
