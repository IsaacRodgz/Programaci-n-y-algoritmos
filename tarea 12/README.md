# Tarea 12. UMDA

## Parámetros:

* Population size
* Chromosome size
* Function option to minimize
* Left limit of interval of search
* Right limit of interval of search
* Ranking percentage
* Max number of iterations
* Stopping variance value

## Ejemplo ejecución

* Population size: 12
* Chromosome size: 20
* Function option to minimize: 2
* Left limit of interval of search: -4
* Right limit of interval of search: 4
* Ranking percentage: 30%
* Max number of iterations: 50
* Stopping variance value: 1e-06

> make && ./test 12 20 2 -4 4 50 0.3 0.000001

## Resultado

* Lista de parámetros con los que se ejecutará el algoritmo
* Valor de convergencia para cada iteración
* Solución (x_1, x_2) óptima encontrada y el valor de la función evaluado en dicho punto.
* Número de iteraciones que se ejecutó el algoritmo

## Compilado con

* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
