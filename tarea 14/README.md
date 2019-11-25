# Tarea 13. Multilayer Perceptron

## Parámetros:

* load: 0 para entrenar un modelo y guardarlo, 0 para cargar y evaluar accuracy de modelo preentrenado

## Ejemplo ejecución

* Se entrena red neuronal y se guarda en un archivo

> make && ./test 0

## Resultado

### Resultado modo entrenamiento (load = 0)

* Imágen "loss.png" con la gráfica de la función de costo/pérdida en el eje y. El eje x corresponde
  a la época en donde se evaluó la función de costo.
* Carpeta "model" con 2 archivos:
    * "model/params": Archivo con información general del modelo
      (número de capas, learning rate y función de activación de cada capa)
    * "model/weights": Archivo con las matrices de pesos de cada capa
* En consola se imprime cada 100 épocas, el valor de la función de costo y la época actual del entrenamiento.
  Al final se muestra el accuracy obtenido en el data set de entrenamiento.

### Resultado modo entrenamiento (load = 1)

* En consola se imprime el accuracy del modelo cargado, sobre todo el data set.

## Creación de red neuronal y parámetros

Tres tipos de capas: Data, Dense, Output.

* model.addData(n): Configura el tamaño de entrada a la red (vector de n entradas)
* model.addDense(n, "relu") : Añade capa oculta de n neuronas con función de activación "relu" o "sigmoid"
* model.addOutput(n, "sigmoid"): Añade capa de salida de n neuronas con función de activación "relu" o "sigmoid"

Entrenamiento.

* model.fit(x_train, y_train, num_epochs, batch_size): Se especifica el data set de entrenamiento (x_train,    y_train), número de épocas para entrenar y el tamaño de batch para actualizar los pesos.

Evaluación.

* model.eval(x_test, y_test): Calcula el accuracy en el data set (x_test, y_test)
* model.getAccuracy(): Regresa valor de accuracy calculado con método eval()

## Compilado con

* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
