# Compuertas para calcular aceleración
El proyecto consta de 2 compuertas, cada una tiene en un extremo un diodo laser que apunta al otro extremo donde se ubuca un fotosensor. Cuando la luz del laser se interrumpe, ocurriendo cuando pasa un objeto por la compuerta, el fotosensor nota la caida de luz y activa un temporizador, al suceder lo mismo por la segunda compuerta el temporizador se detiene y con los datos proporcionados y otras constantes, se puede determinar la aceleración del objeto.

## Explicación del codigo
---
Declaración de los fotosensores:

    AnalogIn ain(A1);
    AnalogIn aout(A2);

---
Variables importantes:

    using namespace std::chrono;
    Timer t;
    const int distancia = 1;
    const double precision = 0.4;

* Se usara la libreria Timer para medir el tiempo.
* La variable distancia, almacena la distancia que hay entre ambas compuertas
* La variable precision, determina desde que valor se hara la comparación por la luz recibida por el fotosensor, entre más alto sea, más facil determinara si paso algun objeto por la compuerta. (0 <= precision <= 1)

---
Metodo para calcular la precision del sensor:

    bool sensor(AnalogIn fotoSensor) {
        return fotoSensor.read()>precision;
    }

Este metodo, devolvera true mientras que el fotosensor reciba una cantidad de luz medida, mayor que lo que contenga la variable precisión, falso en caso contrario

---
    while (sensor(ain)) {};
    while (sensor(aout)) {};

Estos while, se mantienen ejecutando y no permiten que el codigo continue hacia abajo, mientras que el metodo sensor no devuelva un false, es decir, que la luz recibida sea menor que el valor de la precisión.

---
Tiempo:

Se inicia el contador:

    t.start();
    printf("Inicia contador \n");

Se detiene el contador:

    t.stop();
    printf("Fin contador \n");

Obtención del tiempo transcurrido:

    tiempo = duration_cast<milliseconds>(t.elapsed_time()).count();

Se recetea el contador:

    t.reset();

---
Calcular la aceleración:

    aceleracion = 2*distancia/pow(tiempo, 2);
