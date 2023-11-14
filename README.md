# Compuertas para calcular aceleración
El proyecto consta de 2 compuertas, cada una tiene en un extremo un diodo laser que apunta al otro extremo donde se ubuca un fotosensor. Cuando la luz del laser se interrumpe, ocurriendo cuando pasa un objeto por la compuerta, el fotosensor nota la caida de luz y activa un temporizador, al suceder lo mismo por la segunda compuerta el temporizador se detiene y con los datos proporcionados y otras constantes, se puede determinar la aceleración del objeto.

## Explicación del codigo
---
Declaración de los fotosensores:

    AnalogIn ain(A1);
    AnalogIn aout(A2);

---
Variables importantes:

    const double distancia = 0.14;
    Timer t;

* La variable distancia, almacena la distancia que hay entre ambas compuertas
* Se usara la libreria Timer para medir el tiempo.

---
Metodo para calcular la precision del sensor:

    bool sensor(AnalogIn fotoSensor) {
        return fotoSensor.read()==1;
    }

Este metodo, devolvera true mientras el sensor reciba su maximo de luz.

---
    while (sensor(ain)) {};
    while (sensor(aout)) {};

Estos while, se mantienen ejecutando y no permiten que el codigo continue hacia abajo, mientras que el metodo sensor no devuelva un false, es decir, que la luz recibida sea menor que el valor de la precisión.

---
Tiempo:

Se inicia el contador:

    t.start();

Se detiene el contador:

    t.stop();

Obtención del tiempo transcurrido:

    long long tiempo = duration_cast<milliseconds>(t.elapsed_time()).count();

Se recetea el contador:

    t.reset();

---
Calcular la aceleración:

    aceleracion = 2*distancia/pow(tiempo, 2);

---
Mostrar aceleracion por el lcd:

    void escribirLCD(double a) {
        display.cls();
        display.locate(0, 0);
        display.printf("aceleracion: ");
        display.locate(0, 1);
        display.printf("%f", a);
    }

Ya que el lcd cuenta con un maximo de caracteres, se coloca el mensaje de aceleracion en la parte de arriba y su valor en la parte de abajo.

---
### NOTA:
Consideramos que no hace falta un teclado matricial, ya que el programa se ejecuta automaticamente y para volver a medir la aceleración basta con volver a soltar el objeto
