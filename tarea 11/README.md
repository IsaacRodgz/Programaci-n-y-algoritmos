# Tarea 11. Visvalingam

## Parámetros:

* Ruta de archivo con puntos en formato: "x,y", un punto por linea
* Umbral de área mínima

## Ejemplo ejecución

* Se prueba el algoritmo con archivo data3.txt y umbral de 1000 de área

> g++ -std=c++11 visvalingam.cpp plot.cpp test2.cpp -o test -lcairo && ./test data3.txt 1000

## Resultado

* En pantalla se imprime el porcentaje de compresión logrado y el error incurrido al simplificar el polígono con el umbral definido.

* Se genera imagen en formato png con los puntos del archivo de entrada en color rojo, las lineas del polígono original en color azul y las líneas del polígono simplificado en color verde.

## Compilado con

* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
