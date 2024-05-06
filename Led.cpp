/*Led.cpp*/
#include "Led.h"
#include <Arduino.h>

/* Constructor de objetos */
Led::Led(int pinLED) : pin(pinLED) {}

/* Inicializador de objetos */
void Led::begin()
{
    pinMode(pin, OUTPUT);

    apagar();
}

/* Activa una salida en estado alto para encender el Led */
void Led::encender()
{
    digitalWrite(pin, 1);
}

/* Activa una salida en estado bajo para apagar el Led */
void Led::apagar()
{
    digitalWrite(pin, 0);
}

/* Hace parpadear al led un numero determinado de veces con cierto tiempo de retraso */
void Led::parpadear(int veces, int milisegundos)
{
  for (int i = 0; i < veces; i++)
  {
    encender();
    delay(milisegundos);

    apagar();
    delay(milisegundos);
  }
}

/* Hace parpadear al led una sola vez con cierto tiempo de retraso */
void Led::parpadearUno(int milisegundos)
{
  encender();
  delay(milisegundos);

  apagar();
  delay(milisegundos);
}

/* Activa una salida en estado alto para encender el Led, después de un tiempo activa la salida en estado bajo para apagar el Led */
void Led::encenderTemporal(int milisegundos)
{
  encender();
  delay(milisegundos);
  apagar();
}
