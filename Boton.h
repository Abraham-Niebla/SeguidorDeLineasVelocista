/*Boton.h*/
#ifndef Boton_h
#define Boton_h

#include <Arduino.h>

class Boton
{
  public:
      Boton(int pinBTN); // Constructor de objetos
      void begin(bool activacion); // Inicializador del Boton

      bool esPulsado();
      void esperarPresionar();
      void esperarSoltar();

  private:
      uint8_t pin; //Pin del Boton
      bool state; //Estado del botón para indicar que se presiona
};

#endif