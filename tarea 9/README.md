# Tarea 9. Programación dinámica

* Knapsack
* Máxima subsecuencia palíndromo
* Probabilidad ganar serie

## Ejecución

* make && ./runTest option [data]

### Knapsack

> make && ./runTest 1 filename

Ejemplo

* make && ./runTest 1 data.txt
* make clean

### Palindromo

> make && ./runTest 2 string

Ejemplo

* make && ./runTest 2 acbbxyzcaw
* make clean

### Probabilidad gana pumas

> make && ./runTest 3 count_pumas count_america total_games

Ejemplo

* make && ./runTest 3 3 2 10
* make clean

## Análisis complejidad palíndormo

* Tiempo

Debido a que el programa se realizó de manera iterativa y se iteran las subsecuenias de palabras mediante un doble ciclo for, la complejidad del algoritmo será de O(n^2). Para el ciclo exterior se iteran las subsecuencias de longitud k, con k desde 2 hasta n, donde n es la longitud de la cadena original. Para el ciclo for interno se iteran las subsecuencias de longitud k que empiezan en indice i y terminan en indice i + k - 1, con i desde 0 hasta len-k+1.

Como en general se tienen n-k+1 subcadenas de tamaño k, En total se iterarán:

Sum{k = 2, ..., n}(n-k+1) = n*Sum{k = 2, ..., n}(1) + Sum{k = 2, ..., n}(k) + Sum{k = 2, ..., n}(1) = n*(n-1) + (n*(n+1)-2)/2 + (n-1). Lo cual es de orden O(n^2)

* Espacio

Respecto al espacio debido a que se reserva memoria para una matriz cuadrada de n*n, la complejidad en espacio será de orden O(n^2).

## Compilado con

* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
