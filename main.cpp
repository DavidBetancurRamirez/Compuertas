#include "mbed.h"
#include <iostream>
#include <chrono>
#include <cmath>
#include "TextLCD.h"

UnbufferedSerial serial(USBTX, USBRX, 9600);
TextLCD display(D2,D3,D4,D5,D6,D7,TextLCD::LCD16x2);

AnalogIn ain(A1);
AnalogIn aout(A2);

const double distancia = 0.14;

using namespace std;
using namespace chrono;


void escribirLCD(double a) {
    display.cls();
    display.locate(0, 0);
    display.printf("aceleracion: ");
    display.locate(0, 1);
    display.printf("%f", a);
}

bool sensor(AnalogIn fotoSensor) {
    return fotoSensor.read()==1;
}

int main()
{
    Timer t;
    string mensaje;
    double aceleracion;

    while (true) {
        t.reset();

        cout << "Start..."<< endl;
        // Espera hasta que pase algo por la primera compuerta
        while (sensor(ain)) {};

        // Inicializa el contador
        t.start();
        cout << "Inicia contador"<< endl;

        // Espera hasta que pase algo por la segunda compuerta
        while (sensor(aout)) {};

        // Detiene el contador
        t.stop();

        // Obtener el tiempo transcurrido
        long long tiempo = duration_cast<milliseconds>(t.elapsed_time()).count();

        // Pasar de milisegundos a segundos
        double tiempo_s = tiempo/1000.0;

        // Calcular aceleracion
        aceleracion = 2*distancia/pow(tiempo_s, 2);

        escribirLCD(aceleracion);

        cout << "Tiempo: " << tiempo_s << endl;
        cout << "Aceleracion: " << aceleracion << endl;
    }
}
