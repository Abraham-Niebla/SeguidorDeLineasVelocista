/*Boton.cpp*/
#include "Boton.h"
#include <Arduino.h>

/* Constructor de objetos */
Boton::Boton(int pinBTN) : pin(pinBTN) {}

/* Inicializador de objetos */
void Boton::begin(bool activacion)
{
  if(activacion) // Si se activa con 1
    pinMode(pin, INPUT);
  else // Si se activa con 0
    pinMode(pin, INPUT_PULLUP);

  state = activacion;
}

/* Envía un 1 lógico si el botón ha sido pulsado
 * Envía un 0 lógico si el botón no ha sido pulsado */
bool Boton::esPulsado()
{
    return (digitalRead(pin) == state);
}

/* Crea un bucle infinito que se detendrá hasta que el botón sea pulsado */
void Boton::esperarPresionar()
{
    while (!esPulsado()) {};
}

/* Crea un bucle infinito que se detendrá hasta que el botón deje de ser pulsado */
void Boton::esperarSoltar()
{
    while (esPulsado()) {};
}
