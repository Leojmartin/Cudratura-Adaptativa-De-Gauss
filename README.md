# Cudratura-Adaptativa-De-Gauss


El siguiente es un conjunto de funciones escritas en ANSI C para resolver una integral definida mediante el método de Cuadratura Adaptativa de Gauss.

Primero, se creó la función cuadGauss que recibe como parámetros los extremos del intervalo a integrar, a y b,
y la función a integrar y devuelve el resultado de la integral. 

Luego, se creó la función cuadAdaptativa que recibee como parámetros la función a integrar, fun, el intervalo de integración, a y b, la tolerancia, tol, y un contador, recursión, que nos permite determinar cuántas pasadas deseamos realizar en caso de nunca llegar a la precisión deseada y tener otro criterio de parada y devuelve el valor final de la integral haciendo llamados recursivos a la función cuadGauss.

Nota: Es necesario dominar el tema de cuadratura Gaussiana para poder entender en su totalidad las funciones creadas.
