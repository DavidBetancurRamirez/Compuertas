#include "mbed.h"
#include <iostream>

UnbufferedSerial serial(USBTX, USBRX, 9600);

AnalogIn ain(A1);
AnalogIn aout(A2);

using namespace std::chrono;
Timer t;
const int distancia = 1;
const double precision = 0.4;


bool sensor(AnalogIn fotoSensor) {
    return fotoSensor.read()>precision;
}

int main()
{
    double aceleracion, tiempo;

    while (true) {
        printf("Compuerta 1 \n");
        // Espera hasta que pase algo por la primera compuerta
        while (sensor(ain)) {};

        // Inicializa el contador
        t.start();
        printf("Inicia contador \n");

        // Espera hasta que pase algo por la segunda compuerta
        while (sensor(aout)) {};

        // Detiene el contador
        t.stop();
        printf("Fin contador \n");

        // Mostrar el tiempo por pantalla
        tiempo = duration_cast<milliseconds>(t.elapsed_time()).count();

        // Calcular aceleracion
        aceleracion = 2*distancia/pow(tiempo, 2);

        printf("Tiempo: %f\n", tiempo);
        printf("Aceleracion: %f\n", aceleracion);

        t.reset();
    }
}
/*
int main() {
    while (true) {
        std::cout << ain.read() << endl;
    }
}*/